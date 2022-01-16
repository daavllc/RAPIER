#pragma once

#include "Base.h"

#include <xhash>

namespace RAPIER
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID& other) = default;

		operator uint64_t () { return m_UUID; }
		operator const uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};

}	//	END namespace RAPIER

namespace std
{
	template <>
	struct hash<RAPIER::UUID>
	{
		std::size_t operator()(const RAPIER::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}	//	END namespace std
