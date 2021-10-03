#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "DAGGer/Scene/Components.h"
#include <cstring>


#ifdef _MSVC_LANG
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <glm/gtc/type_ptr.hpp>

namespace DAGGer
{
	extern const std::filesystem::path g_AssetPath;

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
		m_SelectionContext = {};
		if (m_SelectionContext && false)
		{
			// Try and find same entity in new scene
			auto& entityMap = m_Context->GetEntityMap();
			UUID selectedEntityID = m_SelectionContext.GetUUID();
			if (entityMap.find(selectedEntityID) != entityMap.end())
				m_SelectionContext = entityMap.at(selectedEntityID);
		}

	}

	void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
	{
		m_SelectionContext = entity;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		if (m_Context)
		{
			// Entity List
			m_Context->m_Registry.each([&](auto entity)
			{
				Entity e(entity, m_Context.Raw());
				if (e.HasComponent<IDComponent>())
					DrawEntityNode(e);
			});


			// Right-click on blank space
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::BeginMenu("Create"))
				{
					if (ImGui::MenuItem("Empty Entity"))
					{
						auto newEntity = m_Context->CreateEntity("New Entity");
						SetSelectedEntity(newEntity);
					}
					if (ImGui::MenuItem("Camera"))
					{
						auto newEntity = m_Context->CreateEntity("New Camera");
						newEntity.AddComponent<CameraComponent>();
						SetSelectedEntity(newEntity);
					}
					if (ImGui::BeginMenu("2D"))
					{
						if (ImGui::MenuItem("Sprite"))
						{
							auto newEntity = m_Context->CreateEntity("New Sprite");
							newEntity.AddComponent<SpriteRendererComponent>();
							SetSelectedEntity(newEntity);
						}
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndPopup();
			}	//	END right-click on blank space

			ImGui::End();

			ImGui::Begin("Properties");
			if (m_SelectionContext)
				DrawComponentsView(m_SelectionContext);
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity, const std::string& searchFilter /*= {}*/)
	{
		UUID id;
		if (entity.HasComponent<IDComponent>())
			id = entity.GetComponent<IDComponent>().ID;

		const char* name = "Unnamed Entity";
		if (entity.HasComponent<TagComponent>())
			name = entity.GetComponent<TagComponent>().Tag.c_str();

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, name);
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
				entityDeleted = true;
			if (ImGui::MenuItem("Duplicate"))
				m_Context->DuplicateEntity(entity);

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			ImGui::TextDisabled("%llx", id);
			DrawComponents(entity, flags);
			//for (auto child : entity.Children())
			//{
			//	Entity e = m_Context->FindEntityByUUID(child);
			//	if (e)
			//		DrawEntityNode(e, searchFilter);
			//}
			ImGui::TreePop();
		}
		//	Wait until end of node UI to delete entity
		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);

		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);
		ImGui::PopFont();

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopStyleColor(3);
		ImGui::PopFont();

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopStyleColor(3);
		ImGui::PopFont();

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, ImGuiTreeNodeFlags& treeNodeFlags, UIFunction uiFunction)
	{
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y;
			ImGui::Separator();
			bool open = (ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str()));
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button(">", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;

				ImGui::EndPopup();
			}
			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	void SceneHierarchyPanel::DrawComponentsView(Entity entity)
	{
		ImGui::AlignTextToFramePadding();

		UUID id;
		if (entity.HasComponent<IDComponent>())
			id = entity.GetComponent<IDComponent>().ID;

		ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));
			ImGui::PushItemWidth(contentRegionAvailable.x * 0.5f);
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
			ImGui::PopItemWidth();
		}	//	END TagComponent

		ImGui::SameLine();
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 textSize = ImGui::CalcTextSize("Add Component");
		ImGui::SameLine(contentRegionAvailable.x - (textSize.x + GImGui->Style.FramePadding.y));
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponentPanel");

		if (ImGui::BeginPopup("AddComponentPanel"))
		{
			if (!m_SelectionContext.HasComponent<RelationshipComponent>())
			{
				if (ImGui::Button("Relationship"))
				{
					m_SelectionContext.AddComponent<RelationshipComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectionContext.HasComponent<CameraComponent>())
			{
				if (ImGui::Button("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectionContext.HasComponent<SpriteRendererComponent>())
			{
				if (ImGui::Button("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectionContext.HasComponent<RigidBody2DComponent>())
			{
				if (ImGui::Button("Rigidbody 2D"))
				{
					m_SelectionContext.AddComponent<RigidBody2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectionContext.HasComponent<BoxCollider2DComponent>())
			{
				if (ImGui::Button("Box Collider 2D"))
				{
					m_SelectionContext.AddComponent<BoxCollider2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectionContext.HasComponent<CircleCollider2DComponent>())
			{
				if (ImGui::Button("Circle Collider 2D"))
				{
					m_SelectionContext.AddComponent<CircleCollider2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::EndPopup();
		}
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
		DrawComponents(entity, treeNodeFlags);
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity, ImGuiTreeNodeFlags treeNodeFlags)
	{
		//  -----------------------------  NATIVE SCRIPT COMPONENT  -----------------------------  //
		DrawComponent<NativeScriptComponent>("Native Script", entity, treeNodeFlags, [](auto& component)
		{
		});
		//  -----------------------------  SCRIPT COMPONENT  -----------------------------  //
		DrawComponent<ScriptComponent>("Script", entity, treeNodeFlags, [](auto& component)
		{
		});
		//  -----------------------------  RELATIONSHIP COMPONENT  -----------------------------  //
		DrawComponent<RelationshipComponent>("Relationship", entity, treeNodeFlags, [](auto& component)
		{
			ImGui::TextDisabled("%llx", component.ParentHandle);
			ImGui::Separator();
			for (auto& childID : component.Children)
				ImGui::TextDisabled("%llx", childID);
			ImGui::Separator();
		});
		//  -----------------------------  TRANSFORM COMPONENT  -----------------------------  //
		DrawComponent<TransformComponent>("Transform", entity, treeNodeFlags, [](auto& component)
		{
			DrawVec3Control("Translation", component.Translation);
			ImGui::Separator();
			glm::vec3 rotation = glm::degrees(component.Rotation);
			DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);
			ImGui::Separator();
			DrawVec3Control("Scale", component.Scale, 1.0f);
			ImGui::Separator();
		});
		//  -----------------------------  CAMERA COMPONENT  -----------------------------  //
		DrawComponent<CameraComponent>("Camera", entity, treeNodeFlags, [](auto& component)
		{
			auto& camera = component.Camera;

			ImGui::Checkbox("Primary", &component.Primary);

			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
			if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float perspectiveFOV = glm::degrees(camera.GetPerspectiveVerticalFOV());
				float perspectiveNear = camera.GetPerspectiveNearClip();
				float perspectiveFar = camera.GetPerspectiveFarClip();

				if (ImGui::DragFloat("Vertical FOV", &perspectiveFOV))			//	FOV
					camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveFOV));
				if (ImGui::DragFloat("Near", &perspectiveNear))	//	Near
					camera.SetPerspectiveNearClip(perspectiveNear);
				if (ImGui::DragFloat("Far", &perspectiveFar))		//	Far
					camera.SetPerspectiveFarClip(perspectiveFar);
			}
			else if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float orthoSize = camera.GetOrthographicSize();
				float orthoNear = camera.GetOrthographicNearClip();
				float orthoFar = camera.GetOrthographicFarClip();

				if (ImGui::DragFloat("Size", &orthoSize))		//	Size
					camera.SetOrthographicSize(orthoSize);
				if (ImGui::DragFloat("Near Clip", &orthoNear))	//	Near
					camera.SetOrthographicNearClip(orthoNear);
				if (ImGui::DragFloat("Far Clip", &orthoFar))	//	Far
					camera.SetOrthographicFarClip(orthoFar);

				ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
			}
		});
		//  -----------------------------  SPRITE RENDERER COMPONENT  -----------------------------  //
		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, treeNodeFlags, [](auto& component)
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

			ImGui::Button("Texture", ImVec2(100.0f, 0.0f));

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ASSET"))
				{
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::filesystem::path texturePath = std::filesystem::path(g_AssetPath) / path;
					Ref<Texture2D> texture = Texture2D::Create(texturePath.string());
					if (texture->IsLoaded())
						component.Texture = texture;
					else
						Dr_WARN("Could not load texture {0}", texturePath.filename().string());
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::DragFloat("Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 100.0f);
		});
		//  -----------------------------  RIGID 2D BODY COMPONENT  -----------------------------  //
		DrawComponent<RigidBody2DComponent>("Rigidbody 2D", entity, treeNodeFlags, [](auto& component)
		{
				const char* bodyTypeStrings[] = { "Static", "Dynamic", "Kinematic" };
			const char* currentBodyTypeStrings = bodyTypeStrings[(int)component.Type];
			if (ImGui::BeginCombo("Body Type", currentBodyTypeStrings))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentBodyTypeStrings == bodyTypeStrings[i];
					if (ImGui::Selectable(bodyTypeStrings[i], isSelected))
					{
						currentBodyTypeStrings = bodyTypeStrings[i];
						component.Type = (RigidBody2DComponent::BodyType)i;
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			ImGui::Checkbox("Fixed Rotation", &component.FixedRotation);
		});
		//  -----------------------------  BOX COLLIDER COMPONENT  -----------------------------  //
		DrawComponent<BoxCollider2DComponent>("Box Collider 2D", entity, treeNodeFlags, [](auto& component)
		{
			ImGui::DragFloat2("Offset",               glm::value_ptr(component.Offset));
			ImGui::DragFloat2("Size",                 glm::value_ptr(component.Size));
			ImGui::DragFloat("Density",               &component.Density,     0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Friction",              &component.Friction,    0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution",           &component.Restitution, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
		});
		//  -----------------------------  CIRCLE COLLIDER COMPONENT  -----------------------------  //
		DrawComponent<CircleCollider2DComponent>("Circle Collider 2D", entity, treeNodeFlags, [](auto& component)
		{
			ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
			ImGui::DragFloat("Radius",      &component.Radius, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Density",     &component.Density, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Friction",    &component.Friction, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution", &component.Restitution, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
		});

	}	//	END DrawComponents

}	//	END namespace DAGGer
