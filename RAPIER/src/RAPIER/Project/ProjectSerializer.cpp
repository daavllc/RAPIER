#include "rppch.h"
#include "ProjectSerializer.h"

#include "RAPIER/Utilities/YAMLSerializationHelpers.h"

#include <yaml-cpp/yaml.h>

#include <filesystem>

namespace RAPIER
{
	ProjectSerializer::ProjectSerializer(Ref<Project> project)
		: m_Project(project)
	{}

	void ProjectSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Project" << YAML::Value;
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Name" << YAML::Value << m_Project->m_Config.Name;
			out << YAML::Key << "AudioCommandsRegistryPath" << YAML::Value << m_Project->m_Config.AudioCommandsRegistryPath;
			out << YAML::Key << "ScriptModulePath" << YAML::Value << m_Project->m_Config.ScriptModulePath;
			out << YAML::Key << "StartScene" << YAML::Value << m_Project->m_Config.StartScene;
			out << YAML::Key << "ReloadAssemblyOnPlay" << YAML::Value << m_Project->m_Config.ReloadAssemblyOnPlay;

			out << YAML::EndMap;
		}
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	bool ProjectSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		RP_CORE_ASSERT(stream);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Project"])
			return false;

		YAML::Node rootNode = data["Project"];
		if (!rootNode["Name"])
			return false;

		auto& config = m_Project->m_Config;
		config.Name = rootNode["Name"].as<std::string>();

		config.AssetDirectory = rootNode["AssetDirectory"].as<std::string>();
		config.AssetRegistryPath = rootNode["AssetRegistry"].as<std::string>();

		if (rootNode["AudioCommandsRegistryPath"])
			config.AudioCommandsRegistryPath = rootNode["AudioCommandsRegistryPath"].as<std::string>();

		config.ScriptModulePath = rootNode["ScriptModulePath"].as<std::string>();
		config.StartScene = rootNode["StartScene"] ? rootNode["StartScene"].as<std::string>() : "";

		config.ReloadAssemblyOnPlay = rootNode["ReloadAssemblyOnPlay"] ? rootNode["ReloadAssemblyOnPlay"].as<bool>() : true;

		std::filesystem::path projectPath = filepath;
		config.ProjectFileName = projectPath.filename().string();
		config.ProjectDirectory = projectPath.parent_path().string();

		m_Project->OnDeserialized();
		return true;
	}
}	//	END namespace RAPIER
