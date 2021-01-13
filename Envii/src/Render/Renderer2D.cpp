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
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexSlot;
	}; 

	struct RenderData
	{
		const size_t MAX_QUADS = 10000;
		const size_t MAX_VERTS = (4 * MAX_QUADS);
		const size_t MAX_INDICES = (6 * MAX_QUADS);
		static const size_t MAX_TEXTURES = 32; // TODO: Get max from renderer caps
		std::array<Ref<Texture>, MAX_TEXTURES> textures;
		uint32_t currTexSlot = 1; // 0 will be white texture
		
		uint32_t quadIndexCount = 0;
		QuadVertex* quadBufferStart = nullptr;
		QuadVertex* quadBufferPtr = nullptr;
		
		RenderData()
			: m_ShaderLib() {}
		
		Ref<VertexArray> m_QuadVao;
		Ref<VertexBuffer> m_QuadVbo;
		Ref<Texture2D> m_WhiteTex;

		ShaderLibrary m_ShaderLib;

		glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f }, m_SquarePos = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_ViewProj = glm::mat4(1.0f);
	};

	static RenderData* s_Data;
	void Renderer2D::Init()
    {
		s_Data = new RenderData();

		// Create vertex array
		s_Data->m_QuadVao = VertexArray::Create();

		// Create vertex buffer and layout
		s_Data->m_QuadVbo = VertexBuffer::Create(s_Data->MAX_VERTS * sizeof(QuadVertex));
		s_Data->m_QuadVbo->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexSlot" }
		});

		s_Data->quadBufferStart = new QuadVertex[s_Data->MAX_VERTS];

		// Create index buffer
		uint32_t* indices = new uint32_t[s_Data->MAX_INDICES]; 

		uint32_t indexCount = 0;
		uint32_t pattern[6] = { 0, 1, 2, 2, 3, 0 };
		for (uint32_t i = 0; i < s_Data->MAX_QUADS; ++i)
		{
			for (uint32_t j = 0; j < 6; j++)
				indices[indexCount + j] = pattern[j] + i * (uint32_t)4;
			
			indexCount += 6;
		}
		EV_CORE_ASSERT(indexCount == s_Data->MAX_INDICES, "Index Count wrong during generation.")

		Ref<IndexBuffer> Ib;
		Ib = IndexBuffer::Create(indices, indexCount);
		delete[] indices;

		s_Data->m_QuadVao->AddVertexBuffer(s_Data->m_QuadVbo);
		s_Data->m_QuadVao->SetIndexBuffer(Ib);

		// Create shaders
		s_Data->m_ShaderLib.Load("assets/shaders/VFTexColor.glsl");
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor");
		texShader->Bind();

		// Create default (white) 1x1 texture
		s_Data->m_WhiteTex = Texture2D::Create(1, 1, 3);
		unsigned char pixel[3] = { 0xff, 0xff, 0xff };
		s_Data->m_WhiteTex->SetData(pixel, sizeof(pixel));
		s_Data->m_WhiteTex->Bind(0);

		// Init tex slots
		s_Data->textures[0] = s_Data->m_WhiteTex;
    }

    void Renderer2D::Shutdown()
    {
		delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthoCamera& camera)
    {
        s_Data->m_ViewProj = camera.GetViewProjection();
		s_Data->quadBufferPtr = s_Data->quadBufferStart;
		s_Data->quadIndexCount = 0;
		s_Data->currTexSlot = 1;
    }

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data->currTexSlot; i++)
			s_Data->textures[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data->m_QuadVao, s_Data->quadIndexCount);
	}

    void Renderer2D::EndScene()
    {
		uint32_t sizeInBytes = (uint8_t*)s_Data->quadBufferPtr - (uint8_t*)s_Data->quadBufferStart;
		s_Data->m_QuadVbo->SetData(s_Data->quadBufferStart, sizeInBytes);
		Flush();
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture>& texture, float texCoordScale, uint32_t texId)
    {
		float texSlot = 0.0f;
		for (uint32_t i = 1; i < s_Data->currTexSlot; i++)
		{
			if (*(s_Data->textures[i].get()) == *(texture.get()))
			{
				texSlot = (float)i;
				break;
			}
		}

		if (texSlot == 0.0f)
		{
			texSlot = (float)s_Data->currTexSlot;
			s_Data->textures[s_Data->currTexSlot] = texture;
			s_Data->currTexSlot++;
		}

		s_Data->quadBufferPtr->Position = position;
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;
		
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor");
		texture->Bind(texId);
        texShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		//glm::mat4 transform = glm::translate(glm::mat4(1.0), position);
		texShader->SetUniformMat4f("u_Transform", glm::mat4(1.0f));// transform);

		int samplers[s_Data->MAX_TEXTURES];
		for (uint32_t i = 0; i < s_Data->MAX_TEXTURES; i++)
			samplers[i] = i;
			
		texShader->SetUniform1iv("u_TexSlot", s_Data->MAX_TEXTURES, samplers);
		texShader->SetUniform1f("u_TexCoordScale", texCoordScale);

		s_Data->quadIndexCount += 6;
    }

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		const float texSlot = 0.0f; // White texture
		
		s_Data->quadBufferPtr->Position = position;
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor"); 
		texShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		//glm::mat4 transform = glm::translate(glm::mat4(1.0), position);
		texShader->SetUniformMat4f("u_Transform", glm::mat4(1.0f));// transform);
		// Default (white) texture is already bound at slot 0
		int samplers[s_Data->MAX_TEXTURES];
		for (uint32_t i = 0; i < s_Data->MAX_TEXTURES; i++)
			samplers[i] = i;

		texShader->SetUniform1iv("u_TexSlot", s_Data->MAX_TEXTURES, samplers);
		texShader->SetUniform1f("u_TexCoordScale", 1.0f);

		s_Data->quadIndexCount += 6;
	}


	void Renderer2D::DrawQuadRotate(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture>& texture, float rotation, float texCoordScale, uint32_t texId)
	{
		float texSlot = 0.0f;
		for (uint32_t i = 1; i < s_Data->currTexSlot; i++)
		{
			if (*(s_Data->textures[i].get()) == *(texture.get()))
			{
				texSlot = (float)i;
				break;
			}
		}

		if (texSlot == 0.0f)
		{
			texSlot = (float)s_Data->currTexSlot;
			s_Data->textures[s_Data->currTexSlot] = texture;
			s_Data->currTexSlot++;
		}
		
		s_Data->quadBufferPtr->Position = position;
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;
		
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor");
		texture->Bind(texId);
		texShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		//glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * 
			//glm::rotate(glm::mat4(1.0), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });

		texShader->SetUniformMat4f("u_Transform", glm::mat4(1.0f));// transform);
		int samplers[s_Data->MAX_TEXTURES];
		for (uint32_t i = 0; i < s_Data->MAX_TEXTURES; i++)
			samplers[i] = i;

		texShader->SetUniform1iv("u_TexSlot", s_Data->MAX_TEXTURES, samplers);
		texShader->SetUniform1f("u_TexCoordScale", texCoordScale);

		s_Data->quadIndexCount += 6;
	}

	void Renderer2D::DrawQuadRotate(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		const float texSlot = 0.0f;
		
		s_Data->quadBufferPtr->Position = position;
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;

		s_Data->quadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data->quadBufferPtr->Color = color;
		s_Data->quadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data->quadBufferPtr->TexSlot = texSlot;
		s_Data->quadBufferPtr++;
		
		Ref<Shader> texShader = s_Data->m_ShaderLib.Get("VFTexColor");
		texShader->SetUniformMat4f("u_VP", s_Data->m_ViewProj);
		//glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * 
			//glm::rotate(glm::mat4(1.0), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });

		texShader->SetUniformMat4f("u_Transform", glm::mat4(1.0f));// transform);
		// Default (white) texture is already bound at slot 0
		int samplers[s_Data->MAX_TEXTURES];
		for (uint32_t i = 0; i < s_Data->MAX_TEXTURES; i++)
			samplers[i] = i;

		texShader->SetUniform1iv("u_TexSlot", s_Data->MAX_TEXTURES, samplers);
		texShader->SetUniform1f("u_TexCoordScale", 1.0f);

		s_Data->quadIndexCount += 6;
	}
}