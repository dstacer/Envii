#include "evpch.h"

#include <glad/glad.h>
#include "Renderer.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

namespace Envii
{
    void ClearGlErrors()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool LogGlErrors(const char* file, const char* function, int line)
    {
        while (GLenum err = glGetError())
        {
            std::cout << "OPENGL ERROR: (0x" << std::hex << err << ") in "
                << function << " " << file << ": " << std::dec << line << std::endl;
            return false;
        }
        return true;
    }

    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        delete s_SceneData;
        Renderer2D::Shutdown();
    }

    void Renderer::BeginScene(const OrthoCamera& camera)
    {
        s_SceneData->ViewProjMat = camera.GetViewProjection();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, 
                          const Ref<Shader>& shader,
                          const glm::mat4& transform)
    {
        vertexArray->Bind();
        shader->Bind();
        shader->SetUniformMat4f("u_VP", s_SceneData->ViewProjMat);
        shader->SetUniformMat4f("u_Transform", transform);
        RenderCommand::DrawIndexed(vertexArray);
    }
}