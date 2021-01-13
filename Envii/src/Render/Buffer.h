#pragma once

#include <vector>
#include "../Core/Log.h"
#include "../Core/Core.h"

namespace Envii
{
	enum class ShaderDataType
	{
		NONE = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 2*4;
			case ShaderDataType::Float3:	return 3*4;
			case ShaderDataType::Float4:	return 4*4;
			case ShaderDataType::Mat3:		return 3*4*4;
			case ShaderDataType::Mat4:		return 4*4*4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 2*4;
			case ShaderDataType::Int3:		return 3*4;
			case ShaderDataType::Int4:		return 4*4;
			case ShaderDataType::Bool:		return 1;

			EV_CORE_ASSERT(false, "Undefined ShaderDataType: {0}", type);
			return 999;
		}

		return 999;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		bool Normalized;
		uint32_t Size;
		uint32_t Offset;
		
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), 
			 Type(type), 
			 Normalized(normalized),
			 Size(ShaderDataTypeSize(type)), 
			 Offset(0) {}

		uint32_t GetValueCount(ShaderDataType type) const
		{
			switch (type)
			{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 4;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Bool:		return 1;

				EV_CORE_ASSERT(false, "Undefined ShaderDataType: {0}", type);
				return 0;
			}
			return 0;
		}

		
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const
		{
			return m_Elements;
		}

		inline const uint32_t GetStride() const
		{
			return m_Stride;
		}

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }


		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end()	const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset += offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	}; 
	
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual void SetData(const void* data, uint32_t sizeInBytes) = 0;

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* indices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* vertices, uint32_t count);
	};
}
