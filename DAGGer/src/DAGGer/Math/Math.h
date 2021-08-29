/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the defines for DAGGer mathematics
/////////////////////////////
#pragma once

#include <glm/glm.hpp>

namespace DAGGer::Math
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& rotation, glm::vec3& outScale);

}	//	END namespace DAGGer::Math