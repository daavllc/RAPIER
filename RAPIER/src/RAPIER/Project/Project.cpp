#include "rppch.h"
#include "Project.h"

namespace RAPIER
{
	Project::Project() {}
	Project::~Project() {}

	void Project::SetActive(Ref<Project> project)
	{
		if (s_ActiveProject)
		{
		}

		s_ActiveProject = project;
		if (s_ActiveProject)
		{
		}
	}

	void Project::OnDeserialized()
	{
	}

}	//	END namespace RAPIER
