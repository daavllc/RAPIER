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