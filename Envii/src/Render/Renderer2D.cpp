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
		
		Envii::Ref<Envii::VertexArray> m_Vao;
		Envii::Ref<Envii::VertexArray> m_SquareVao;

		Envii::ShaderLibrary m_ShaderLib;
		Envii::Ref<Envii::Texture2D> m_Tex;
		Envii::Ref<Envii::Texture2D> m_SquareTex;

		glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f }, m_SquarePos = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_ViewProj = glm::mat4(1.0f);
	};

	static RenderData* s_Data;
	void Renderer2D::Init()
    {
		s_Data = new RenderData();
		float vertices[] = {
		-0.6f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.6f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		 0.6f,  0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.6f,  0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
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
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		// Create vertex array
		s_Data->m_SquareVao = VertexArray::Create();

		// Create vertex buffer and layout
		Ref<VertexBuffer> quadVb;
		quadVb = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVb->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});

		// Create index buffer
		uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> quadIb;
		quadIb = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));

		s_Data->m_SquareVao->AddVertexBuffer(quadVb);
		s_Data->m_SquareVao->SetIndexBuffer(quadIb);

		// Create shaders
		s_Data->m_ShaderLib.Load("assets/shaders/Square.glsl");
		s_Data->m_ShaderLib.Load("assets/shaders/Quad.glsl");

		s_Data->m_Tex = Texture2D::Create("assets/textures/Kreator.png", 0);
		s_Data->m_Tex->Bind(0);
		s_Data->m_SquareTex = Texture2D::Create("assets/textures/Checkerboard.png", 1);
		s_Data->m_SquareTex->Bind(1);
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

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float texId)
    {
		Ref<Shader> squareShader = s_Data->m_ShaderLib.Get("Square");
		squareShader->Bind();
        squareShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		squareShader->SetUniformMat4f("u_Transform", transform);
		squareShader->SetUniform1i("u_TexSlot", 1);
		s_Data->m_SquareVao->Bind();
        RenderCommand::DrawIndexed(s_Data->m_SquareVao);
    }

    
}