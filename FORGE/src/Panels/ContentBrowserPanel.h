#pragma once

#include <filesystem>

#include "RAPIER/Renderer/Texture.h"
#include "RAPIER/Core/Events/Event.h"
#include "RAPIER/Core/Events/KeyEvent.h"

#include <imgui/imgui.h>

namespace RAPIER
{
	class FileColumn
	{
	public:
		FileColumn()
		{
			myPath = "";
			myDepth = 0;
		}
		FileColumn(std::filesystem::path path, size_t depth)
		{
			Set(path, depth);
		}

		void Set(std::filesystem::path path, size_t depth)
		{
			myPath = path;
			myDepth = depth;
		}

		std::filesystem::path GetPath() { return myPath; }
		size_t GetDepth() { return myDepth; }
		std::string GetString() { return std::filesystem::directory_entry(myPath).path().string(); }
		float GetMaxText()
		{
			float max = 0.0f;
			for (auto& directoryEntry : std::filesystem::directory_iterator(GetPath()))
			{
				const auto& path = directoryEntry.path();
				std::string filenameString = path.filename().string();
				ImVec2 textSize = ImGui::CalcTextSize(filenameString.c_str());
				if (textSize.x > max)
					max = textSize.x;
			}
			return max;
		}
	private:
		std::filesystem::path myPath;
		size_t myDepth;
	};

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		bool OnDrawColumn(FileColumn Column, float thumbnailSize, float& longestName, std::filesystem::path& uPath);
		bool OnDragAndDrop(std::filesystem::path& relativePath);
		bool OnItemCheck(std::filesystem::directory_entry& directoryEntry, std::filesystem::path path, std::filesystem::path& uPath);
	private:
		std::filesystem::path GetCurrentDirectory();
		std::vector<FileColumn> m_Columns;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}	//	END namespace RAPIER
