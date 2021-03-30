#include "drpch.h"
#include "ScriptWrappers.h"


#include "DAGGer/Scene/Scene.h"
#include "DAGGer/Scene/Entity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/common.hpp>

#include <mono/jit/jit.h>

namespace DAGGer {
	extern std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	extern std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;
}

namespace DAGGer::Script
{
	////////////////////////////////////////////////////////////////
	// Input ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	bool DAGGer_Input_IsKeyPressed(KeyCode key)
	{
		return Input::IsKeyPressed(key);
	}

	bool DAGGer_Input_IsMouseButtonPressed(MouseCode button)
	{
		return Input::IsMouseButtonPressed(button);
	}

	void DAGGer_Input_GetMousePosition(glm::vec2* outPosition)
	{
		auto [x, y] = Input::GetMousePosition();
		*outPosition = { x, y };
	}

	////////////////////////////////////////////////////////////////
	// Entity //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	void DAGGer_Entity_CreateComponent(uint64_t entityID, void* type)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		s_CreateComponentFuncs[monoType](entity);
	}

	bool DAGGer_Entity_HasComponent(uint64_t entityID, void* type)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		bool result = s_HasComponentFuncs[monoType](entity);
		return result;
	}

	uint64_t DAGGer_Entity_FindEntityByTag(MonoString* tag)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");

		Entity entity = scene->FindEntityByTag(mono_string_to_utf8(tag));
		if (entity)
			return entity.GetComponent<IDComponent>().ID;
		
		return 0;
	}

	void DAGGer_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outTransform = entity.GetComponent<TransformComponent>();
	}

	void DAGGer_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>() = *inTransform;
	}

	void DAGGer_TransformComponent_GetTranslation(uint64_t entityID, glm::vec3* outTranslation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	void DAGGer_TransformComponent_SetTranslation(uint64_t entityID, glm::vec3* inTranslation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>().Translation = *inTranslation;
	}

	void DAGGer_TransformComponent_GetRotation(uint64_t entityID, glm::vec3* outRotation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outRotation = entity.GetComponent<TransformComponent>().Rotation;
	}

	void DAGGer_TransformComponent_SetRotation(uint64_t entityID, glm::vec3* inRotation)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>().Rotation = *inRotation;
	}

	void DAGGer_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		*outScale = entity.GetComponent<TransformComponent>().Scale;
	}

	void DAGGer_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		Dr_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		Dr_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		entity.GetComponent<TransformComponent>().Scale = *inScale;
	}

	void* DAGGer_Texture2D_Constructor(uint32_t width, uint32_t height)
	{
		auto result = Texture2D::Create(width, height);
		return new Ref<Texture2D>(result);
	}

	void DAGGer_Texture2D_Destructor(Ref<Texture2D>* _this)
	{
		delete _this;
	}

	void DAGGer_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count)
	{
		Ref<Texture2D>& instance = *_this;

		uint32_t dataSize = count * sizeof(glm::vec4) / 4;
	}

}	//	END namespace DAGGer::Script
