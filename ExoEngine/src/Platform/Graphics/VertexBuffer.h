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
#include <GL/glew.h>
namespace EM
{
	class VertexBuffer
	{
	public:
		VertexBuffer(float* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	

	private:
		unsigned int m_RenderID;

	};


	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int* indices, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		unsigned int GetCount() const { return m_count; }

	private:

		unsigned int m_RenderID;
		unsigned int m_count;
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffers; }
		static VertexArray* Create();

	private:
		unsigned int m_RenderID;
		unsigned int m_VBIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffers;
	};
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 8;
			case ShaderDataType::Float3:	return 12;
			case ShaderDataType::Float4:	return 16;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 8;
			case ShaderDataType::Int3:		return 12;
			case ShaderDataType::Int4:		return 16;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		EM_EXO_ASSERT(false, "Unknow Data type!");
		return 0;
	}

	//////////buffer elements
	class BufferElements
	{
	public:

		//BufferElements() {};
		BufferElements(ShaderDataType type, const std::string& name,  bool normalized = GL_FALSE)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		unsigned int GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			EM_EXO_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	public:
		ShaderDataType Type;
		std::string Name;
		size_t Size;
		unsigned int Offset;
		bool Normalized;
		
	};


	//bufferlayout
	class BufferLayout 
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElements>& elements)
		: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		//getter
		inline unsigned int GetStride() const { return m_stride; }
		inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }

		std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElements> m_Elements;
		unsigned int m_stride = 0;
		
	};

	
}