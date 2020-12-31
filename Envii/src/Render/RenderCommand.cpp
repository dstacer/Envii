#include "evpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderApi.h"

namespace Envii
{
	RenderApi* RenderCommand::s_RenderApi = new OpenGLRenderApi();

}