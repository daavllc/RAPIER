#include "rppch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RAPIER/Scene/Entity.h"
#include "ScriptWrappers.h"

namespace RAPIER
{
	std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

	extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name("RAPIER." #Type, s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			RP_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

	static void InitComponentTypes()
	{
		Component_RegisterType(ScriptComponent);

		Component_RegisterType(TagComponent);
		Component_RegisterType(TransformComponent);
		Component_RegisterType(SpriteRendererComponent);
		Component_RegisterType(CircleRendererComponent);
		Component_RegisterType(CameraComponent);
		Component_RegisterType(RigidBody2DComponent);
		Component_RegisterType(BoxCollider2DComponent);
		Component_RegisterType(CircleCollider2DComponent);
	}

	void ScriptEngineRegistry::RegisterAll()
	{
		InitComponentTypes();

		//  -----------------------------  SCENE  -----------------------------  //
		mono_add_internal_call("RAPIER.Scene::GetEntities", RAPIER::Script::RAPIER_Scene_GetEntities);

		//  -----------------------------  INPUT  -----------------------------  //
		mono_add_internal_call("RAPIER.Input::IsKeyPressed_Native", RAPIER::Script::RAPIER_Input_IsKeyPressed);
		mono_add_internal_call("RAPIER.Input::IsMouseButtonPressed_Native", RAPIER::Script::RAPIER_Input_IsMouseButtonPressed);
		mono_add_internal_call("RAPIER.Input::GetMousePosition_Native", RAPIER::Script::RAPIER_Input_GetMousePosition);
		mono_add_internal_call("RAPIER.Input::IsControllerPresent_Native", RAPIER::Script::RAPIER_Input_IsControllerPresent);
		mono_add_internal_call("RAPIER.Input::GetConnectedControllerIDs_Native", RAPIER::Script::RAPIER_Input_GetConnectedControllerIDs);
		mono_add_internal_call("RAPIER.Input::GetControllerName_Native", RAPIER::Script::RAPIER_Input_GetControllerName);
		mono_add_internal_call("RAPIER.Input::IsControllerButtonPressed_Native", RAPIER::Script::RAPIER_Input_IsControllerButtonPressed);
		mono_add_internal_call("RAPIER.Input::GetControllerAxis_Native", RAPIER::Script::RAPIER_Input_GetControllerAxis);
		mono_add_internal_call("RAPIER.Input::GetControllerHat_Native", RAPIER::Script::RAPIER_Input_GetControllerHat);

		//  -----------------------------  ENTITY  -----------------------------  //
		mono_add_internal_call("RAPIER.Entity::CreateComponent_Native", RAPIER::Script::RAPIER_Entity_CreateComponent);
		mono_add_internal_call("RAPIER.Entity::CreateEntity_Native", RAPIER::Script::RAPIER_Entity_CreateEntity);
		mono_add_internal_call("RAPIER.Entity::Instatiate_Native", RAPIER::Script::RAPIER_Entity_Instantiate);
		mono_add_internal_call("RAPIER.Entity::InstansiateWithTranslation_Native", RAPIER::Script::RAPIER_Entity_InstantiateWithTranslation);
		mono_add_internal_call("RAPIER.Entity::InstansiateWithTransform_Native", RAPIER::Script::RAPIER_Entity_InstantiateWithTransform);
		mono_add_internal_call("RAPIER.Entity::DestroyEntity_Native", RAPIER::Script::RAPIER_Entity_DestroyEntity);
		mono_add_internal_call("RAPIER.Entity::HasComponent_Native", RAPIER::Script::RAPIER_Entity_HasComponent);
		mono_add_internal_call("RAPIER.Entity::FindEntityByTag_Native", RAPIER::Script::RAPIER_Entity_FindEntityByTag);

		mono_add_internal_call("RAPIER.Tagcomponent:GetTag_Native", RAPIER::Script::RAPIER_TagComponent_GetTag);
		mono_add_internal_call("RAPIER.Tagcomponent:SetTag_Native", RAPIER::Script::RAPIER_TagComponent_SetTag);

		mono_add_internal_call("RAPIER.TransformComponent::GetTransform_Native", RAPIER::Script::RAPIER_TransformComponent_GetTransform);
		mono_add_internal_call("RAPIER.TransformComponent::SetTransform_Native", RAPIER::Script::RAPIER_TransformComponent_SetTransform);

		mono_add_internal_call("RAPIER.BoxColliderComponent::GetSize_Native", RAPIER::Script::RAPIER_BoxCollider2DComponent_GetSize);
		mono_add_internal_call("RAPIER.BoxColliderComponent::SetSize_Native", RAPIER::Script::RAPIER_BoxCollider2DComponent_SetSize);
		mono_add_internal_call("RAPIER.BoxColliderComponent::GetOffset_Native", RAPIER::Script::RAPIER_BoxCollider2DComponent_GetOffset);
		mono_add_internal_call("RAPIER.BoxColliderComponent::SetOffset_Native", RAPIER::Script::RAPIER_BoxCollider2DComponent_SetOffset);

		mono_add_internal_call("RAPIER.CircleColliderComponent::GetRadius_Native", RAPIER::Script::RAPIER_CircleCollider2DComponent_GetRadius);
		mono_add_internal_call("RAPIER.CircleColliderComponent::SetRadius_Native", RAPIER::Script::RAPIER_CircleCollider2DComponent_SetRadius);
		mono_add_internal_call("RAPIER.CircleColliderComponent::GetOffset_Native", RAPIER::Script::RAPIER_CircleCollider2DComponent_GetOffset);
		mono_add_internal_call("RAPIER.CircleColliderComponent::SetOffset_Native", RAPIER::Script::RAPIER_CircleCollider2DComponent_SetOffset);
	}
}	//	END namespace RAPIER
