#include "mzpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Mizu {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		MZ_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& file)
	{
		MZ_PROFILE_FUNCTION();
		std::string source = ReadFile(file);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		size_t begin = file.find_last_of("/\\");
		begin = begin == std::string::npos ? 0 : begin + 1;
		size_t end = file.rfind('.');
		m_Name = file.substr(begin, end == std::string::npos ? file.size() - begin : end - begin);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name(name)
	{
		MZ_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		MZ_PROFILE_FUNCTION();
		glDeleteProgram(m_ProgramID);
	}

	std::string OpenGLShader::ReadFile(const std::string& file)
	{
		MZ_PROFILE_FUNCTION();
		std::string result;
		std::ifstream in(file, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				MZ_CORE_ERROR("Invalid file size '{0}'", file);
			}
		}
		else
		{
			MZ_CORE_ERROR("Could not open file '{0}'", file);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		MZ_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			MZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			MZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			MZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		MZ_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();
		//MZ_CORE_ASSERT(shaderSources.size() <= 2, "Only up to 2 shaders are supported");
		//std::array<GLuint, 2> glShaderIDs; // Maybe std::vector was better (should check performance)
		std::vector<GLuint> glShaderIDs;
		glShaderIDs.reserve(shaderSources.size());
		//int glShaderIDIndex = 0;
		for (auto& keyValuePair : shaderSources)
		{
			GLenum type = keyValuePair.first;
			const std::string& shaderSource = keyValuePair.second;

			GLuint shader = glCreateShader(type);

			const GLchar *source = shaderSource.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);
				for (auto id : glShaderIDs)
					glDeleteShader(id);

				MZ_CORE_ERROR("{0}", infoLog.data());
				MZ_CORE_ASSERT(false, "Shader compilation failed!");

				return;
			}
			glAttachShader(program, shader);
			//glShaderIDs[glShaderIDIndex++] = shader;
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			MZ_CORE_ERROR("{0}", infoLog.data());
			MZ_CORE_ASSERT(false, "Shader linking failed!");

			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_ProgramID = program;
	}

	void OpenGLShader::Bind() const
	{
		MZ_PROFILE_FUNCTION();
		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::Unbind() const
	{
		MZ_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		MZ_PROFILE_FUNCTION();
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		MZ_PROFILE_FUNCTION();
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		MZ_PROFILE_FUNCTION();
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		MZ_PROFILE_FUNCTION();
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_ProgramID, name.c_str()), value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_ProgramID, name.c_str()), value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(m_ProgramID, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
