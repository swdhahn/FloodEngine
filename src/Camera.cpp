#include "Camera.h"


engine::Camera::Camera() : Entity() {

}

engine::Camera::Camera(uint32_t windowWidth, uint32_t windowHeight, float nearPlane, float farPlane, float fov)
: m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_near(nearPlane), m_far(farPlane), m_fov(fov), Entity() {
    recreateProjectionMatrix(windowWidth, windowHeight, nearPlane, farPlane, fov);
}

void engine::Camera::updateProjection(uint32_t windowWidth, uint32_t windowHeight, float nearPlane, float farPlane, float fov) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_near = nearPlane;
    m_far = farPlane;
    m_fov = fov;
    recreateProjectionMatrix(windowWidth, windowHeight, nearPlane, farPlane, fov);
}

void engine::Camera::updateProjection(glm::mat4x4 projectionMatrix, Camera* cam) {
    m_windowWidth = cam->getWindowWidth();
    m_windowHeight = cam->getWindowHeight();
    m_near = cam->getNearPlane();
    m_far = cam->getFarPlane();
    m_fov = cam->getFOV();
    m_projectionMatrix = projectionMatrix;
}

engine::Camera::~Camera() {

}

void engine::Camera::tick(const float& delta) {

}

void engine::Camera::init() {

}

void engine::Camera::destroy() {

}

glm::mat4x4 engine::Camera::recreateProjectionMatrix(uint32_t windowWidth, uint32_t windowHeight, float nearPlane, float farPlane, float fov) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_near = nearPlane;
    m_far = farPlane;
    m_fov = fov;
    return m_projectionMatrix = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, nearPlane, farPlane);
}

glm::mat4x4 engine::Camera::getProjectionMatrix() {
    return m_projectionMatrix;
}

uint32_t engine::Camera::getWindowWidth() {
    return m_windowWidth;
}

uint32_t engine::Camera::getWindowHeight() {
    return m_windowHeight;
}

float engine::Camera::getNearPlane() {
    return m_near;
}

float engine::Camera::getFarPlane() {
    return m_far;
}

float engine::Camera::getFOV() {
    return m_fov;
}

