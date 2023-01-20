/*!*************************************************************************
****
\file			VertexBuffer.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			9-28-2022
\brief			This file contain the neccesary declaration functions for class vertexbuffer,
				vertexarray, index array and buffer element and layout.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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

		virtual const BufferLayout& GetLayout() const override { return mLayout; }
		virtual void  SetLayout(const BufferLayout& layout) override { mLayout = layout; }
	private:
		unsigned int mRenderID;
		BufferLayout mLayout;
	};

	
	class IBuffer : public IndexBuffer
	{
	public:
		 IBuffer(unsigned int* indices, unsigned int count);
		 virtual ~IBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const { return mCount; }
	private:

		unsigned int mRenderID;
		unsigned int mCount;
	};
	
}
