#pragma once


namespace EM {

	// user defined format of Opengl framebuffer format types 
	enum class FrameBufferTextureFormat {
		NONE = 0,
		RGBA8,					// Color
		RED_INTEGER,
		DEPTH24STENCIL8,		// Depth stencil
		DEPTH = DEPTH24STENCIL8 // default
	};

	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format) : TextureFormat(format) {}
		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::NONE;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list< FrameBufferTextureSpecification> attachments) : Attachments(attachments) {}
		std::vector<FrameBufferTextureSpecification> Attachments;
	};

	struct FrameBufferSpecification
	{
		uint32_t Width{}, Height{};
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};
	class FrameBuffer
	{
	public:
		FrameBuffer() = default;
		~FrameBuffer();

		const FrameBufferSpecification GetSpecification() const;
		uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const;
		void SetFrameBufferSpecification(const FrameBufferSpecification&);

		void Resize(uint32_t width, uint32_t height);

		int ReadPixel(uint32_t attachmentIndex, int x, int y);
		void Create();
		void Bind();
		void UnBind();
	private:
		// framebuffer
		uint32_t m_RendererID = 0;
		FrameBufferSpecification m_Specification;
		// framebuffer instance 
		static std::unique_ptr<FrameBuffer> _finstance;

		// contains all the ColorAttachmentSpecification (user has defined)
		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecification;
		// depth attachment not using currently 
		FrameBufferTextureSpecification m_DepthAttachmentSpecifiication = FrameBufferTextureFormat::NONE;

		// contains all the ColorAttachments renderID 
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}