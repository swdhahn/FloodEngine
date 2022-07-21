#include "Entity.h"

engine::Entity::Entity() : m_position(0), m_rotation(0), m_scale(1), m_id(0) {

}

engine::Entity::Entity(unsigned long _id) : m_position(0), m_rotation(0), m_scale(1) {

}

engine::Entity::~Entity() {

}

void engine::Entity::_tick(const float& delta) {
	tick(delta);
	loadTransformationMatrix(m_transformationMatrix, m_position, m_rotation, m_scale);
}

glm::mat4x4 engine::Entity::getTransformationMatrix() {
    return m_transformationMatrix;
}

glm::vec3& engine::Entity::getPosition() {
	return m_position;
}

glm::vec3& engine::Entity::getRotation() {
	return m_rotation;
}

glm::vec3& engine::Entity::getScale() {
	return m_scale;
}

void engine::Entity::setPosition(glm::vec3 position) {
	m_position = position;
}

void engine::Entity::setRotation(glm::vec3 rotation) {
	m_rotation = rotation;
}

void engine::Entity::setScale(glm::vec3 scale) {
	m_scale = scale;
}

void engine::Entity::setScale(float scale) {
	m_scale = glm::vec3(scale);
}

unsigned long engine::Entity::getID() {
    return m_id;
}

void engine::Entity::_setID(unsigned long _id) {
    m_id = _id;
}

