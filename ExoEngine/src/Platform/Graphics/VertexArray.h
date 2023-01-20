/*!*************************************************************************
****
\file			VertexArray.h
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
#pragma once
#include "Buffer.h"
namespace EM {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return mVertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return mIndexBuffers; }
		static MultiRefs<VertexArray> Create() { return CreateMultiRefs<VertexArray>(); }
	private:
		unsigned int mRenderID;
		unsigned int mVBIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffers;
	};
}