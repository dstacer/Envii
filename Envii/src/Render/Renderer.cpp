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

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}