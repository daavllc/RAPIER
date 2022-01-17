#pragma once

#include "RAPIER/Core/Buffer.h"

#include <functional>
#include <filesystem>

namespace RAPIER
{
	enum class FileSystemAction
	{
		Added, Rename, Modified, Delete
	};

	struct FileSystemChangedEvent
	{
		FileSystemAction Action;
		std::string FilePath;
		std::string NewName;
		bool IsDirectory;

		std::wstring OldName = L"";
	};

	class FileSystem
	{
	public:
		static bool CreateDirectory(const std::filesystem::path& filepath);
		static bool CreateDirectory(const std::string& filepath);
		static bool Exists(const std::filesystem::path& filepath);
		static bool Exists(const std::string& filepath);
		static bool DeleteFile(const std::filesystem::path& filepath);
		static bool MoveFile(const std::filesystem::path& filepath, const std::filesystem::path& dest);
		static bool IsDirectory(const std::filesystem::path& filepath);

		static bool Move(const std::filesystem::path& oldFilePath, const std::filesystem::path& newFilePath);
		static bool Rename(const std::filesystem::path& oldFilePath, const std::filesystem::path& newFilePath);
		static bool RenameFilename(const std::filesystem::path& oldFilePath, const std::string& newName);

		static bool ShowFileInExplorer(const std::filesystem::path& path);
		static bool OpenDirectoryInExplorer(const std::filesystem::path& path);
		static bool OpenExternally(const std::filesystem::path& path);

		static bool WriteBytes(const std::filesystem::path& filepath, const Buffer& buffer);
		static Buffer ReadBytes(const std::filesystem::path& filepath);
	public:
		using FileSystemChangedCallbackFn = std::function<void(const std::vector<FileSystemChangedEvent>&)>;

		static void SetChangeCallback(const FileSystemChangedCallbackFn& callback);

		static void SkipNextFileSystemChange();
	public:
		static bool HasEnvironmentVariable(const std::string& key);
		static bool SetEnvironmentVariable(const std::string& key, const std::string& value);
		static std::string GetEnvironmentVariable(const std::string& key);
	private:
		//static unsigned long Watch(void* param);

	private:
		static FileSystemChangedCallbackFn s_Callback;
	};

}	//	END namespace RAPIER
