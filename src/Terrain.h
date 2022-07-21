//
// Created by Seth H. on 12/26/2021.
//

#ifndef FLOODENGINE_TERRAIN_H
#define FLOODENGINE_TERRAIN_H

#include "GeneratedModelEntity.h"

namespace engine {

    class Terrain : public GeneratedModelEntity {
    public:
        Terrain(float sizeX, float sizeZ, uint32_t vertexX, uint32_t vertexZ);
        ~Terrain();

        Model* generate() override;

        float getHeight(const glm::vec3& pos);

        void init() override;
        void tick(const float& delta) override;
        void destroy() override;

        void updateShaderParams(ShaderProgram* shader, Model* model) override;

    private:
        float m_sizeX, m_sizeZ;
        uint32_t m_vertexX, m_vertexZ;

        float* m_heights = nullptr;

        glm::vec3 calcNormal(int x, int y);

    };



}


#endif //FLOODENGINE_TERRAIN_H
