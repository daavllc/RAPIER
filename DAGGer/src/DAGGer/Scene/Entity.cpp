/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the implementation of DAGGer entities
////////////////////////////////
#include "drpch.h"
#include "Entity.h"

namespace DAGGer
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

	Entity::~Entity()
	{

	}

}	//	END namespace DAGGer
