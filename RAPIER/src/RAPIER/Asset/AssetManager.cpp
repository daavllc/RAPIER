#include "rppch.h"
#include "AssetManager.h"

#include "RAPIER/Renderer/SceneRenderer.h"
#include "RAPIER/Project/Project.h"

#include <yaml-cpp/yaml.h>

#include <filesystem>

namespace RAPIER {

	void AssetTypes::Init()
	{
		s_Types["hsc"] = AssetType::Scene;
		s_Types["fbx"] = AssetType::Mesh;
		s_Types["obj"] = AssetType::Mesh;
		s_Types["blend"] = AssetType::Mesh;
		s_Types["png"] = AssetType::Texture;
		s_Types["hdr"] = AssetType::EnvMap;
		s_Types["hpm"] = AssetType::PhysicsMat;
		s_Types["wav"] = AssetType::Audio;
		s_Types["ogg"] = AssetType::Audio;
		s_Types["cs"] = AssetType::Script;
	}

	size_t AssetTypes::GetAssetTypeID(const std::string& extension)
	{
		if (extension == "")
			return 0;

		for (auto& kv : s_Types)
		{
			if (kv.first == extension)
				return std::hash<std::string>()(extension);
		}

		return -1;
	}

	AssetType AssetTypes::GetAssetTypeFromExtension(const std::string& extension)
	{
		return s_Types.find(extension) != s_Types.end() ? s_Types[extension] : AssetType::Other;
	}

	std::map<std::string, AssetType> AssetTypes::s_Types;

	void AssetManager::Init()
	{
		FileSystem::SetChangeCallback(AssetManager::OnFileSystemChanged);
		ReloadAssets();
	}

	void AssetManager::SetAssetChangeCallback(const AssetsChangeEventFn& callback)
	{
		s_AssetsChangeCallback = callback;
	}

	void AssetManager::Shutdown()
	{
		s_LoadedAssets.clear();
	}

	void AssetManager::OnFileSystemChanged(const std::vector<FileSystemChangedEvent>& events)
	{
		// Process all events before the refreshing the Content Browser
		for (const auto& e : events)
		{
			if (!e.IsDirectory)
			{
				switch (e.Action)
				{
					case FileSystemAction::Modified:
					{
						break;
					}
					case FileSystemAction::Rename:
					{
						break;
					}
					case FileSystemAction::Delete:
					{
						break;
					}
				}
			}
		}

		s_AssetsChangeCallback(events);
	}

	std::string AssetManager::StripExtras(const std::string& filename)
	{
		std::vector<std::string> out;
		size_t start;
		size_t end = 0;

		while ((start = filename.find_first_not_of(".", end)) != std::string::npos)
		{
			end = filename.find(".", start);
			out.push_back(filename.substr(start, end - start));
		}

		if (out[0].length() >= 10)
		{
			auto cutFilename = out[0].substr(0, 9) + "...";
			return cutFilename;
		}

		auto filenameLength = out[0].length();
		auto paddingToAdd = 9 - filenameLength;

		std::string newFileName;

		for (int i = 0; i <= paddingToAdd; i++)
		{
			newFileName += " ";
		}

		newFileName += out[0];

		return newFileName;
	}

	std::unordered_map<AssetHandle, Ref<Asset>> AssetManager::s_LoadedAssets;
	AssetManager::AssetsChangeEventFn AssetManager::s_AssetsChangeCallback;

}
