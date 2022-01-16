#pragma once

#include "rppch.h"

namespace RAPIER
{
	class PlatformUtils : public RefCounted
	{
	public:
		virtual std::string OpenFileDialog(const char* filter) = 0;
		virtual std::string SaveFileDialog(const char* filter) = 0;

		static Scope<PlatformUtils> Create();
	};
	
}	//	END namespace RAPIER

