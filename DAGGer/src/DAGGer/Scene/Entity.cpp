#include "drpch.h"
#include "Entity.h"

namespace DAGGer
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}	//	END namespace DAGGer