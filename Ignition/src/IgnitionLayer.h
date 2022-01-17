#pragma once

#include "RAPIER.h"
#include <imgui.h>

#include "RAPIER/Project/UserPreferences.h"

#include <functional>

namespace RAPIER
{
	struct IgnitionProperties
	{
		Ref<UserPreferences> UserPreferences;
		std::string InstallPath;
		std::function<void(std::string)> ProjectOpenedCallback;
	};

	class IgnitionLayer : public Layer
	{
	public:
		IgnitionLayer(const IgnitionProperties& properies);
		virtual ~IgnitionLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;
	private:
		void CreateProject(std::filesystem::path projectPath);
		void AddProjectToRecents(const std::filesystem::path& projectFile);
	private:
		IgnitionProperties m_Properties;
		ImGuiID m_HoveredProjectID;
		Ref<Texture2D> m_RapierLogo;
	};

}	//	END namespace RAPIER
