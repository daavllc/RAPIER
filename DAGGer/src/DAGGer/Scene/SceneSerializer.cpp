/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the implementation for Opening/Saving files
////////////////////////////////
#include "drpch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

#include <yaml-cpp/yaml.h>

namespace YAML
{
	template<>
	struct convert<glm::vec2>	//	VEC2
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>	//	VEC3
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>	//	VEC4
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::quat>	//	QUAT
	{
		static Node encode(const glm::quat& rhs)
		{
			Node node;
			node.push_back(rhs.w);
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::quat& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.w = node[0].as<float>();
			rhs.x = node[1].as<float>();
			rhs.y = node[2].as<float>();
			rhs.z = node[3].as<float>();
			return true;
		}
	};


}	//	END namespace YAML
//=---=------------------------------------------------------------=---=//
//=---=-                       Scene Serializer                   -=---=//
//=---=------------------------------------------------------------=---=//
namespace DAGGer
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)	//	VEC2
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)	//	VEC3
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)	//	VEC4
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::quat& v)	//	QUAT
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.w << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	static std::string RigidBody2DBodyTypeToString(RigidBody2DComponent::BodyType bodyType)
	{
		switch (bodyType)
		{
			case RigidBody2DComponent::BodyType::Static:    return "Static";
			case RigidBody2DComponent::BodyType::Dynamic:   return "Dynamic";
			case RigidBody2DComponent::BodyType::Kinematic: return "Kinematic";
		}

		Dr_CORE_ASSERT(false, "Unknown body type!");
		return {};
	}
	static RigidBody2DComponent::BodyType RigidBody2DBodyTypeFromString(std::string bodyTypeString)
	{
		if (bodyTypeString == "Static")    return RigidBody2DComponent::BodyType::Static;
		if (bodyTypeString == "Dynamic")   return RigidBody2DComponent::BodyType::Dynamic;
		if (bodyTypeString == "Kinematic") return RigidBody2DComponent::BodyType::Kinematic;

		Dr_CORE_ASSERT(false, "Unknown body type!");
		return RigidBody2DComponent::BodyType::Static;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}
	void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		Dr_PROFILE_FUNCTION();
		Dr_CORE_ASSERT(entity.HasComponent<IDComponent>(), "No ID Component");

		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << entity.GetUUID();

		// --------------------------- TAG COMPONENT ----------------------- //
		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent
		}
		// --------------------------- RELATIONSHIP COMPONENT ----------------------- //
		if (entity.HasComponent<RelationshipComponent>())
		{
			auto& relationshipComponent = entity.GetComponent<RelationshipComponent>();
			out << YAML::Key << "Parent" << YAML::Value << relationshipComponent.ParentHandle;

			out << YAML::Key << "Children";
			out << YAML::Value << YAML::BeginSeq;

			for (auto child : relationshipComponent.Children)
			{
				out << YAML::BeginMap;	//	Child
				out << YAML::Key << "Handle" << YAML::Value << child;
				out << YAML::EndMap;	//	Child
			}
			out << YAML::EndSeq;

		}
		// --------------------------- TRANSFORM COMPONENT ----------------------- //
		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; // TransformComponent
		}
		// --------------------------- CAMERA COMPONENT ----------------------- //
		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap; // Camera

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

			out << YAML::EndMap; // CameraComponent
		}
		// --------------------------- SPRITE RENDERER COMPONENT ----------------------- //
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			out << YAML::EndMap; // SpriteRendererComponent
		}
		// --------------------------- CIRCLE RENDERER COMPONENT ----------------------- //
		if (entity.HasComponent<CircleRendererComponent>())
		{
			out << YAML::Key << "CircleRendererComponent";
			out << YAML::BeginMap; // CircleRendererComponent

			auto& circleRendererComponent = entity.GetComponent<CircleRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << circleRendererComponent.Color;
			out << YAML::Key << "Thickness" << YAML::Value << circleRendererComponent.Thickness;
			out << YAML::Key << "Fade" << YAML::Value << circleRendererComponent.Fade;

			out << YAML::EndMap; // CircleRendererComponent
		}
		// --------------------------- Rigidbody 2D COMPONENT ----------------------- //
		if (entity.HasComponent<RigidBody2DComponent>())
		{
			out << YAML::Key << "RigidBody2DComponent";
			out << YAML::BeginMap; // RigidBody2DComponent

			auto& rb2dComponent = entity.GetComponent<RigidBody2DComponent>();
			out << YAML::Key << "BodyType" << YAML::Value << RigidBody2DBodyTypeToString(rb2dComponent.Type);
			out << YAML::Key << "FixedRotation" << YAML::Value << rb2dComponent.FixedRotation;

			out << YAML::EndMap; // RigidBody2DComponent
		}
		// --------------------------- Box Collider 2D COMPONENT ----------------------- //
		if (entity.HasComponent<BoxCollider2DComponent>())
		{
			out << YAML::Key << "BoxCollider2DComponent";
			out << YAML::BeginMap; // BoxCollider2DComponent

			auto& bc2dComponent = entity.GetComponent<BoxCollider2DComponent>();
			out << YAML::Key << "Offset" << YAML::Value << bc2dComponent.Offset;
			out << YAML::Key << "Size"   << YAML::Value << bc2dComponent.Size;
			out << YAML::Key << "Density"     << YAML::Value << bc2dComponent.Density;
			out << YAML::Key << "Friction"    << YAML::Value << bc2dComponent.Friction;
			out << YAML::Key << "Restitution" << YAML::Value << bc2dComponent.Restitution;
			out << YAML::Key << "RestitutionThreshold" << YAML::Value << bc2dComponent.RestitutionThreshold;

			out << YAML::EndMap; // BoxCollider2DComponent
		}
		// --------------------------- CIRCLE Collider 2D COMPONENT ----------------------- //
		if (entity.HasComponent<CircleCollider2DComponent>())
		{
			out << YAML::Key << "CircleCollider2DComponent";
			out << YAML::BeginMap; // CircleCollider2DComponent

			auto& cc2dComponent = entity.GetComponent<CircleCollider2DComponent>();
			out << YAML::Key << "Offset" << YAML::Value << cc2dComponent.Offset;
			out << YAML::Key << "Radius" << YAML::Value << cc2dComponent.Radius;
			out << YAML::Key << "Density" << YAML::Value << cc2dComponent.Density;
			out << YAML::Key << "Friction" << YAML::Value << cc2dComponent.Friction;
			out << YAML::Key << "Restitution" << YAML::Value << cc2dComponent.Restitution;
			out << YAML::Key << "RestitutionThreshold" << YAML::Value << cc2dComponent.RestitutionThreshold;

			out << YAML::EndMap; // CircleCollider2DComponent
		}

		out << YAML::EndMap; // Entity
	}
	//////////////////////////////////////////////////////////////////////////////
	//  -------------------------------  SERIALIZE  --------------------------  //
	//////////////////////////////////////////////////////////////////////////////
	void SceneSerializer::Serialize(const std::string& filepath)
	{
		Dr_PROFILE_FUNCTION();

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
		{
			Entity entity = { entityID, m_Scene.Raw() };
			if (!entity)
				return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}
	//////////////////////////////////////////////////////////////////////////////
	//  ---------------------------  SERIALIZE RUNTIME  ----------------------  //
	//////////////////////////////////////////////////////////////////////////////
	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		Dr_PROFILE_FUNCTION();
		// Not implemented
		Dr_CORE_ASSERT(false);
	}
	//////////////////////////////////////////////////////////////////////////////
	//  -----------------------------  DESERIALIZE  --------------------------  //
	//////////////////////////////////////////////////////////////////////////////
	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		Dr_PROFILE_FUNCTION();

		YAML::Node data;
		try
		{
			data = YAML::LoadFile(filepath);
		}
		catch (YAML::ParserException e)
		{
			return false;
		}
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		Dr_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				uint64_t uuid = entity["Entity"].as<uint64_t>();
				// --------------------------- TAG COMPONENT ----------------------- //
				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				Dr_CORE_TRACE("Deserialized entity with ID: \'{0}\',\tname: \'{1}\'", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntityWithUUID(uuid, name);
				// --------------------------- RELATIONSHIP COMPONENT ----------------------- //
				auto relationshipComponent = entity["RelationshipComponent"];
				if (relationshipComponent)
				{
					auto rc = deserializedEntity.GetComponent<RelationshipComponent>();
					uint64_t parentHandle = relationshipComponent["Parent"] ? relationshipComponent["Parent"].as<uint64_t>() : 0;
					rc.ParentHandle = parentHandle;

					auto children = entity["Children"];
					if (children)
					{
						for (auto child : children)
						{
							uint64_t childHandle = child["Handle"].as<uint64_t>();
							rc.Children.push_back(childHandle);
						}
					}
				}
				// --------------------------- TRANSFORM COMPONENT ----------------------- //
				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					// Entities always have transforms
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Translation = transformComponent["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}
				// --------------------------- CAMERA COMPONENT ----------------------- //
				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();

					auto& cameraProps = cameraComponent["Camera"];
					cc.Camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

					cc.Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
					cc.Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
					cc.Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

					cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
					cc.Camera.SetOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
					cc.Camera.SetOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());

					cc.Primary = cameraComponent["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
				}
				// --------------------------- SPRITE RENDERER COMPONENT ----------------------- //
				auto spriteRendererComponent = entity["SpriteRendererComponent"];
				if (spriteRendererComponent)
				{
					auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
					src.Color = spriteRendererComponent["Color"].as<glm::vec4>();
				}
				// --------------------------- CIRCLE RENDERER COMPONENT ----------------------- //
				auto circleRendererComponent = entity["CircleRendererComponent"];
				if (circleRendererComponent)
				{
					auto& crc = deserializedEntity.AddComponent<CircleRendererComponent>();
					crc.Color = circleRendererComponent["Color"].as<glm::vec4>();
					crc.Thickness = circleRendererComponent["Thickness"].as<float>();
					crc.Fade = circleRendererComponent["Fade"].as<float>();
				}
				// --------------------------- RIGIDBODY 2D COMPONENT ----------------------- //
				auto rb2dComponent = entity["RigidBody2DComponent"];
				if (rb2dComponent)
				{
					auto& rb2d = deserializedEntity.AddComponent<RigidBody2DComponent>();
					rb2d.Type = RigidBody2DBodyTypeFromString(rb2dComponent["BodyType"].as<std::string>());
					rb2d.FixedRotation = rb2dComponent["FixedRotation"].as<bool>();
				}
				// --------------------------- BOX COLLIDER 2D COMPONENT ----------------------- //
				auto bc2dComponent = entity["BoxCollider2DComponent"];
				if (bc2dComponent)
				{
					auto& bc2d = deserializedEntity.AddComponent<BoxCollider2DComponent>();
					bc2d.Offset  = bc2dComponent["Offset"].as<glm::vec2>();
					bc2d.Size    = bc2dComponent["Size"].as<glm::vec2>();
					bc2d.Density     = bc2dComponent["Density"].as<float>();
					bc2d.Friction    = bc2dComponent["Friction"].as<float>();
					bc2d.Restitution = bc2dComponent["Restitution"].as<float>();
					bc2d.RestitutionThreshold = bc2dComponent["RestitutionThreshold"].as<float>();
				}
				// --------------------------- CIRCLE COLLIDER 2D COMPONENT ----------------------- //
				auto cc2dComponent = entity["CircleCollider2DComponent"];
				if (cc2dComponent)
				{
					auto& cc2d = deserializedEntity.AddComponent<CircleCollider2DComponent>();
					cc2d.Offset = cc2dComponent["Offset"].as<glm::vec2>();
					cc2d.Radius   = cc2dComponent["Radius"].as<float>();
					cc2d.Density  = cc2dComponent["Density"].as<float>();
					cc2d.Friction = cc2dComponent["Friction"].as<float>();
					cc2d.Restitution = cc2dComponent["Restitution"].as<float>();
					cc2d.RestitutionThreshold = cc2dComponent["RestitutionThreshold"].as<float>();
				}
			}
		}

		return true;
	}
	//////////////////////////////////////////////////////////////////////////////
	//  -------------------------  DESERIALIZE RUNTIME  ----------------------  //
	//////////////////////////////////////////////////////////////////////////////
	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		Dr_PROFILE_FUNCTION();

		// Not implemented
		Dr_CORE_ASSERT(false);
		return false;
	}

}	//	END namespace DAGGer
