/*!*************************************************************************
****
\file			Buffer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			02-11-2022
\brief			This file contain all the helper function needed for buffer
				optimatization so that it will be easier to handle the buffer
				data

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Buffer.h"
#include "VertexBuffer.h"

namespace EM {
	/*!*************************************************************************
	Dynamic draw buffer
	****************************************************************************/
	MultiRefs<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		return CreateMultiRefs<VBuffer>(size);
	}

	/*!*************************************************************************
	Static draw buffer
	****************************************************************************/
	MultiRefs<VertexBuffer> VertexBuffer::Create(float* data, unsigned int size)
	{
		return CreateMultiRefs<VBuffer>(data, size);
	}

	/*!*************************************************************************
	draw buffer
	****************************************************************************/
	MultiRefs<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		return CreateMultiRefs<IBuffer>(indices, count);
	}
}