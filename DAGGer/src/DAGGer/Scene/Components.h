/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file contains the structs for components
////////////////////////////////
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "DAGGer/Core/UUID.h"
#include "DAGGer/Scene/SceneCamera.h"

namespace DAGGer
{
	//  -----------------------------  ID COMPONENT  -----------------------------  //
	struct IDComponent
	{
		UUID ID = 0;
	};
	//  -----------------------------  TAG COMPONENT  -----------------------------  //
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

	};
	//  -----------------------------  TRANSFORM COMPONENT  -----------------------------  //
	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation    = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale       = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
	//  -----------------------------  SPRITE COMPONENT  -----------------------------  //
	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
		//Ref<MaterialInstance>

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};
	//  -----------------------------  CAMERA COMPONENT  -----------------------------  //
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;	//	TODO: move to scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
	//  -----------------------------  NATIVE SCRIPT COMPONENT  -----------------------------  //
	struct NativeScriptComponent
	{
		
	};

}	//	END namespace DAGGer
