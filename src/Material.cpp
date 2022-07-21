//
// Created by Seth H. on 12/31/2021.
//

#include "Material.h"

engine::Material::Material() :
m_shader(nullptr), m_colorDiffuse(glm::vec3(0)), m_colorSpecular(glm::vec3(0)), m_colorAmbient(glm::vec3(0)),
m_colorEmissive(glm::vec3(0)), m_colorTransparent(glm::vec3(0)), m_colorReflective(glm::vec3(0)),
m_reflectivity(0.0f), m_twoSided(false), m_opacity(1.0f), m_shininess(0.0f), m_shininessStrength(1.0f),
m_textures(new Texture*[1]{DEFAULT_TEXTURE}), m_textureCount(1)
{}
engine::Material::Material(Texture* texture) :
        m_shader(nullptr), m_colorDiffuse(glm::vec3(0)), m_colorSpecular(glm::vec3(0)), m_colorAmbient(glm::vec3(0)),
        m_colorEmissive(glm::vec3(0)), m_colorTransparent(glm::vec3(0)), m_colorReflective(glm::vec3(0)),
        m_reflectivity(0.0f), m_twoSided(false), m_opacity(1.0f), m_shininess(0.0f), m_shininessStrength(1.0f),
        m_textures(new Texture*[1]{texture}), m_textureCount(1)
{}
engine::Material::Material(Texture** textures, int textureCount) :
        m_shader(nullptr), m_colorDiffuse(glm::vec3(0)), m_colorSpecular(glm::vec3(0)), m_colorAmbient(glm::vec3(0)),
        m_colorEmissive(glm::vec3(0)), m_colorTransparent(glm::vec3(0)), m_colorReflective(glm::vec3(0)),
        m_reflectivity(0.0f), m_twoSided(false), m_opacity(1.0f), m_shininess(0.0f), m_shininessStrength(1.0f),
        m_textures(textures), m_textureCount(textureCount)
{}

engine::Material::~Material() {
    for(int i = 0; i < m_textureCount; i++) {
        if(m_textures[i] != nullptr) {
            delete m_textures[i];
            m_textures[i] = nullptr;
        }
    }
    delete[] m_textures;
}

void engine::Material::updateTextures() {
    
}
