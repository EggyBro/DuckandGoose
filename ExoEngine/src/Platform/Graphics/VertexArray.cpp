/*!*************************************************************************
****
\file			VertexArray.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			02-11-2022
\brief			This file contain VertexBuffer binding and unbind set the buffer
				layout to tell house our buffer data will be read by our gpu

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "VertexArray.h"

namespace EM {

	////////////Vertex Array///////////
	/*!*************************************************************************
	Constructor for VertexArray
	****************************************************************************/
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &mRenderID);
	}

	/*!*************************************************************************
	Destructor for VertexArray
	****************************************************************************/
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(0, &mRenderID);
	}

	/*!*************************************************************************
	Bind VertexArray
	****************************************************************************/
	void VertexArray::Bind() const
	{
		glBindVertexArray(mRenderID);
	}

	/*!*************************************************************************
	Bind VertexArray
	****************************************************************************/
	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	/*!*************************************************************************
	Add vertex buffer
	****************************************************************************/
	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		glBindVertexArray(mRenderID);
		vertexbuffer->Bind();

		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(mVBIndex);
			glVertexAttribPointer(mVBIndex, element.GetComponentCount(),
				GL_FLOAT, element.Normalized, layout.GetStride(), (const void*) element.Offset);

			mVBIndex++;
		}

		mVertexBuffers.push_back(vertexbuffer);
	}

	/*!*************************************************************************
	Set index buffer
	****************************************************************************/
	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(mRenderID);
		indexBuffer->Bind();

		mIndexBuffers = indexBuffer;
	}
}