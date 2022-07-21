//
// Created by Seth H. on 1/1/2022.
//

#include "Light.h"

engine::Light::Light() : m_color(glm::vec3(1, 1, 1)), m_strength(1), m_attenuation(1, 0, 0) {

}

void engine::Light::init() {

}

void engine::Light::tick(const float& delta) {

}

void engine::Light::destroy() {

}

glm::vec3& engine::Light::getAttenuation() {
    return m_attenuation;
}

void engine::Light::setAttenuation(glm::vec3 attenuation) {
    m_attenuation = attenuation;
}

glm::vec3& engine::Light::getColor() {
    return m_color;
}

void engine::Light::setColor(glm::vec3 color) {
    m_color = color;
}

float& engine::Light::getStrength() {
    return m_strength;
}

void engine::Light::setStrength(float strength) {
    m_strength = strength;
}
