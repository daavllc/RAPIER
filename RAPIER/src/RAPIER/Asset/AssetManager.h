#pragma once

#include "AssetSerializer.h"
#include "RAPIER/Project/Project.h"
#include "RAPIER/Utilities/FileSystem.h"
#include "RAPIER/Utilities/StringUtils.h"

#include "RAPIER/Debug/Profiler.h"

#include <map>
#include <unordered_map>

namespace RAPIER
{
	// Deserialized from project file - these are just defaults
	class AssetManagerConfig
	{
		std::string AssetDirectory = "Assets/";
		std::string AssetRegistryPath = "Assets/AssetRegistry.rpr";
	};

	class AssetTypes
	{
	public:
		static void Init();
		static size_t GetAssetTypeID(const std::string& extension);
		static AssetType GetAssetTypeFromExtension(const std::string& extension);

	private:
		static std::map<std::string, AssetType> s_Types;
	};

	class AssetManager
	{
	public:
		using AssetsChangeEventFn = std::function<void(const std::vector<FileSystemChangedEvent>&)>;
	public:
		static void Init();
		static void SetAssetChangeCallback(const AssetsChangeEventFn& callback);
		static void Shutdown();

		static std::string StripExtras(const std::string& filename);
		static void OnImGuiRender(bool& open);
	private:
		static void LoadAssetRegistry();
		static void ProcessDirectory(const std::filesystem::path& directoryPath);
		static void ReloadAssets();
		static void WriteRegistryToFile();

		//static AssetMetadata& GetMetadataInternal(AssetHandle handle);

		static void OnFileSystemChanged(const std::vector<FileSystemChangedEvent>& events);
		static void OnAssetRenamed(AssetHandle assetHandle, const std::filesystem::path& newFilePath);
		static void OnAssetMoved(AssetHandle assetHandle, const std::filesystem::path& destinationPath);
		static void OnAssetDeleted(AssetHandle assetHandle);

	private:
		static std::unordered_map<AssetHandle, Ref<Asset>> s_LoadedAssets;
		static std::unordered_map<AssetHandle, Ref<Asset>> s_MemoryAssets;
		static AssetsChangeEventFn s_AssetsChangeCallback;
		//inline static AssetRegistry s_AssetRegistry;

	private:
		friend class ContentBrowserPanel;
		friend class ContentBrowserAsset;
		friend class ContentBrowserDirectory;

	};

}	//	END namespace RAPIER
