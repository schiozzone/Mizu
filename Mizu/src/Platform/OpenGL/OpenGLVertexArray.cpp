#include "mzpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Mizu {

	static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3:   return GL_FLOAT;
		case ShaderDataType::Mat4:   return GL_FLOAT;
		case ShaderDataType::Int:    return GL_INT;
		case ShaderDataType::Int2:   return GL_INT;
		case ShaderDataType::Int3:   return GL_INT;
		case ShaderDataType::Int4:   return GL_INT;
		case ShaderDataType::Bool:   return GL_BOOL;
		}

		MZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		MZ_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_ArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		MZ_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void OpenGLVertexArray::Bind() const
	{
		MZ_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		MZ_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		MZ_PROFILE_FUNCTION();
		MZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!")

		glBindVertexArray(m_ArrayID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToGLenum(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(size_t)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		MZ_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
