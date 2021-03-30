#include "drpch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DAGGer/Scene/Entity.h"
#include "ScriptWrappers.h"

namespace DAGGer
{

	std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

	extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name("DAGGer." #Type, s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			Dr_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

	static void InitComponentTypes()
	{
		Component_RegisterType(TagComponent);
		Component_RegisterType(TransformComponent);
		Component_RegisterType(ScriptComponent);
		Component_RegisterType(CameraComponent);
		Component_RegisterType(SpriteRendererComponent);
	}

	void ScriptEngineRegistry::RegisterAll()
	{
		InitComponentTypes();

		mono_add_internal_call("DAGGer.Entity::CreateComponent_Native", DAGGer::Script::DAGGer_Entity_CreateComponent);
		mono_add_internal_call("DAGGer.Entity::HasComponent_Native", DAGGer::Script::DAGGer_Entity_HasComponent);
		mono_add_internal_call("DAGGer.Entity::FindEntityByTag_Native", DAGGer::Script::DAGGer_Entity_FindEntityByTag);

		mono_add_internal_call("DAGGer.TransformComponent::GetTransform_Native", DAGGer::Script::DAGGer_TransformComponent_GetTransform);
		mono_add_internal_call("DAGGer.TransformComponent::SetTransform_Native", DAGGer::Script::DAGGer_TransformComponent_SetTransform);
		mono_add_internal_call("DAGGer.TransformComponent::GetTranslation_Native", DAGGer::Script::DAGGer_TransformComponent_GetTranslation);
		mono_add_internal_call("DAGGer.TransformComponent::SetTranslation_Native", DAGGer::Script::DAGGer_TransformComponent_SetTranslation);
		mono_add_internal_call("DAGGer.TransformComponent::GetRotation_Native", DAGGer::Script::DAGGer_TransformComponent_GetRotation);
		mono_add_internal_call("DAGGer.TransformComponent::SetRotation_Native", DAGGer::Script::DAGGer_TransformComponent_SetRotation);
		mono_add_internal_call("DAGGer.TransformComponent::GetScale_Native", DAGGer::Script::DAGGer_TransformComponent_GetScale);
		mono_add_internal_call("DAGGer.TransformComponent::SetScale_Native", DAGGer::Script::DAGGer_TransformComponent_SetScale);

		mono_add_internal_call("DAGGer.Input::IsKeyPressed_Native", DAGGer::Script::DAGGer_Input_IsKeyPressed);
		mono_add_internal_call("DAGGer.Input::IsMouseButtonPressed_Native", DAGGer::Script::DAGGer_Input_IsMouseButtonPressed);
		mono_add_internal_call("DAGGer.Input::GetMousePosition_Native", DAGGer::Script::DAGGer_Input_GetMousePosition);

		mono_add_internal_call("DAGGer.Texture2D::Constructor_Native", DAGGer::Script::DAGGer_Texture2D_Constructor);
		mono_add_internal_call("DAGGer.Texture2D::Destructor_Native", DAGGer::Script::DAGGer_Texture2D_Destructor);
		mono_add_internal_call("DAGGer.Texture2D::SetData_Native", DAGGer::Script::DAGGer_Texture2D_SetData);

	}

}	//	END namespace DAGGer
