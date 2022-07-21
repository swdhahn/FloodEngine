//
// Created by Count on 9/5/2021.
//

#include "ModelEntity.h"
#include "Camera.h"


engine::ModelEntity::ModelEntity() {

}

engine::ModelEntity::ModelEntity(Model* model) : m_model(new Model*[1]{model}), m_modelCount(1) {

}

engine::ModelEntity::ModelEntity(Model** model, int modelCount) : m_model(model), m_modelCount(modelCount) {

}

engine::ModelEntity::ModelEntity(engine::ModelArray modelArray) : m_model(modelArray.m_models), m_modelCount(modelArray.m_modelCount) {

}


engine::ModelEntity::~ModelEntity() {
    for(int i = 0; i < m_modelCount; i++) {
        delete m_model[i];
    }
    delete[] m_model;
}

void engine::ModelEntity::setModel(Model** model) {
    m_model = model;
}

engine::Model** engine::ModelEntity::getModel() {
    return m_model;
}

int engine::ModelEntity::getModelCount() {
    return m_modelCount;
}

void engine::ModelEntity::tick(const float& delta) {

}

void engine::ModelEntity::updateShaderParams(ShaderProgram* shader, Model* model) {

}

