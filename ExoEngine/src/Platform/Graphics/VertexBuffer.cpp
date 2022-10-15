/*!*************************************************************************
****
\file			VertexBuffer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file handle vertexbuffer, indexbuffer, vertaxarray

****************************************************************************
***/
#include "empch.h"
#include "VertexBuffer.h"

namespace EM{

	//////////Vertex BUFFER///////////
	VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//////////INDEX BUFFER///////////

	IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
		:m_count(count)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}
	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}
	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	//////////Vertex Array///////////
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		glBindVertexArray(m_RenderID);
		vertexbuffer->Bind();
		//do the layout here
		BufferLayout layout = {
			{ShaderDataType::Float3, "position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		};

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VBIndex);
			glVertexAttribPointer(m_VBIndex, element.GetComponentCount(),
				GL_FLOAT, element.Normalized, layout.GetStride(), (const void*)element.Offset);

			m_VBIndex++;
		}

		m_VertexBuffers.push_back(vertexbuffer);
	}
	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();

		m_IndexBuffers = indexBuffer;

	}
	VertexArray* VertexArray::Create()
	{
		return new VertexArray;
	}
}
