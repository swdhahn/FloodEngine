//
// Created by Seth H. on 12/24/2021.
//

#include "PlayerCamera.h"

void PlayerCamera::init() {

}

void PlayerCamera::destroy() {

}

void PlayerCamera::tick(const float& delta) {


    m_position.z +=
            engine::INPUT->getActionValue("move_forward") * delta * 10 -
            engine::INPUT->getActionValue("move_backward") * delta * 10;

    m_position.x +=
            engine::INPUT->getActionValue("move_left") * delta * 10 -
            engine::INPUT->getActionValue("move_right") * delta * 10;

    m_position.y +=
            engine::INPUT->getActionValue("move_down") * delta * 10 -
            engine::INPUT->getActionValue("move_up") * delta * 10;

    m_rotation.y += engine::INPUT->getActionValue("look_right") * delta - engine::INPUT->getActionValue("look_left") * delta;
    m_rotation.x += engine::INPUT->getActionValue("look_up") * delta - engine::INPUT->getActionValue("look_down") * delta;
}
