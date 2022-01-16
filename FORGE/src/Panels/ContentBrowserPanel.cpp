#include "rppch.h"
#include "ContentBrowserPanel.h"

namespace RAPIER
{
	//	Change once we have projects
	extern const std::filesystem::path g_AssetPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
	{
		m_DirectoryIcon = Texture2D::Create("Resources/Icons/ContentBrowser/DirectoryIcon.png");
		m_FileIcon = Texture2D::Create("Resources/Icons/ContentBrowser/FileIcon.png");

		m_Columns.push_back(FileColumn(g_AssetPath, m_Columns.size()));
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("ContentBrowser");
		std::string pStr = std::filesystem::directory_entry(GetCurrentDirectory()).path().string().c_str();
		ImGui::Text(pStr.c_str());

		ImGui::Separator();

		static float padding = 16.0f;
		static float thumbnailSize = ImGui::GetFontSize();
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		float panelHeight = ImGui::GetContentRegionAvail().y;

		int columns = m_Columns.size();
		ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit;
		ImGui::BeginTable(pStr.c_str(), columns, flags);
		ImGuiTableColumnFlags cflags = ImGuiTableColumnFlags_WidthFixed;
		ImGui::TableSetupColumn(pStr.c_str(), cflags, 0.0f);

		bool Update = false;
		size_t uIndex;
		std::filesystem::path uPath;
		for (int i = 0; i < columns; i++)
		{
			FileColumn& Column = m_Columns[i];
			ImGui::TableNextColumn();
			ImGui::TableHeader(Column.GetPath().filename().string().c_str());

			std::filesystem::path path = Column.GetPath();

			float longestName = 0.0f;
			if (OnDrawColumn(Column, thumbnailSize, longestName, uPath))
			{
				uIndex = i;
				Update = true;
			}

			ImGui::NextColumn();
		}
		ImGui::EndTable();
		ImGui::Separator();

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);
		// TODO: status bar
		ImGui::End();
		if (Update)
		{
			FileColumn Column = m_Columns[uIndex];
			if (uIndex + 1 == m_Columns.size())
			{
				auto pP = uPath.parent_path();
				auto cP = Column.GetPath();
				m_Columns.push_back(FileColumn(Column.GetPath() /= uPath.filename(), m_Columns.size()));
			}
			else
			{
				while (m_Columns.size() > Column.GetDepth() + 1)
				{
					size_t size = m_Columns.size();
					size_t depth = Column.GetDepth();
					m_Columns.pop_back();
				}
				m_Columns.push_back(FileColumn(Column.GetPath() /= uPath.filename(), m_Columns.size()));
			}
		}
	}

	bool ContentBrowserPanel::OnDrawColumn(FileColumn Column, float thumbnailSize, float& longestName, std::filesystem::path& uPath)
	{
		bool Change = false;
		for (std::filesystem::directory_entry directoryEntry : std::filesystem::directory_iterator(Column.GetPath()))
		{

			const auto& path = directoryEntry.path();
			std::filesystem::path relativePath = std::filesystem::relative(path, g_AssetPath);
			std::string filenameString = relativePath.filename().string();

			ImGui::PushID(filenameString.c_str());
			ImVec2 textSize = ImGui::CalcTextSize(filenameString.c_str());
			if (textSize.x > longestName)
				longestName = textSize.x;
			Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
			//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			//ImGui::PopStyleColor();
			OnDragAndDrop(relativePath);
			bool cChange = OnItemCheck(directoryEntry, path, uPath);
			if (cChange)
				Change = true;
			ImGui::SameLine();
			ImGui::Button(filenameString.c_str());
			OnDragAndDrop(relativePath);
			cChange = OnItemCheck(directoryEntry, path, uPath);
			if (cChange)
				Change = true;

			ImGui::PopID();
		}
		return Change;
	}
	bool ContentBrowserPanel::OnDragAndDrop(std::filesystem::path& relativePath)
	{
		bool Dropped = false;
		if (ImGui::BeginDragDropSource())
		{
			const wchar_t* itemPath = relativePath.c_str();
			ImGui::SetDragDropPayload("CONTENT_BROWSER_ASSET", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t), ImGuiCond_Once);
			ImGui::EndDragDropSource();
			Dropped = true;
		}
		return Dropped;
	}

	bool ContentBrowserPanel::OnItemCheck(std::filesystem::directory_entry& directoryEntry, std::filesystem::path path, std::filesystem::path& uPath)
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (directoryEntry.is_directory())
			{
				uPath = path;
				return true;
			}
		}
		return false;
	}

	std::filesystem::path ContentBrowserPanel::GetCurrentDirectory()
	{
		return m_Columns[m_Columns.size() - 1].GetPath();
	}
}	//	END namespace RAPIER
