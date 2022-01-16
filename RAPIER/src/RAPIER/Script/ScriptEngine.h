#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Timestep.h"

#include <string>

#include "RAPIER/Scene/Components.h"
#include "RAPIER/Scene/Entity.h"

#include "ScriptModuleField.h"

extern "C" {
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoClass MonoClass;
}

namespace RAPIER
{
	struct EntityScriptClass;
	struct EntityInstance
	{
		EntityScriptClass* ScriptClass = nullptr;

		uint32_t Handle = 0;
		Scene* SceneInstance = nullptr;

		MonoObject* GetInstance();
		bool IsRuntimeAvailable() const;
	};

	struct EntityInstanceData
	{
		EntityInstance Instance;
		ScriptModuleFieldMap ModuleFieldMap;
	};

	using EntityInstanceMap = std::unordered_map<UUID, std::unordered_map<UUID, EntityInstanceData>>;

	class ScriptEngine
	{
	public:
		static void Init(const std::string& assemblyPath);
		static void Shutdown();

		static void OnSceneDestruct(UUID sceneID);

		static bool LoadRapierRuntimeAssembly(const std::string& path);
		static bool ScriptEngine::LoadAppAssembly(const std::string& path);
		static bool ReloadAssembly(const std::string& path);

		static void SetSceneContext(const Ref<Scene>& scene);
		static const Ref<Scene>& GetCurrentSceneContext();

		static void CopyEntityScriptData(UUID dst, UUID src);

		static void OnCreateEntity(Entity entity);
		static void OnUpdateEntity(Entity entity, Timestep ts);
		static void OnPhysicsUpdateEntity(Entity entity, float fixedTimeStep);

		static void OnCollision2DBegin(Entity entity, Entity other);
		static void OnCollision2DEnd(Entity entity, Entity other);
		static void OnCollisionBegin(Entity entity, Entity other);
		static void OnCollisionEnd(Entity entity, Entity other);
		static void OnTriggerBegin(Entity entity, Entity other);
		static void OnTriggerEnd(Entity entity, Entity other);
		static void OnJointBreak(Entity entity, const glm::vec3& linearForce, const glm::vec3& angularForce);

		static MonoObject* Construct(const std::string& fullName, bool callConstructor = true, void** parameters = nullptr);
		static MonoClass* GetCoreClass(const std::string& fullName);

		static bool IsEntityModuleValid(Entity entity);

		static void OnScriptComponentDestroyed(UUID sceneID, UUID entityID);

		static bool ModuleExists(const std::string& moduleName);
		static std::string StripNamespace(const std::string& nameSpace, const std::string& moduleName);

		static void InitScriptEntity(Entity entity);
		static void ShutdownScriptEntity(Entity entity, const std::string& moduleName);
		static void InstantiateEntityClass(Entity entity);

		static EntityInstanceMap& GetEntityInstanceMap();
		static EntityInstanceData& GetEntityInstanceData(UUID sceneID, UUID entityID);

		// Debug
		static void OnImGuiRender();

	private:
		static std::unordered_map<std::string, std::string> s_PublicFieldStringValue;

		friend PublicField;

	};

}	//	END namespace RAPIER
