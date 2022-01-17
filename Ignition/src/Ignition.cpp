#include <RAPIER.h>
#include <RAPIER/Core/Entry.h>
#include <RAPIER/Utilities/FileSystem.h>

#include "IgnitionLayer.h"

#include <Shlobj.h>
#include <windows.h>

class IgnitionApplication : public RAPIER::Application
{
public:
	IgnitionApplication(const RAPIER::ApplicationSpecification& specification)
		: Application(specification), m_UserPreferences(RAPIER::Ref<RAPIER::UserPreferences>::Create())
	{
	}

	virtual void OnInit() override
	{
		// Persistent Storage
		{
			PWSTR roamingFilePath;
			HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, NULL, &roamingFilePath);
			RP_ASSERT(resullt == S_OK);
			std::wstring filepath = roamingFilePath;
			std::replace(filepath.begin(), filepath.end(), L'\\', L'/');
			m_PersistentStoragePath = filepath + L"/RAPIER_FORGE";

			if (!std::filesystem::exists(m_PersistentStoragePath))
				std::filesystem::create_directory(m_PersistentStoragePath);
		}

		//	User Preferences
		{
			RAPIER::UserPreferencesSerializer serializer(m_UserPreferences);
			if (!std::filesystem::exists(m_PersistentStoragePath / "UserPreferences.yaml"))
				serializer.Serialize(m_PersistentStoragePath / "UserPreferences.yaml");
			else
				serializer.Deserialize(m_PersistentStoragePath / "UserPreferences.yaml");
		}

		RAPIER::IgnitionProperties ignitionProperties;
		ignitionProperties.UserPreferences = m_UserPreferences;
		ignitionProperties.ProjectOpenedCallback = std::bind(&IgnitionApplication::OnProjectOpened, this, std::placeholders::_1);

		//	Installation Path
		{
			if (RAPIER::FileSystem::HasEnvironmentVariable("RAPIER_DIR"))
				ignitionProperties.InstallPath = RAPIER::FileSystem::GetEnvironmentVariable("RAPIER_DIR");
		}

		SetShowStats(false);
		PushLayer(new RAPIER::IgnitionLayer(ignitionProperties));
	}

private:
	void OnProjectOpened(std::string projectPath)
	{
		std::filesystem::path rapierDir = RAPIER::FileSystem::GetEnvironmentVariable("RAPIER_DIR");
		std::string forgeWorkingDirectory = (rapierDir / "FORGE").string();
#ifdef RP_DEBUG
		rapierDir = rapierDir / "bin" / "Debug-windows-Win64" / "FORGE";
#else
		rapierDir = rapierDir / "bin" / "Release-windows-Win64" / "FORGE";
#endif

		std::string forgeExe = (rapierDir / "FORGE.exe").string();
		std::string commandLine = forgeExe + " " + projectPath;

		PROCESS_INFORMATION processInfo;
		STARTUPINFOA startupInfo;
		ZeroMemory(&startupInfo, sizeof(STARTUPINFOA));
		startupInfo.cb = sizeof(startupInfo);

		bool result = CreateProcessA(forgeExe.c_str(), commandLine.data(), NULL, NULL, FALSE, DETACHED_PROCESS, NULL, forgeWorkingDirectory.c_str(), &startupInfo, &processInfo);
		if (result)
		{
			CloseHandle(processInfo.hThread);
			CloseHandle(processInfo.hProcess);
		}
	}

private:
	std::filesystem::path m_PersistentStoragePath;
	RAPIER::Ref<RAPIER::UserPreferences> m_UserPreferences;
};	// END class IgnitionApplication

RAPIER::Application* CreateApplication(RAPIER::ApplicationCommandLineArgs args)
{
	RAPIER::ApplicationSpecification specification;
	specification.Name = "Ignition";
	specification.WindowWidth = 1280;
	specification.WindowHeight = 720;
	specification.StartMaximized = false;
	specification.VSync = true;
	specification.Resizeable = false;
	specification.Decorations = true;
	specification.EnableImGui = true;
	specification.WorkingDirectory = RAPIER::FileSystem::HasEnvironmentVariable("RAPIER_DIR") ? RAPIER::FileSystem::GetEnvironmentVariable("RAPIER_DIR") + "FORGE" : "../FORGE";


	return new IgnitionApplication(specification);
}	//	END CreateApplication
