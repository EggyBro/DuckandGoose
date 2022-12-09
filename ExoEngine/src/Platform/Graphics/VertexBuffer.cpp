/*!*************************************************************************
****
\file			VertexBuffer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			9-28-2022
\brief			This file handle vertexbuffer, indexbuffer, vertaxarray

****************************************************************************
***/
#include "empch.h"
#include "VertexBuffer.h"

//new 
#include "GL/glew.h"
namespace EM{

	/*!*************************************************************************
	Constructor for VBuffer
	****************************************************************************/
	VBuffer::VBuffer(uint32_t size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	/*!*************************************************************************
	Overloaded Constructor for VBuffer
	****************************************************************************/
	VBuffer::VBuffer(float* vertices, unsigned int size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	/*!*************************************************************************
	Destructor for VBuffer
	****************************************************************************/
	VBuffer::~VBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	/*!*************************************************************************
	Bind VBuffer
	****************************************************************************/
	void VBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	/*!*************************************************************************
	Unbind VBuffer
	****************************************************************************/
	void VBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*!*************************************************************************
	Set buffer data
	****************************************************************************/
	void VBuffer::SetBufferData(const void* data, unsigned int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	////////////INDEX BUFFER///////////
	/*!*************************************************************************
	Constructor for IBuffer
	****************************************************************************/
	IBuffer::IBuffer(unsigned int* indices, unsigned int count)
		:m_count(count)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	/*!*************************************************************************
	Destructor for IBuffer
	****************************************************************************/
	IBuffer::~IBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	/*!*************************************************************************
	Bind for IBuffer
	****************************************************************************/
	void IBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}

	/*!*************************************************************************
	Unbind for IBuffer
	****************************************************************************/
	void IBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
