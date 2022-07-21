#include "WorldManager.h"

#include "Camera.h"
#include "Scene.h"

engine::WorldManager::WorldManager(Scene* mainScene, Camera* camera) : m_mainCamera(camera) {
    m_scene = mainScene;
}

engine::WorldManager::~WorldManager() {
    m_scene->destroy();
}

void engine::WorldManager::tick(const float& delta) {
    m_mainCamera->_tick(delta);
    m_scene->_tick(delta);
}

void engine::WorldManager::changeCamera(Camera* camera) {
    Camera* oldCamera = m_mainCamera;
    if(camera->getWindowWidth() == 0 || camera->getWindowHeight() == 0) {
        camera->updateProjection(oldCamera->getProjectionMatrix(), oldCamera);
    }
    m_mainCamera = camera;
    delete oldCamera;
    m_mainCamera->init();
}

engine::Camera* engine::WorldManager::getCamera() {
    return m_mainCamera;
}

engine::Scene* engine::WorldManager::getScene() {
    return m_scene;
}

glm::vec4 engine::WorldManager::getSkyColor() {
    return m_skyColor;
}

void engine::WorldManager::setSkyColor(glm::vec4 skyColor) {
    m_skyColor = skyColor;
}

unsigned long engine::WorldManager::getNewId() {
    return (++m_lastIDAssigned);
}

void engine::WorldManager::addFramebuffer(Framebuffer* framebuffer) {
    m_framebuffers.push_back(framebuffer);
}

std::vector<engine::Framebuffer*>& engine::WorldManager::getFramebuffers() {
    return m_framebuffers;
}

