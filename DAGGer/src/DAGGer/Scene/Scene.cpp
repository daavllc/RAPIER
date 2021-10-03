/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the implementation for scenes
////////////////////////////////
#include "drpch.h"
#include "Scene.h"

#include "Components.h"
#include "ScriptableEntity.h"
#include "DAGGer/Renderer/Renderer2D.h"

#include "Entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//	Box2D
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>

namespace DAGGer
{
	static b2BodyType RigidBody2DTypeToBox2DBody(RigidBody2DComponent::BodyType bodyType)
	{
		switch (bodyType)
		{
			case RigidBody2DComponent::BodyType::Static:    return b2_staticBody;
			case RigidBody2DComponent::BodyType::Dynamic:   return b2_dynamicBody;
			case RigidBody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
		}

		Dr_CORE_ASSERT(false, "Unknown body type!");
		return b2_staticBody;
	}

	static const std::string DefaultEntityName = "Entity";

	std::unordered_map<UUID, Scene*> s_ActiveScenes;

	struct SceneComponent
	{
		UUID ID = 0;
	};

	Scene::Scene(const std::string& debugName)
		: m_DebugName(debugName)
	{
		//m_SceneEntity = m_Registry.create();
		//m_Registry.emplace<SceneComponent>(m_SceneEntity, m_SceneID);
		//
		//s_ActiveScenes[m_SceneID] = this;

		Init();
	}

	Scene::~Scene()
	{
		m_Registry.clear();
		s_ActiveScenes.erase(m_SceneID);
	}

	void Scene::Init()
	{

	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		Dr_PROFILE_FUNCTION();

		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				nsc.Instance->OnUpdate(ts);
			});
		}

		//	Physics
		{
			const int32_t velocityIterations = 6;	//	TODO: EXPOSE TO EDITOR
			const int32_t positionIterations = 2;	//	TODO: EXPOSE TO EDITOR
			m_PhysicsWorld->Step(ts, velocityIterations, positionIterations);

			//	Retrieve transfrom from Box2D
			auto view = m_Registry.view<RigidBody2DComponent>();
			for (auto e : view)
			{
				Entity entity = { e, this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rb2d = entity.GetComponent<RigidBody2DComponent>();

				//b2Body* body = m_EntityBox2DBodyMap.at(entityID)
				b2Body* body = (b2Body*)rb2d.RuntimeBody;
				const auto& position = body->GetPosition();
				transform.Translation.x = position.x;
				transform.Translation.y = position.y;
				transform.Rotation.z = body->GetAngle();
			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			Dr_PROFILE_FUNCTION();

			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Dr_PROFILE_FUNCTION();

			Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Dr_PROFILE_FUNCTION();

		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnRuntimeStart()
	{
		{	//	Initialize Scripts
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}
			});
		}
		m_PhysicsWorld = new b2World({ 0.0f, -9.8f });
		auto view = m_Registry.view<RigidBody2DComponent>();
		for (auto e : view)
		{
			Entity entity = { e, this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<RigidBody2DComponent>();

			b2BodyDef bodyDef;
			bodyDef.type = RigidBody2DTypeToBox2DBody(rb2d.Type);
			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
			bodyDef.angle = transform.Rotation.z;

			b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
			body->SetFixedRotation(rb2d.FixedRotation);
			rb2d.RuntimeBody = body;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();

				b2PolygonShape boxShape;
				boxShape.SetAsBox(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &boxShape;
				fixtureDef.density              = bc2d.Density;
				fixtureDef.friction             = bc2d.Friction;
				fixtureDef.restitution          = bc2d.Restitution;
				fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}
			if (entity.HasComponent<CircleCollider2DComponent>())
			{
				auto& cc2d = entity.GetComponent<CircleCollider2DComponent>();

				b2CircleShape circleShape;
				circleShape.m_radius = transform.Scale.x * cc2d.Radius;

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &circleShape;
				fixtureDef.density = cc2d.Density;
				fixtureDef.friction = cc2d.Friction;
				fixtureDef.restitution = cc2d.Restitution;
				fixtureDef.restitutionThreshold = cc2d.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}
		}

		m_IsPlaying = true;
	}

	void Scene::OnRuntimeStop()
	{
		{	//	Stop Scripts
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				nsc.Instance = nullptr;
			});
		}
		delete m_PhysicsWorld;
		m_PhysicsWorld = nullptr;
		m_IsPlaying = false;
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		Dr_PROFILE_FUNCTION();

		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}


	Entity Scene::GetPrimaryCameraEntity()
	{
		Dr_PROFILE_FUNCTION();

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity(entity, this);
		}
		return {};
	}

	//  ------------------------------  Entities  ----------------------- //
	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		Dr_PROFILE_FUNCTION();

		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		Dr_CORE_ASSERT(m_EntityIDMap.find(uuid) == m_EntityIDMap.end());
		m_EntityIDMap[uuid] = entity;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	template<typename T>
	static void CopyComponent(entt::registry& dstRegistry, entt::registry& srcRegistry, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		auto components = srcRegistry.view<T>();
		for (auto srcEntity : components)
		{
			entt::entity destEntity = enttMap.at(srcRegistry.get<IDComponent>(srcEntity).ID);

			auto& srcComponent = srcRegistry.get<T>(srcEntity);
			auto& destComponent = dstRegistry.emplace_or_replace<T>(destEntity, srcComponent);
		}
	}

	template<typename T>
	static void CopyComponentIfExists(entt::entity dst, entt::entity src, entt::registry& registry)
	{
		if (registry.has<T>(src))
		{
			auto& srcComponent = registry.get<T>(src);
			registry.emplace_or_replace<T>(dst, srcComponent);
		}
	}

	void Scene::DuplicateEntity(Entity entity)
	{
		Entity newEntity;
		std::string name = entity.GetName();
		if (entity.HasComponent<TagComponent>())
			newEntity = CreateEntity(name);
		else
			newEntity = CreateEntity();

		CopyComponentIfExists<TransformComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
		CopyComponentIfExists<NativeScriptComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
		CopyComponentIfExists<CameraComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
		CopyComponentIfExists<SpriteRendererComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
		CopyComponentIfExists<RigidBody2DComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
		CopyComponentIfExists<BoxCollider2DComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
		CopyComponentIfExists<CircleCollider2DComponent>(newEntity.m_EntityHandle, entity.m_EntityHandle, m_Registry);
	}

	Entity Scene::FindEntityByTag(const std::string& tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const auto& candidate = view.get<TagComponent>(entity).Tag;
			if (candidate == tag)
				return Entity(entity, this);
		}

		Dr_CORE_ASSERT(false, "Entity not found by tag!");
		return Entity{};
	}

	Entity Scene::FindEntityByUUID(UUID id)
	{
		auto view = m_Registry.view<IDComponent>();
		for (auto entity : view)
		{
			auto& idComponent = m_Registry.get<IDComponent>(entity);
			if (idComponent.ID == id)
				return Entity(entity, this);
		}

		Dr_CORE_ASSERT(false, "Entity not found by id!");
		return Entity{};
	}

	//	Copy to runtime
	void Scene::CopyTo(Ref<Scene>& target)
	{

		std::unordered_map<UUID, entt::entity> enttMap;

		auto idComponents = m_Registry.view<IDComponent>();
		for (auto entity : idComponents)
		{
			auto uuid = m_Registry.get<IDComponent>(entity).ID;
			const auto& name = m_Registry.get<TagComponent>(entity).Tag;
			Entity e = target->CreateEntityWithUUID(uuid, name);
			enttMap[uuid] = e.m_EntityHandle;
		}

		CopyComponent<TransformComponent>(target->m_Registry, m_Registry, enttMap);
		CopyComponent<NativeScriptComponent>(target->m_Registry, m_Registry, enttMap);
		CopyComponent<CameraComponent>(target->m_Registry, m_Registry, enttMap);
		CopyComponent<SpriteRendererComponent>(target->m_Registry, m_Registry, enttMap);
		CopyComponent<RigidBody2DComponent>(target->m_Registry, m_Registry, enttMap);
		CopyComponent<BoxCollider2DComponent>(target->m_Registry, m_Registry, enttMap);
		CopyComponent<CircleCollider2DComponent>(target->m_Registry, m_Registry, enttMap);
	}


	Ref<Scene> Scene::GetScene(UUID uuid)
	{
		if (s_ActiveScenes.find(uuid) != s_ActiveScenes.end())
			return s_ActiveScenes.at(uuid);

		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		//static_assert(false);
	}
	//  -----------------------------  ID COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{
	}
	//  -----------------------------  TAG COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}
	//  -----------------------------  RELATIONSHIP COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<RelationshipComponent>(Entity entity, RelationshipComponent& component)
	{
	}
	//  -----------------------------  TRANSFORM COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}
	//  -----------------------------  CAMERA COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}
	//  -----------------------------  SPRITE RENDERER COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}
	//  -----------------------------  NATIVE SCRIPT COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}
	//  -----------------------------  SCRIPT COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<ScriptComponent>(Entity entity, ScriptComponent& component)
	{
	}
	//  -----------------------------  RIGID BODY 2D COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<RigidBody2DComponent>(Entity entity, RigidBody2DComponent& component)
	{
	}
	//  -----------------------------  BOX COLLIDER 2D COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
	{
	}
	//  -----------------------------  CIRCLE COLLIDER 2D COMPONENT  -----------------------------  //
	template<>
	void Scene::OnComponentAdded<CircleCollider2DComponent>(Entity entity, CircleCollider2DComponent& component)
	{
	}

}	//	END namespace DAGGer
