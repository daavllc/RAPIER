#pragma once

#include <glm/glm.hpp>

namespace RAPIER::Math
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& rotation, glm::vec3& outScale);

}	//	END namespace RAPIER::Math