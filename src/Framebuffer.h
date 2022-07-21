//
// Created by Seth H. on 1/2/2022.
//

#ifndef FLOODENGINE_FRAMEBUFFER_H
#define FLOODENGINE_FRAMEBUFFER_H

#include "Platform.h"
#include "Model.h"
#include "ShaderProgram.h"

namespace engine {

    class Framebuffer {
    public:
        Framebuffer(unsigned int width, unsigned int height, bool hasDepthAttachment, int textureCount, int* textureTypes, int samples, ShaderProgram* shader);
        Framebuffer(unsigned int width, unsigned int height, bool hasDepthAttachment, int textureCount, int* textureTypes, ShaderProgram* shader);
        ~Framebuffer();

        static void unbind(const int& windowWidth, const int& windowHeight);
        void bind();
        void resolveToFbo(Framebuffer* framebufferToBeDrawnTo);
        void resolveToScreen(const int& windowWidth, const int& windowHeight);
        void render(Framebuffer* previousBuffer);

        int getTextureCount();
        int getTexture(const int& index);
        int getFBO();
        int getWidth();
        int getHeight();

    protected:
        ShaderProgram* m_shader = nullptr;

        uint32_t* m_textures;
        uint32_t* m_buffersForDrawing;
        uint32_t m_fbo, m_rbo, m_textureCount, m_width, m_height;

        bool m_multisample;

        void createColorAttachment(const int& index, int* textureTypes);
        void createMultisampleColorAttachment(const int& index, int* textureTypes, const int& textureTypeCount, const int& samples);
        void createDepthBuffer(const int& samples);

    private:
        void checkFramebufferComplete();

    };

}

#endif //FLOODENGINE_FRAMEBUFFER_H
