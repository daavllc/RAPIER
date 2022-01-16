#pragma once

#include "RAPIER/Core/Input.h"
#include "RAPIER/Scene/Components.h"

#include <glm/glm.hpp>

extern "C" {
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoString MonoString;
	typedef struct _MonoArray MonoArray;
}

namespace RAPIER::Script
{
	//  -----------------------------  SCENE  -----------------------------  //
	MonoArray* RAPIER_Scene_GetEntities();

	//  -----------------------------  INPUT  -----------------------------  //
	bool RAPIER_Input_IsKeyPressed(KeyCode key);
	bool RAPIER_Input_IsMouseButtonPressed(MouseCode button);
	void RAPIER_Input_GetMousePosition(glm::vec2* outPosition);
	void RAPIER_Input_SetCursorMode(CursorMode mode);
	CursorMode RAPIER_Input_GetCursorMode();
	bool RAPIER_Input_IsControllerPresent(int id);
	MonoArray* RAPIER_Input_GetConnectedControllerIDs();
	MonoString* RAPIER_Input_GetControllerName(int id);
	bool RAPIER_Input_IsControllerButtonPressed(int id, int button);
	float RAPIER_Input_GetControllerAxis(int id, int axis);
	uint8_t RAPIER_Input_GetControllerHat(int id, int hat);


	//  -----------------------------  ENTITY  -----------------------------  //
	uint64_t RAPIER_Entity_CreateEntity(uint64_t entityID);
	uint64_t RAPIER_Entity_Instantiate(uint64_t entityID, uint64_t prefabID);
	uint64_t RAPIER_Entity_InstantiateWithTranslation(uint64_t entityID, uint64_t prefabID, glm::vec3* inTranslation);
	uint64_t RAPIER_Entity_InstantiateWithTransform(uint64_t entityID, uint64_t prefabID, glm::vec3* inTranslation, glm::vec3* inRotation, glm::vec3* inScale);
	void RAPIER_Entity_DestroyEntity(uint64_t entityID);
	void RAPIER_Entity_CreateComponent(uint64_t entityID, void* type);
	bool RAPIER_Entity_HasComponent(uint64_t entityID, void* type);
	uint64_t RAPIER_Entity_FindEntityByTag(MonoString* tag);

	MonoString* RAPIER_TagComponent_GetTag(uint64_t entityID);
	void RAPIER_TagComponent_SetTag(uint64_t entityID, MonoString* tag);

	void RAPIER_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform);
	void RAPIER_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform);

	void RAPIER_BoxCollider2DComponent_GetSize(uint64_t entityID, glm::vec2* outSize);
	void RAPIER_BoxCollider2DComponent_SetSize(uint64_t entityID, glm::vec2* inSize);
	void RAPIER_BoxCollider2DComponent_GetOffset(uint64_t entityID, glm::vec2* outOffset);
	void RAPIER_BoxCollider2DComponent_SetOffset(uint64_t entityID, glm::vec2* inOffset);

	void RAPIER_CircleCollider2DComponent_GetRadius(uint64_t entityID, float* outSize);
	void RAPIER_CircleCollider2DComponent_SetRadius(uint64_t entityID, float* inSize);
	void RAPIER_CircleCollider2DComponent_GetOffset(uint64_t entityID, glm::vec2* outOffset);
	void RAPIER_CircleCollider2DComponent_SetOffset(uint64_t entityID, glm::vec2* inOffset);

	MonoObject* RAPIER_ScriptComponent_GetInstance(uint64_t entityID);

	enum class LogLevel : int32_t
	{
		Trace = BIT(0),
		Info = BIT(1),
		Warn = BIT(2),
		Error = BIT(3),
		Critical = BIT(4)
	};

	void RAPIER_Log_LogMessage(LogLevel level, MonoString* message);


}	// end namespace RAPIER::Script
