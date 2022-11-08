/*!*************************************************************************
****
\file			VertexBuffer.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the neccesary declaration functions for class vertexbuffer,
				vertexarray, index array and buffer element and layout.

****************************************************************************
***/
#pragma once
#include "Buffer.h"
namespace EM
{
	class VBuffer : public VertexBuffer
	{
	public:
		VBuffer(uint32_t size);
		VBuffer(float* data, unsigned int size);
		virtual ~VBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetBufferData(const void* data, unsigned int size) override;

		virtual const BufferLayout& GetLayout() const override { return m_layout; }
		virtual void  SetLayout(const BufferLayout& layout) override { m_layout = layout; }
	private:
		unsigned int m_RenderID;
		BufferLayout m_layout;
	};

	
	class IBuffer : public IndexBuffer
	{
	public:
		 IBuffer(unsigned int* indices, unsigned int count);
		 virtual ~IBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const { return m_count; }
	private:

		unsigned int m_RenderID;
		unsigned int m_count;
	};
	
}
