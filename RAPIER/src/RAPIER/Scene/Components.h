#pragma once

#include "RAPIER/Core/UUID.h"
#include "RAPIER/Scene/SceneCamera.h"
#include "RAPIER/Renderer/Texture.h"

#include "RAPIER/Script/ScriptModuleField.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

/*	When adding a new component: TODO: make this not stupid
* Add here
* Update SceneHierarchyPanel
* Update SceneSerializer
* Update Scene::OnComponentAdded
* Add to Scene::DuplicateEntity
* Add to Scene::CopyTo
* To access from C#
  * Add to Script::ScriptEngineRegistry.cpp
  * Add to Script::ScriptWrappers.h/.cpp
  * Add Implementation in Components.cs
*/

/* COMPONENTS
IDComponent
TagComponent
RelationshipComponent
TransformComponent
SpriteRendererComponent
CircleRendererComponent
CameraComponent
NativeScriptComponent
ScriptComponent
RigidBody2DComponent
BoxCollider2DComponent
CircleCollider2DComponent
*/

namespace RAPIER
{
	//  -----------------------------  ID COMPONENT  -----------------------------  //
	struct IDComponent
	{
		UUID ID = 0;

		IDComponent() = default;
		IDComponent(const IDComponent& other) = default;
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
	//  -----------------------------  RELATIONSHIP COMPONENT  -----------------------------  //
	struct RelationshipComponent
	{
		UUID ParentHandle = 0;
		std::vector<UUID> Children;

		RelationshipComponent() = default;
		RelationshipComponent(const RelationshipComponent& other) = default;
		RelationshipComponent(UUID parent)
			: ParentHandle(parent) {}
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
	//  -----------------------------  SPRITE RENDERER COMPONENT  -----------------------------  //
	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};
	//  -----------------------------  CIRCLE RENDERER COMPONENT  -----------------------------  //
	struct CircleRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		float Radius = 0.5f;
		float Thickness = 1.0f;
		float Fade = 0.005f;

		CircleRendererComponent() = default;
		CircleRendererComponent(const CircleRendererComponent&) = default;
		CircleRendererComponent(const glm::vec4& color)
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
	class ScriptableEntity;	//	Forward declaration
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
	//  -----------------------------  SCRIPT COMPONENT  -----------------------------  //
	struct ScriptComponent
	{
		std::string ModuleName;
		ScriptModuleFieldMap ModuleFieldMap;

		ScriptComponent() = default;
		ScriptComponent(const ScriptComponent& other) = default;
		ScriptComponent(const std::string& moduleName)
			: ModuleName(moduleName) {}
	};

	//	Physics

	//  -----------------------------  RIGID BODY 2D COMPONENT  -----------------------------  //
	struct RigidBody2DComponent
	{
		enum class BodyType { Static = 0, Dynamic, Kinematic};
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;

		//	Storage for runtime
		void* RuntimeBody = nullptr;

		RigidBody2DComponent() = default;
		RigidBody2DComponent(const RigidBody2DComponent& other) = default;
	};
	//  -----------------------------  BOX COLLIDER 2D COMPONENT  -----------------------------  //
	struct BoxCollider2DComponent
	{
		glm::vec2 Offset = { 0.0f, 0.0f };
		glm::vec2 Size   = { 0.5f, 0.5f };

		// TODO: move into physics material
		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f; // Threshold when objects stop bouncing

		//	Storage for runtime
		void* RuntimeFixture = nullptr;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent& other) = default;
	};
	//  -----------------------------  CIRCLE COLLIDER 2D COMPONENT  -----------------------------  //
	struct CircleCollider2DComponent
	{
		glm::vec2 Offset = { 0.0f,0.0f };
		float Radius = 0.5f;

		float Density = 1.0f;
		float Friction = 1.0f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f; // Threshold when objects stop bouncing

		// Storage for runtime
		void* RuntimeFixture = nullptr;

		CircleCollider2DComponent() = default;
		CircleCollider2DComponent(const CircleCollider2DComponent& other) = default;
	};


}	//	END namespace RAPIER
