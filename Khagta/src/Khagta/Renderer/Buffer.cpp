#include "kgpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Khagta {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KG_CORE_ASSERT(false,"RendererAPI::None is currently not supported."); return nullptr;

		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		KG_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KG_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;

		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		KG_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}