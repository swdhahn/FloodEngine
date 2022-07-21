//
// Created by Seth H. on 12/24/2021.
//

#include "Input.h"


engine::Action::Action(std::string name) : m_name(name) {

}

engine::Action& engine::Action::addKey(int keyCode) {
    m_keys.push_back(keyCode);
    return *this;
}

float engine::Action::getValue() {
    return m_value;
}

void engine::Action::setValue(float value) {
    m_value = value;
}

std::vector<int>& engine::Action::getKeys() {
    return m_keys;
}

std::string engine::Action::getName() {
    return m_name;
}

engine::Input::Input(Window* window) : m_window(window) {

}

void engine::Input::addAction(Action action) {
    m_actions.push_back(action);
}

float engine::Input::getActionValue(std::string name) {
    for(int i = 0; i < m_actions.size(); i++) {
        if(m_actions[i].getName() == name) {
            return m_actions[i].getValue();
        }
    }

    logError("Action could not be found: " + std::string(name));
    return 0;
}

void engine::Input::tick() {
    for(int i = 0; i < m_actions.size(); i++) {
        Action& a = m_actions[i];
        bool flag = true;
        for(int j = 0; j < a.getKeys().size(); j++) {
            int key = glfwGetKey(m_window->getWindow(), a.getKeys()[j]);
            if(key == GLFW_PRESS) {
                a.setValue(1.0f);
                flag = false;
                break;
            }
        }
        //joystick
        //mouse click
        //joystick buttons
        if(flag) {
            a.setValue(0);
        }
    }
}
