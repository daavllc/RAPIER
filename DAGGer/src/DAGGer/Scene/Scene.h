/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the defintions for scenes
////////////////////////////////
#pragma once

#include "DAGGer/Core/UUID.h"
#include "DAGGer/Core/Timestep.h"
#include "DAGGer/Renderer/EditorCamera.h"

#include <entt.hpp>
//#include <glm/glm.hpp>

namespace DAGGer
{
	class Entity;
	using EntityMap = std::unordered_map<UUID, Entity>;

	class Scene : public RefCounted
	{
	public:
		Scene(const std::string& debugName = "Scene");
		~Scene();

		void Init();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		//	Runtime
		void OnRuntimeStart();
		void OnRuntimeStop();

		//void SetViewportSize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithID(UUID uuid, const std::string& name = "");
		void DestroyEntity(Entity entity);

		void DuplicateEntity(Entity entity);

		template<typename T>
		auto GetAllEntitiesWith() { return m_Registry.view<T>(); }
		Entity FindEntityByTag(const std::string& tag);

		Entity FindEntityByUUID(UUID id);
		const EntityMap& GetEntityMap() const { return m_EntityIDMap; }
		void CopyTo(Ref<Scene>& target);

		UUID GetUUID() const { return m_SceneID; }

		static Ref<Scene> GetScene(UUID uuid);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	protected:
		UUID m_SceneID;
		entt::entity m_SceneEntity;
		entt::registry m_Registry;

		std::string m_DebugName;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		EntityMap m_EntityIDMap;
		bool m_IsPlaying = false;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};	//	END class Scene

}	//	END namespace DAGGer
