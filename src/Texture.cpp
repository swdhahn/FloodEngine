//
// Created by Seth H. on 12/29/2021.
//

#include "Texture.h"

engine::Texture::Texture(unsigned int* texture, int width, int height, int channels) : m_texture(texture), m_width(width), m_height(height), m_channels(channels) {

}

void engine::Texture::bind(const int& textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, *m_texture);
}

engine::Texture::~Texture() {
    glDeleteTextures(1, m_texture);
    delete m_texture;
}

unsigned int* engine::Texture::getTexture() {
    return m_texture;
}

int engine::Texture::getWidth() {
    return m_width;
}

int engine::Texture::getHeight() {
    return m_height;
}
