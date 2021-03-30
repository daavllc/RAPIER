#pragma once

#include "DAGGer/Script/ScriptEngine.h"
#include "DAGGer/Core/Input.h"
#include "DAGGer/Renderer/Texture.h"

#include <glm/glm.hpp>

extern "C" {
	typedef struct _MonoString MonoString;
	typedef struct _MonoArray MonoArray;
}

namespace DAGGer::Script
{
	// Input
	bool DAGGer_Input_IsKeyPressed(KeyCode key);
	bool DAGGer_Input_IsMouseButtonPressed(MouseCode button);
	void DAGGer_Input_GetMousePosition(glm::vec2* outPosition);

	// Entity
	void DAGGer_Entity_CreateComponent(uint64_t entityID, void* type);
	bool DAGGer_Entity_HasComponent(uint64_t entityID, void* type);
	uint64_t DAGGer_Entity_FindEntityByTag(MonoString* tag);

	void DAGGer_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform);
	void DAGGer_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform);
	void DAGGer_TransformComponent_GetTranslation(uint64_t entityID, glm::vec3* outTranslation);
	void DAGGer_TransformComponent_SetTranslation(uint64_t entityID, glm::vec3* inTranslation);
	void DAGGer_TransformComponent_GetRotation(uint64_t entityID, glm::vec3* outRotation);
	void DAGGer_TransformComponent_SetRotation(uint64_t entityID, glm::vec3* inRotation);
	void DAGGer_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale);
	void DAGGer_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale);

	// Renderer
	// Texture2D
	void* DAGGer_Texture2D_Constructor(uint32_t width, uint32_t height);
	void DAGGer_Texture2D_Destructor(Ref<Texture2D>* _this);
	void DAGGer_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count);

}	//	END namespace DAGGer::Script
