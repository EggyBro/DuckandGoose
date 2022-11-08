#include "empch.h"
#include "Buffer.h"
#include "VertexBuffer.h"

namespace EM {
	MultiRefs<VertexBuffer> VertexBuffer::Create(uint32_t size)//Dynamic Draw
	{
		return CreateMultiRefs<VBuffer>(size);
	}

	MultiRefs<VertexBuffer> VertexBuffer::Create(float* data, unsigned int size)//Static Draw
	{
		return CreateMultiRefs<VBuffer>(data, size);
	}

	MultiRefs<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		return CreateMultiRefs<IBuffer>(indices, count);
	}
}