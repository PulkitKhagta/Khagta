#include "kgpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Khagta {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}