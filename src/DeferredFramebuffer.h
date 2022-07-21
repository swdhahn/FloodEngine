//
// Created by Seth H. on 7/4/2022.
//

#ifndef FLOODENGINE_DEFERREDFRAMEBUFFER_H
#define FLOODENGINE_DEFERREDFRAMEBUFFER_H

#include "Application.h"
#include "ShaderProgram.h"
#include "Framebuffer.h"

namespace engine {

    class DeferredFramebuffer : public engine::Framebuffer {
    public:
        DeferredFramebuffer(unsigned int width, unsigned int height);

    };

    class DeferredFramebufferShader : public engine::ShaderProgram {
    public:
        DeferredFramebufferShader();

        void setupMaterial() override;

    };

}

#endif //FLOODENGINE_DEFERREDFRAMEBUFFER_H
