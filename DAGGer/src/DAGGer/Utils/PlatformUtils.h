/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation for Platform specific utilities
////////////////////////////////
#pragma once

#include <string>

namespace DAGGer
{
	class FileDialogs
	{
	public:
		//	Returns empty string if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}	//	END namespace DAGGer
