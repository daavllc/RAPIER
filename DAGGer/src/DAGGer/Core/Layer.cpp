/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the implementation for layers
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Core/Layer.h"

namespace DAGGer
{
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

}	//	END namespace DAGGer