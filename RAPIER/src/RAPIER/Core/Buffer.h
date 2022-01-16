#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Log.h"

namespace RAPIER
{

	struct Buffer
	{
		void* Data;
		uint32_t Size;

		Buffer()
			: Data(nullptr), Size(0)
		{
		}

		Buffer(void* data, uint32_t size)
			: Data(data), Size(size)
		{
		}

		static Buffer Copy(const void* data, uint32_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}

		void Allocate(uint32_t size)
		{
			delete[] Data;
			Data = nullptr;

			if (size == 0)
				return;

			Data = new std::byte[size];
			Size = size;
		}

		void Release()
		{
			delete[] Data;
			Data = nullptr;
			Size = 0;
		}

		void ZeroInitialize()
		{
			if (Data)
				memset(Data, 0, Size);
		}

		template<typename T>
		T& Read(uint32_t offset = 0)
		{
			return *(T*)((byte*)Data + offset);
		}

		std::byte* ReadBytes(uint32_t size, uint32_t offset)
		{
			RP_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			std::byte* buffer = new std::byte[size];
			memcpy(buffer, (std::byte*)Data + offset, size);
			return buffer;
		}

		void Write(void* data, uint32_t size, uint32_t offset = 0)
		{
			RP_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			memcpy((std::byte*)Data + offset, data, size);
		}

		operator bool() const
		{
			return Data;
		}

		std::byte& operator[](int index)
		{
			return ((std::byte*)Data)[index];
		}

		std::byte operator[](int index) const
		{
			return ((std::byte*)Data)[index];
		}

		template<typename T>
		T* As()
		{
			return (T*)Data;
		}

		inline uint32_t GetSize() const { return Size; }
	};

}	//	END namespace RAPIER
