#include "evpch.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexArray.h"
#include "Shader.h"
#include "CameraController.h"
#include "RenderCommand.h"
#include "Render/Renderer2D.h"
#include "Texture.h"

namespace Envii
{
	struct RenderData
	{
		RenderData()
			: m_ShaderLib() {}
		
		Ref<VertexArray> m_Vao;
		Ref<VertexArray> m_SquareVao;
		Ref<Texture2D> m_WhiteTex;

		ShaderLibrary m_ShaderLib;

		glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f }, m_SquarePos = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_ViewProj = glm::mat4(1.0f);
	};

	static RenderData* s_Data;
	void Renderer2D::Init()
    {
		s_Data = new RenderData();
		float vertices[] = {
			-0.6f, -0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 0.6f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			 0.6f,  0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.6f,  0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		// Create vertex array
		s_Data->m_Vao = VertexArray::Create();

		// Create vertex buffer and layout
		Ref<VertexBuffer> Vb;
		Vb = VertexBuffer::Create(vertices, sizeof(vertices));
		Vb->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		// Create index buffer
		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> Ib;
		Ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		s_Data->m_Vao->AddVertexBuffer(Vb);
		s_Data->m_Vao->SetIndexBuffer(Ib);

		float quadVertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		// Create vertex array
		s_Data->m_SquareVao = VertexArray::Create();

		// Create vertex buffer and layout
		Ref<VertexBuffer> quadVb;
		quadVb = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVb->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		// Create index buffer
		uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> quadIb;
		quadIb = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));

		s_Data->m_SquareVao->AddVertexBuffer(quadVb);
		s_Data->m_SquareVao->SetIndexBuffer(quadIb);

		// Create shaders
		s_Data->m_ShaderLib.Load("assets/shaders/VFTexColor.glsl");
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor");
		texShader->Bind();

		// Create default (white) 1x1 texture
		s_Data->m_WhiteTex = Texture2D::Create(1, 1, 3);
		unsigned char pixel[3] = { 0xff, 0xff, 0xff };
		s_Data->m_WhiteTex->SetData(pixel, sizeof(pixel));
		s_Data->m_WhiteTex->Bind(0);
    }

    void Renderer2D::Shutdown()
    {
		delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthoCamera& camera)
    {
        s_Data->m_ViewProj = camera.GetViewProjection();
    }

    void Renderer2D::EndScene()
    {

    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture>& texture, uint32_t texId)
    {
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor");
		texture->Bind(texId);
        texShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		texShader->SetUniformMat4f("u_Transform", transform);
		texShader->SetUniform1i("u_TexSlot", texId);
		texShader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
		s_Data->m_Vao->Bind();
        RenderCommand::DrawIndexed(s_Data->m_Vao);
    }

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor"); 
		texShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		texShader->SetUniformMat4f("u_Transform", transform);
		// Default (white) texture is already bound at slot 0
		texShader->SetUniform1i("u_TexSlot", 0);
		texShader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
		s_Data->m_SquareVao->Bind();
		RenderCommand::DrawIndexed(s_Data->m_SquareVao);
	}

    
}