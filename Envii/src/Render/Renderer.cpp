#include "evpch.h"

#include <glad/glad.h>
#include "Render/Renderer.h"
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

    void Renderer::BeginScene(OrthoCamera& camera)
    {
        s_SceneData->ViewProjMat = camera.GetViewProjection();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, 
                          const std::shared_ptr<Shader>& shader,
                          const glm::mat4& transform)
    {
        vertexArray->Bind();
        shader->Bind();
        shader->SetUniformMat4f("u_VP", s_SceneData->ViewProjMat);
        shader->SetUniformMat4f("u_Transform", transform);
        RenderCommand::DrawIndexed(vertexArray);
    }
}