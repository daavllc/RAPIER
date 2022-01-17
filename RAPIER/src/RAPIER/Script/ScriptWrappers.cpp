#include "rppch.h"
#include "ScriptWrappers.h"

#include "RAPIER/Scene/Scene.h"
#include "RAPIER/Scene/Entity.h"
#include "RAPIER/Core/Application.h"
#include "RAPIER/Script/ScriptEngine.h"

#include "RAPIER/Debug/Profiler.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/common.hpp>

#include <mono/jit/jit.h>

#include <box2d/box2d.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace RAPIER
{
	extern std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	extern std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;
}	//	END namespace RAPIER

namespace RAPIER::Script
{
	static inline auto GetEntity(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		RP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		RP_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		return entityMap.at(entityID);
	};

	//  -----------------------------  SCENE  -----------------------------  //
	MonoArray* RAPIER_Scene_GetEntities()
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		RP_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();

		MonoArray* result = mono_array_new(mono_domain_get(), ScriptEngine::GetCoreClass("RAPIER.Entity"), entityMap.size());

		uint32_t index = 0;
		for (auto& [id, entity] : entityMap)
		{
			UUID uuid = id;
			void* data[] = { &uuid };
			MonoObject* obj = ScriptEngine::Construct("RAPIER.Entity:.ctor(ulong)", true, data);
			mono_array_set(result, MonoObject*, index++, obj);
		}

		return result;
	}

	
	//  -----------------------------  INPUT  -----------------------------  //
	bool RAPIER_Input_IsKeyPressed(KeyCode key)
	{
		return Input::IsKeyPressed(key);
	}

	bool RAPIER_Input_IsMouseButtonPressed(MouseCode button)
	{
		bool wasPressed = Input::IsMouseButtonPressed(button);

		bool enableImGui = Application::Get().GetSpecification().EnableImGui;
		if (wasPressed && enableImGui && GImGui->HoveredWindow != nullptr)
		{
			// Make sure we're in the viewport panel
			ImGuiWindow* viewportWindow = ImGui::FindWindowByName("Viewport");
			if (viewportWindow != nullptr)
				wasPressed = GImGui->HoveredWindow->ID == viewportWindow->ID;
		}

		return wasPressed;
	}

	void RAPIER_Input_GetMousePosition(glm::vec2* outPosition)
	{
		auto [x, y] = Input::GetMousePosition();
		*outPosition = { x, y };
	}

	void RAPIER_Input_SetCursorMode(CursorMode mode)
	{
		Input::SetCursorMode(mode);
	}

	CursorMode RAPIER_Input_GetCursorMode()
	{
		return Input::GetCursorMode();
	}

	bool RAPIER_Input_IsControllerPresent(int id)
	{
		return Input::IsControllerPresent(id);
	}

	MonoArray* RAPIER_Input_GetConnectedControllerIDs()
	{
		std::vector<int> ids = Input::GetConnectedControllerIDs();

		MonoArray* result = mono_array_new(mono_domain_get(), mono_get_int32_class(), ids.size());
		for (size_t i = 0; i < ids.size(); i++)
			mono_array_set(result, int, i, ids[i]);

		return result;
	}

	MonoString* RAPIER_Input_GetControllerName(int id)
	{
		auto name = Input::GetControllerName(id);
		if (name.empty())
			return mono_string_new(mono_domain_get(), "");

		return mono_string_new(mono_domain_get(), &name.front());
	}

	bool RAPIER_Input_IsControllerButtonPressed(int id, int button)
	{
		return Input::IsControllerButtonPressed(id, button);
	}

	float RAPIER_Input_GetControllerAxis(int id, int axis)
	{
		return Input::GetControllerAxis(id, axis);
	}

	uint8_t RAPIER_Input_GetControllerHat(int id, int hat)
	{
		return Input::GetControllerHat(id, hat);
	}



	//  -----------------------------  ENTITY  -----------------------------  //
	uint64_t RAPIER_Entity_CreateEntity(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		return scene->CreateEntity("Unnamed from C#").GetUUID();
	}

	uint64_t RAPIER_Entity_Instantiate(uint64_t entityID, uint64_t prefabID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();

		RP_CORE_ASSERT(false, "Not implemented");
		return 0;
	}

	uint64_t RAPIER_Entity_InstantiateWithTranslation(uint64_t entityID, uint64_t prefabID, glm::vec3* inTranslation)
	{
		return RAPIER_Entity_InstantiateWithTransform(entityID, prefabID, inTranslation, nullptr, nullptr);
	}

	uint64_t RAPIER_Entity_InstantiateWithTransform(uint64_t entityID, uint64_t prefabID, glm::vec3* inTranslation, glm::vec3* inRotation, glm::vec3* inScale)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		RP_CORE_ASSERT(false, "Not implemented");
		return 0;
	}

	void RAPIER_Entity_DestroyEntity(uint64_t entityID)
	{
		auto entity = GetEntity(entityID);
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		RP_CORE_ASSERT(false, "Not implemented");
	}

	void RAPIER_Entity_CreateComponent(uint64_t entityID, void* type)
	{
		auto entity = GetEntity(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		s_CreateComponentFuncs[monoType](entity);
	}

	bool RAPIER_Entity_HasComponent(uint64_t entityID, void* type)
	{
		auto entity = GetEntity(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		bool result = s_HasComponentFuncs[monoType](entity);
		return result;
	}

	uint64_t RAPIER_Entity_FindEntityByTag(MonoString* tag)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		RP_CORE_ASSERT(scene, "No active scene!");

		Entity entity = scene->FindEntityByTag(mono_string_to_utf8(tag));
		if (entity)
			return entity.GetComponent<IDComponent>().ID;

		return 0;
	}

	MonoString* RAPIER_TagComponent_GetTag(uint64_t entityID)
	{
		auto entity = GetEntity(entityID);
		auto& tagComponent = entity.GetComponent<TagComponent>();
		return mono_string_new(mono_domain_get(), tagComponent.Tag.c_str());
	}

	void RAPIER_TagComponent_SetTag(uint64_t entityID, MonoString* tag)
	{
		auto entity = GetEntity(entityID);
		auto& tagComponent = entity.GetComponent<TagComponent>();
		tagComponent.Tag = mono_string_to_utf8(tag);
	}

	void RAPIER_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform)
	{
		auto entity = GetEntity(entityID);
		*outTransform = entity.GetComponent<TransformComponent>();
	}

	void RAPIER_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform)
	{
		auto entity = GetEntity(entityID);
		entity.GetComponent<TransformComponent>() = *inTransform;
	}

	void RAPIER_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale)
	{
		auto entity = GetEntity(entityID);
		*outScale = entity.GetComponent<TransformComponent>().Scale;
	}

	void RAPIER_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale)
	{
		auto entity = GetEntity(entityID);
		entity.GetComponent<TransformComponent>().Scale = *inScale;
	}

	void RAPIER_BoxCollider2DComponent_GetSize(uint64_t entityID, glm::vec2* outSize)
	{
		auto entity = GetEntity(entityID);
		RP_CORE_ASSERT(entity.HasComponent<BoxColliderComponent>());
		auto& component = entity.GetComponent<BoxCollider2DComponent>();
		*outSize = component.Size;
	}

	void RAPIER_BoxCollider2DComponent_SetSize(uint64_t entityID, glm::vec2* inSize) {}

	void RAPIER_BoxCollider2DComponent_GetOffset(uint64_t entityID, glm::vec2* outOffset)
	{
		auto entity = GetEntity(entityID);
		RP_CORE_ASSERT(entity.HasComponent<BoxColliderComponent>());
		auto& component = entity.GetComponent<BoxCollider2DComponent>();
		*outOffset = component.Offset;
	}

	void RAPIER_BoxCollider2DComponent_SetOffset(uint64_t entityID, glm::vec2* inOffset) {}


	void RAPIER_CircleCollider2DComponent_GetRadius(uint64_t entityID, float* outSize)
	{
		auto entity = GetEntity(entityID);
		RP_CORE_ASSERT(entity.HasComponent<BoxColliderComponent>());
		auto& component = entity.GetComponent<CircleCollider2DComponent>();
		*outSize = component.Radius;
	}

	void RAPIER_CircleCollider2DComponent_SetRadius(uint64_t entityID, float* inSize) {}

	void RAPIER_CircleCollider2DComponent_GetOffset(uint64_t entityID, glm::vec2* outOffset)
	{
		auto entity = GetEntity(entityID);
		RP_CORE_ASSERT(entity.HasComponent<BoxColliderComponent>());
		auto& component = entity.GetComponent<CircleCollider2DComponent>();
		*outOffset = component.Offset;
	}

	void RAPIER_CircleCollider2DComponent_SetOffset(uint64_t entityID, glm::vec2* inOffset) {}

	MonoObject* RAPIER_ScriptComponent_GetInstance(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		RP_CORE_ASSERT(scene, "No active scene!");
		return ScriptEngine::GetEntityInstanceData(scene->GetUUID(), entityID).Instance.GetInstance();
	}

	void RAPIER_Log_LogMessage(LogLevel level, MonoString* message)
	{
		RP_PROFILE_FUNC();

		char* msg = mono_string_to_utf8(message);
		switch (level)
		{
		case LogLevel::Trace:
			RP_CONSOLE_TRACE(msg);
			break;
		case LogLevel::Info:
			RP_CONSOLE_INFO(msg);
			break;
		case LogLevel::Warn:
			RP_CONSOLE_WARN(msg);
			break;
		case LogLevel::Error:
			RP_CONSOLE_ERROR(msg);
			break;
		case LogLevel::Critical:
			RP_CONSOLE_CRITICAL(msg);
			break;
		}

	}


}	// END namespace RAPIER::Script
