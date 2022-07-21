#include "Maths.h"

void engine::loadTransformationMatrix(glm::mat4x4& transformationMatrix, const glm::vec3& position, const glm::vec3& rotation) {
    transformationMatrix = glm::mat4x4(1.0f);
    transformationMatrix = glm::rotate(transformationMatrix, rotation.x, glm::vec3(1, 0, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.y, glm::vec3(0, 1, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.z, glm::vec3(0, 0, 1));
    transformationMatrix = glm::translate(transformationMatrix, position);

}

void engine::loadTransformationMatrix(glm::mat4x4& transformationMatrix, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
    transformationMatrix = glm::mat4x4(1.0f);
    transformationMatrix = glm::rotate(transformationMatrix, rotation.x, glm::vec3(1, 0, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.y, glm::vec3(0, 1, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.z, glm::vec3(0, 0, 1));
    transformationMatrix = glm::translate(transformationMatrix, position);
    transformationMatrix = glm::scale(transformationMatrix, scale);

}

void engine::loadTransformationMatrix(glm::mat4x4& transformationMatrix, const glm::vec3& position, const glm::vec3& rotation, const float& scale) {
    transformationMatrix = glm::mat4x4(1.0f);
    transformationMatrix = glm::rotate(transformationMatrix, rotation.x, glm::vec3(1, 0, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.y, glm::vec3(0, 1, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.z, glm::vec3(0, 0, 1));
    transformationMatrix = glm::translate(transformationMatrix, position);
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scale));

}
