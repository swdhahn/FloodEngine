#ifndef FLOODENGINE_MATH_H
#define FLOODENGINE_MATH_H

#include "Platform.h"

namespace engine {
	void loadTransformationMatrix(glm::mat4x4& transformationMatrix, const glm::vec3& position, const glm::vec3& rotation);
	void loadTransformationMatrix(glm::mat4x4& transformationMatrix, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	void loadTransformationMatrix(glm::mat4x4& transformationMatrix, const glm::vec3& position, const glm::vec3& rotation, const float& scale);
}

#endif // FLOODENGINE_MATH_H