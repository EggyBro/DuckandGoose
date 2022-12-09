/*!*************************************************************************
****
\file			FrameBuffer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-02-2022
\brief			This file binds the framebuffer and gets the pixel cooridnate
				and can be used in it in level editor
****************************************************************************
***/
#include "empch.h"
#include "FrameBuffer.h"
#include <GL/glew.h>
namespace EM {

	std::unique_ptr<FrameBuffer> FrameBuffer::_finstance{ nullptr };

	std::unique_ptr<FrameBuffer>& FrameBuffer::GetInstance()
	{
		if (_finstance == nullptr)
		{
			_finstance = std::make_unique<FrameBuffer>();
		}
		return _finstance;
	}

	/*!*************************************************************************
	return pixelData
	****************************************************************************/
	int FrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}
	namespace Helper {

		/*!*************************************************************************
		Switch between multi-sampling and single sampling
		****************************************************************************/
		static GLenum TextureTarget(bool multisampled)  
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		/*!*************************************************************************
		Check DepthFormat
		****************************************************************************/
		static bool IsDepthFormat(FrameBufferTextureFormat format)
		{
			switch (format)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				return true;
			}
			return false;
		}

		/*!*************************************************************************
		Create texture
		****************************************************************************/
		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		/*!*************************************************************************
		Bind texture
		****************************************************************************/
		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		/*!*************************************************************************
		ColorAttachment 
		ie internalFormat - GL_RGBA8 format - GL_RGBA
		ie internalFormat - GL_R32I format - GL_RED_INTEGER (reading int from the shader file)	
		****************************************************************************/
		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, size_t index)
		{
			bool multisampled = samples > 1;
			if (multisampled) // check whether its used for multisampling (currently no)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)index, (GLenum)TextureTarget(multisampled), id, 0);

		}

		/*!*************************************************************************
		DepthBufferAttachment :
		currently not using 
		****************************************************************************/
		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}
	}

	/*!*************************************************************************
	Find buffer specs
	****************************************************************************/
	const FrameBufferSpecification EM::FrameBuffer::GetSpecification() const
	{
		return m_Specification;
	}

	/*!*************************************************************************
	Find color attachment
	****************************************************************************/
	uint32_t FrameBuffer::GetColorAttachmentRendererID(uint32_t index) const
	{
		//GM_CORE_ASSERT(index < m_ColorAttachments.size(), "");
		return  m_ColorAttachments[index];
	}

	/*!*************************************************************************
	Set frame specifications
	****************************************************************************/
	void FrameBuffer::SetFrameBufferSpecification(const FrameBufferSpecification& specification)
	{
		m_Specification = specification;

		for (auto spec : m_Specification.Attachments.Attachments)
		{
			if (!Helper::IsDepthFormat(spec.TextureFormat))
			{
				m_ColorAttachmentSpecification.emplace_back(spec);
			}
			else
				m_DepthAttachmentSpecifiication = spec;
		}

		Create();
	}

	/*!*************************************************************************
	Resize frame specification
	****************************************************************************/
	void FrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		// update the specification
		m_Specification.Width = width;
		m_Specification.Height = height;
		Create();
	}

	/*!*************************************************************************
	Destructor
	****************************************************************************/
	FrameBuffer::~FrameBuffer()
	{
		// delete framebuffer object
		glDeleteFramebuffers(1, &m_RendererID);
		// delete color attachment textures
		glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());

		glDeleteRenderbuffers(1, &m_DepthAttachment);
	}

	/*!*************************************************************************
	Create frame buffer
	****************************************************************************/
	void FrameBuffer::Create()
	{
		if (m_RendererID)
		{
			// delete framebuffer object
			glDeleteFramebuffers(1, &m_RendererID);
			// delete color attachment textures
			glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());
			// delete renderbuffer objects
			glDeleteRenderbuffers(1, &m_DepthAttachment);
			// clear attachments
			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		// creating a framebuffer obj
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisample = m_Specification.Samples > 1; // check the specification if its multi-sampling 

		// Attachments
		if (m_ColorAttachmentSpecification.size())
		{
			// resize the ColorAttachment ID vector size to fit the ColorSpecification vector size (contains data properties of color attachment) 
			m_ColorAttachments.resize(m_ColorAttachmentSpecification.size());

			// generates color attachments 
			Helper::CreateTextures(multisample, m_ColorAttachments.data(), (uint32_t)m_ColorAttachments.size());
			for (size_t i{ 0 }; i < m_ColorAttachments.size(); ++i)
			{
				Helper::BindTexture(multisample, m_ColorAttachments[i]);

				// switch between rendering RGBA8 for the game and RED_INTGER for shader 
				switch (m_ColorAttachmentSpecification[i].TextureFormat)
				{
					// Current Game (RGBA8)
				case FrameBufferTextureFormat::RGBA8:
					Helper::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
					break;
					// Used to sample an int value from the fragment shader 
				case FrameBufferTextureFormat::RED_INTEGER:
					Helper::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
					break;
				}
			}
		}


		// generates Depth stencil attachment (not using)
		if (m_DepthAttachmentSpecifiication.TextureFormat != FrameBufferTextureFormat::NONE)
		{
			// create depth attachment 
			Helper::CreateTextures(multisample, &m_DepthAttachment, 1);
			Helper::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecifiication.TextureFormat)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				Helper::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
			}
		}

		// draw (max of 4 color attachments)
		if (m_ColorAttachments.size() > 1)
		{
			/*GM_CORE_ASSERT(m_ColorAttachments.size() <= 4, "Color AttachMent is more than 4");*/
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((GLsizei)m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// depth pass
			glDrawBuffer(GL_NONE);
		}

		// check framebuffer status
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		EM_EXO_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");

		// render onto the main window (activate default framebuffer)	
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	/*!*************************************************************************
	Bind frambuffer
	****************************************************************************/
	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	/*!*************************************************************************
 	Unbind frambuffer
	****************************************************************************/
	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}