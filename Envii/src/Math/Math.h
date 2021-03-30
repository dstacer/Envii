#pragma once

#include <glm/glm.hpp>

namespace Envii
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTrans, glm::vec3& outRot, glm::vec3& outScale);
}