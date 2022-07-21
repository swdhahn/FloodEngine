//
// Created by Seth H. on 7/4/2022.
//

#include "DeferredFramebuffer.h"

engine::DeferredFramebuffer::DeferredFramebuffer(uint32_t width, uint32_t height)
        : Framebuffer(width, height, false, 1, new int[1] {GL_RGBA}, new DeferredFramebufferShader()) {
}

engine::DeferredFramebufferShader::DeferredFramebufferShader() : engine::ShaderProgram("shaders/framebuffers/deferredVertex.glsl", "shaders/framebuffers/deferredFragment.glsl", 3) {

}

void engine::DeferredFramebufferShader::setupMaterial() {

    //getUniformBufferLocation("CameraData", engine::Application::m_cameraData);
    //getUniformBufferLocation("LightData", engine::Application::m_lightData);

    initializeTextures();
}
