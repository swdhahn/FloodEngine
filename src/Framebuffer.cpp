//
// Created by Seth H. on 1/2/2022.
//

#include "Framebuffer.h"


engine::Framebuffer::Framebuffer(uint32_t width, uint32_t height,
                                 bool hasDepthAttachment, int textureCount,
                                 int* textureTypes, int samples, ShaderProgram* shader) :
                                 m_width(width), m_height(height), m_shader(shader), m_textureCount(textureCount), m_multisample(true) {

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    m_textures = new uint32_t[m_textureCount];
    m_buffersForDrawing = new uint32_t[m_textureCount];
    glGenRenderbuffers(m_textureCount, m_textures);

    for(int i = 0; i < m_textureCount; i++) {
        m_buffersForDrawing[i] = GL_COLOR_ATTACHMENT0 + i;
        createMultisampleColorAttachment(i, textureTypes, m_textureCount, samples);
    }

    if(hasDepthAttachment) {
        createDepthBuffer(samples);
    }

    checkFramebufferComplete();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    delete[] textureTypes;
}

engine::Framebuffer::Framebuffer(uint32_t width, uint32_t height,
                                 bool hasDepthAttachment, int textureCount,
                                 int* textureTypes, ShaderProgram* shader) :
        m_width(width), m_height(height), m_shader(shader), m_textureCount(textureCount), m_multisample(false) {

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    m_textures = new uint32_t[m_textureCount];
    m_buffersForDrawing = new uint32_t[m_textureCount];
    glGenTextures(m_textureCount, m_textures);

    for(int i = 0; i < m_textureCount; i++) {
        m_buffersForDrawing[i] = GL_COLOR_ATTACHMENT0 + i;
        createColorAttachment(i, textureTypes);
    }

    if(hasDepthAttachment) {
        createDepthBuffer(0);
    }
    checkFramebufferComplete();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    delete[] textureTypes;
}

void engine::Framebuffer::checkFramebufferComplete() {
    switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
        case GL_FRAMEBUFFER_UNDEFINED:
            logErrorAndCrash("Framebuffer not complete! Framebuffer Undefined: If the target of glCheckFramebufferStatus references the Default Framebuffer (ie: FBO object number 0 is bound), and the default framebuffer does not exist, then you will get GL_FRAMEBUFFER_UNDEFINED. If the default framebuffer exists, then you always get GL_FRAMEBUFFER_COMPLETE. The rest of the rules apply when an FBO is bound.");
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            logErrorAndCrash("Framebuffer not complete! Incomplete Attachment: All attachments must be attachment complete.");
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            logErrorAndCrash("Framebuffer not complete! Missing Attachment: There must be at least one image attached to the FBO, or if OpenGL 4.3 or ARB_framebuffer_no_attachments is available, the GL_FRAMEBUFFER_DEFAULT_WIDTH and GL_FRAMEBUFFER_DEFAULT_HEIGHT parameters of the framebuffer must both be non-zero. (GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT when false).");
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            logErrorAndCrash("Framebuffer not complete! Incomplete Draw Buffer: Each draw buffers must either specify color attachment points that have images attached or must be GL_NONE. (GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER when false). Note that this test is not performed if OpenGL 4.1 or ARB_ES2_compatibility is available.");
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            logErrorAndCrash("Framebuffer not complete! Incomplete Read Buffer: If the read buffer is set, then it must specify an attachment point that has an image attached. (GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER when false). Note that this test is not performed if OpenGL 4.1 or ARB_ES2_compatibility is available.");
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            logErrorAndCrash("Framebuffer not complete! Incomplete Multisample: All images must have the same number of multisample samples. All images must also use the same fixed sample layout setting.");
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            logErrorAndCrash("Framebuffer not complete! Incomplete Layer Targets: If a layered image is attached to one attachment, then all attachments must be layered attachments. The attached layers do not have to have the same number of layers, nor do the layers have to come from the same kind of texture (a cubemap color texture can be paired with an array depth texture)");
        case GL_FRAMEBUFFER_UNSUPPORTED:
            logErrorAndCrash("Framebuffer not complete! Unsupported Framebuffer: OpenGL allows implementations to state that they do not support some combination of image formats for the attached images; they do this by returning GL_FRAMEBUFFER_UNSUPPORTED when you attempt to use an unsupported format combination.");
        case GL_FRAMEBUFFER_COMPLETE:
            return;
        default:
            logErrorAndCrash("Framebuffer not complete! Unknown reasons...");
    }
}

engine::Framebuffer::~Framebuffer() {
    if(m_multisample) {
        glDeleteRenderbuffers(m_textureCount, m_textures);
    } else {
        glDeleteTextures(m_textureCount, m_textures);
    }

    delete[] m_textures;
    delete[] m_buffersForDrawing;
}

void engine::Framebuffer::unbind(const int& windowWidth, const int& windowHeight) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
}


void engine::Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
    glDrawBuffers(m_textureCount, m_buffersForDrawing);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void engine::Framebuffer::resolveToFbo(Framebuffer* framebufferToBeDrawnTo) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferToBeDrawnTo->getFBO());
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    for(int i = 0; i < m_textureCount; i++) {
        glReadBuffer(m_buffersForDrawing[i]);
        glDrawBuffer(m_buffersForDrawing[i]);
        glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, framebufferToBeDrawnTo->getWidth(), framebufferToBeDrawnTo->getHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, framebufferToBeDrawnTo->getWidth(), framebufferToBeDrawnTo->getHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void engine::Framebuffer::resolveToScreen(const int& windowWidth, const int& windowHeight) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glDrawBuffer(GL_BACK);
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void engine::Framebuffer::render(Framebuffer* previousBuffer) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    m_shader->start();
    glBindVertexArray(MODEL_QUAD->getVao());
    glEnableVertexArrayAttrib(MODEL_QUAD->getVao(), 0);
    glEnableVertexArrayAttrib(MODEL_QUAD->getVao(), 1);

    for (int i = 0; i < previousBuffer->getTextureCount(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, previousBuffer->getTexture(i));
    }
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexArrayAttrib(MODEL_QUAD->getVao(), 0);
    glDisableVertexArrayAttrib(MODEL_QUAD->getVao(), 1);
    glBindVertexArray(0);
    m_shader->stop();
    glEnable(GL_DEPTH_TEST);
}

void engine::Framebuffer::createColorAttachment(const int& index, int* textureTypes) {

    glBindTexture(GL_TEXTURE_2D, m_textures[index]);
    glTexImage2D(GL_TEXTURE_2D, 0, textureTypes[index], m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, m_buffersForDrawing[index], GL_TEXTURE_2D, m_textures[index], 0);
}

void engine::Framebuffer::createMultisampleColorAttachment(const int& index, int* textureTypes, const int& textureTypeCount, const int& samples) {
    glBindRenderbuffer(GL_RENDERBUFFER, m_textures[index]);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, textureTypes[index], m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, m_buffersForDrawing[index], GL_RENDERBUFFER, m_textures[index]);
}

void engine::Framebuffer::createDepthBuffer(const int& samples) {

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    if(!m_multisample) {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    } else {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, m_width, m_height);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

int engine::Framebuffer::getTextureCount() {
    return m_textureCount;
}

int engine::Framebuffer::getTexture(const int& index) {
    return m_textures[index];
}

int engine::Framebuffer::getFBO() {
    return m_fbo;
}

int engine::Framebuffer::getWidth() {
    return m_width;
}

int engine::Framebuffer::getHeight() {
    return m_height;
}
