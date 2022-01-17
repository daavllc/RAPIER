#pragma once

#include "Project.h"

#include <string>

namespace RAPIER
{
	class ProjectSerializer
	{
	public:
		ProjectSerializer(Ref<Project> project);

		void Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
	private:
		Ref<Project> m_Project;
	};

}	// end namespace RAPIER
