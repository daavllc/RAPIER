#pragma once

#include "Scene.h"
#include "RAPIER/Core/UUID.h"
#include "Components.h"

#include <glm/glm.hpp>
#include <entt.hpp>


namespace RAPIER
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		~Entity() {};

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			RP_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			RP_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		const T& GetComponent() const
		{
			RP_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		const bool HasComponent() const
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename...T>
		bool HasAny()
		{
			return m_Scene->m_Registry.any<T...>(m_EntityHandle);
		}

		template<typename...T>
		bool HasAny() const
		{
			return m_Scene->m_Registry.any<T...>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			RP_CORE_ASSERT(HasComponent<T>(), "Entity cannot remove non-existing component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		TransformComponent& Transform() { return m_Scene->m_Registry.get<TransformComponent>(m_EntityHandle); }
		const glm::mat4& Transform() const { return m_Scene->m_Registry.get<TransformComponent>(m_EntityHandle).GetTransform(); }

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator==(const Entity& other) const { return m_EntityHandle == other.m_EntityHandle && other.m_Scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }

		Entity GetParent()
		{
			if (!HasParent())
				return {};
			return m_Scene->FindEntityByUUID(GetParentUUID());
		}

		void SetParent(Entity parent)
		{
			SetParentUUID(parent.GetUUID());
			parent.Children().emplace_back(GetUUID());
		}

		void SetParentUUID(UUID parent) { GetComponent<RelationshipComponent>().ParentHandle = parent; }
		UUID GetParentUUID() const { return GetComponent<RelationshipComponent>().ParentHandle; }
		std::vector<UUID>& Children() { return GetComponent<RelationshipComponent>().Children; }

		bool RemoveChild(Entity child)
		{
			UUID childId = child.GetUUID();
			std::vector<UUID>& children = Children();
			auto it = std::find(children.begin(), children.end(), childId);
			if (it != children.end())
			{
				children.erase(it);
				return true;
			}

			return false;
		}

		bool IsAncesterOf(Entity entity)
		{
			const auto& children = Children();

			if (children.size() == 0)
				return false;

			for (UUID child : children)
			{
				if (child == entity.GetUUID())
					return true;
			}

			for (UUID child : children)
			{
				if (m_Scene->FindEntityByUUID(child).IsAncesterOf(entity))
					return true;
			}

			return false;
		}
		
		bool IsDescendantOf(Entity entity)
		{
			return entity.IsAncesterOf(*this);
		}

		bool HasParent() { return m_Scene->FindEntityByUUID(GetParentUUID()); }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }
		
		UUID GetSceneUUID() { return m_Scene->GetUUID(); }
	private:
		Entity(const std::string& name);
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;

		friend class Scene;
		friend class SceneSerializer;
		friend class ScriptEngine;
	};

}	//	END namespace RAPIER
