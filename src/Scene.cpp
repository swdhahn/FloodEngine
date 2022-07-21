//
// Created by Seth H. on 12/20/2021.
//

#include "Scene.h"

engine::Scene::Scene() : m_id(0) {

}

engine::Scene::~Scene() {

}

void engine::Scene::_tick(float delta) {
    tick(delta);
    for(int i = 0; i < m_entities.size(); i++) {
        m_entities[i]->_tick(delta);
    }

    for(int i = 0; i < m_children.size(); i++) {
        m_children[i]->_tick(delta);
    }
}

void engine::Scene::addEntity(Entity* entity) {
    if(entity->getID() == 0) {
        entity->_setID(WORLD->getNewId());
    }
    m_entities.push_back(entity);

    if(ModelEntity* modelEntity = dynamic_cast<ModelEntity*>(entity)) {
        for(int i = 0; i < modelEntity->getModelCount(); i++) {
            Material* mat = modelEntity->getModel()[i]->getMaterial();
            if(mat->m_shader == nullptr) {
                mat->m_shader = STATIC_SHADER;
            }
            mat->m_shader->start();
            mat->m_shader->loadProjectionMatrix(WORLD->getCamera()->getProjectionMatrix());
            mat->m_shader->stop();
            if(m_renderQueue[mat].empty()) {
                m_renderQueue[mat] = std::unordered_map<ModelEntity*, Model*>();
            }
            m_renderQueue.at(mat).insert(std::make_pair(modelEntity, modelEntity->getModel()[i]));
        }
    } else if(Light* light = dynamic_cast<Light*>(entity)) {
        m_lights.push_back(light);
    }
    entity->init();
}


void engine::Scene::removeEntity(Entity* entity) {
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [&](Entity* e){return e->getID() == entity->getID();}), m_entities.end());
    // TODO: remove lights and from render queue
}

void engine::Scene::addChild(Scene* scene) {
    if(scene->getID() == 0) {
        scene->_setID(WORLD->getNewId());
    }
    scene->m_parent = this;
    m_children.push_back(scene);
    scene->init();
}

void engine::Scene::removeChild(Scene* scene) {
    m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&](Scene* s){return s->getID() == scene->getID();}), m_children.end());
}

unsigned long engine::Scene::getID() {
    return m_id;
}

void engine::Scene::_setID(unsigned long _id) {
    m_id = _id;
}
