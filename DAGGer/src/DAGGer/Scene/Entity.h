/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the definitions for DAGGer entities
////////////////////////////////
#pragma once

#include <glm/glm.hpp>
#include <entt.hpp>

#include "Scene.h"
#include "Components.h"

//#include <entt.hpp>

namespace DAGGer
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			Dr_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			Dr_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			Dr_CORE_ASSERT(HasComponent<T>(), "Entity cannot remove non-existing component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator==(const Entity& other) const { return m_EntityHandle == other.m_EntityHandle && other.m_Scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }

		const UUID GetUUID() { return GetComponent<DAGGer::IDComponent>().ID; };
		const UUID GetSceneUUID() const { return m_Scene->GetUUID(); };
	private:
		Entity(const std::string& name);
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;	//	12 Bytes on x64

		friend class Scene;
		friend class SceneSerializer;
		friend class ScriptEngine;
	};

}	//	END namespace DAGGer
