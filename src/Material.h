//
// Created by Seth H. on 12/31/2021.
//

#ifndef FLOODENGINE_MATERIAL_H
#define FLOODENGINE_MATERIAL_H

#include "Platform.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace engine {

    class Material {
    public:
        Material();
        Material(Texture* texture);
        Material(Texture** textures, int textureCount);
        ~Material();

        ShaderProgram* m_shader;

        glm::vec3 m_colorDiffuse;
        glm::vec3 m_colorSpecular;
        glm::vec3 m_colorAmbient;
        glm::vec3 m_colorEmissive;
        glm::vec3 m_colorTransparent;
        glm::vec3 m_colorReflective;

        float m_reflectivity;
        bool m_twoSided;
        float m_opacity;
        float m_shininess;
        float m_shininessStrength;

        Texture** m_textures;
        int m_textureCount;

        void updateTextures();

    };

}

#endif //FLOODENGINE_MATERIAL_H
