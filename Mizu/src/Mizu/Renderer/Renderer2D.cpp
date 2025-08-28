#include "mzpch.h"
#include "Mizu/Renderer/Renderer2D.h"

#include "Mizu/Renderer/VertexArray.h"
#include "Mizu/Renderer/Shader.h"
#include "Mizu/Renderer/RenderCommand.h"

#include <glm/ext/matrix_transform.hpp>

namespace Mizu {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVA;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		MZ_PROFILE_FUNCTION();
		s_Data = new Renderer2DStorage;

		s_Data->QuadVA = VertexArray::Create();

		float vertices[4 * 5] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
		};
		vertexBuffer->SetLayout(layout);
		s_Data->QuadVA->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3 * 2] = {
			3, 1, 0,
			3, 2, 1,
		};
		Ref<Mizu::IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data->QuadVA->SetIndexBuffer(indexBuffer);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t wtData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&wtData, sizeof(uint32_t));

		s_Data->Shader = Shader::Create("assets/shaders/Shader2D.glsl");
		s_Data->Shader->Bind();
		s_Data->Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		MZ_PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		MZ_PROFILE_FUNCTION();
		s_Data->Shader->Bind();
		s_Data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		MZ_PROFILE_FUNCTION();

	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		MZ_PROFILE_FUNCTION();
		s_Data->Shader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();

		s_Data->Shader->SetMat4("u_Transform", glm::scale(glm::translate(glm::mat4(1.0f), position), { size.x, size.y, 1.0f }));

		s_Data->QuadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVA);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		MZ_PROFILE_FUNCTION();
		s_Data->Shader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		s_Data->Shader->SetMat4("u_Transform", glm::scale(glm::translate(glm::mat4(1.0f), position), { size.x, size.y, 1.0f }));


		s_Data->QuadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVA);
	}
	   
}