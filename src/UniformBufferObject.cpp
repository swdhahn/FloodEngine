//
// Created by Seth H. on 7/4/2022.
//

#include "UniformBufferObject.h"

int engine::UniformBufferObject::m_uboMaxSize = 0;

engine::UniformBufferObject::UniformBufferObject(const uint32_t& index, const uint32_t& size) : m_index(index) {
    if(first) {
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &m_uboMaxSize);
        first = false;
    }

    if(index >= m_uboMaxSize) {
        engine::logErrorAndCrash("UniformBufferObject with an index of " + index + std::string(" exceeds the maximum of " + m_uboMaxSize));
    }

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, size * 4, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, index, m_ubo); // connects it to an actual index!

}

void engine::UniformBufferObject::update(float* buffer, const uint32_t& size) {

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, size * 4, buffer, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void engine::UniformBufferObject::update(const uint32_t& offset, float* buffer, const uint32_t& size) {
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size * 4, buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

int engine::UniformBufferObject::getIndex() {
    return m_index;
}

int engine::UniformBufferObject::getMaxUniformBufferBindings() {
    return m_uboMaxSize;
}