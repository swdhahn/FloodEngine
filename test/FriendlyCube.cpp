//
// Created by Seth H. on 12/24/2021.
//

#include "FriendlyCube.h"

FriendlyCube::FriendlyCube() : ModelEntity(engine::LOADER->loadModel("res/pirateShip.obj")) {

}

void FriendlyCube::init() {
    engine::logInfo("Hewo, I'ma friendly cube!");
    m_position.z = -40;
    m_position.y -= 20;
}

void FriendlyCube::tick(const float& delta) {
    //m_rotation.y += delta;
}

void FriendlyCube::destroy() {

}

void FriendlyCube::updateShaderParams(engine::ShaderProgram* shader, engine::Model* model) {

}
