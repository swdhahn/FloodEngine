//
// Created by Seth H. on 12/26/2021.
//

#include "Terrain.h"

engine::Terrain::Terrain(float sizeX, float sizeZ, uint32_t vertexX, uint32_t vertexZ)
: m_sizeX(sizeX), m_sizeZ(sizeZ), m_vertexX(vertexX), m_vertexZ(vertexZ) {
    m_position.z = -20;
}

void engine::Terrain::updateShaderParams(ShaderProgram* shader, Model* model) {

}

engine::Model* engine::Terrain::generate() {
    unsigned int* indices = new unsigned int[(m_vertexX - 1) * (m_vertexZ-1) * 6];
    float *vertices = new float[m_vertexX * m_vertexZ * 3];
    float *normals = new float[m_vertexX * m_vertexZ * 3];
    float *textureCoords = new float[m_vertexX * m_vertexZ * 3];

    m_heights = new float[m_vertexX * m_vertexZ];

    int i = 0, j = 0;
    for(int x = 0; x < m_vertexX; x++) {
        for(int z = 0; z < m_vertexZ; z++) {
            m_heights[x + z * m_vertexX] = cos(x) * 3;

            vertices[i * 3] = ((float)x / (float)(m_vertexX - 1)) * m_sizeX;
            vertices[i * 3 + 1] = m_heights[x + z * m_vertexX];
            vertices[i * 3 + 2] = ((float)z / (float)(m_vertexZ - 1)) * m_sizeZ;
            glm::vec3 normal = calcNormal(x, z);
            normals[i * 3] = normal.x;
            normals[i * 3 + 1] = normal.y;
            normals[i * 3 + 2] = normal.z;
            textureCoords[i * 3] = ((float)x / (float)(m_vertexX - 1));
            textureCoords[i * 3 + 1] = ((float)z / (float)(m_vertexZ - 1));

            i++;

            if(x < m_vertexX - 1 && z < m_vertexZ - 1) {
                int topLeft = (z * m_vertexX) + x;
                int topRight = topLeft + 1;
                int bottomLeft = ((z + 1) * m_vertexX) + x;
                int bottomRight = bottomLeft + 1;

                indices[j * 6] = topLeft;
                indices[j * 6 + 1] = topRight;
                indices[j * 6 + 2] = bottomLeft;

                indices[j * 6 + 3] = topRight;
                indices[j * 6 + 4] = bottomRight;
                indices[j * 6 + 5] = bottomLeft;

                j++;
            }

        }
    }

    Material* terrainMaterial = new Material();

    return LOADER->loadModel(terrainMaterial, vertices, m_vertexX * m_vertexZ * 3, normals, m_vertexX * m_vertexZ * 3, textureCoords, m_vertexX * m_vertexZ * 3, indices, (m_vertexX - 1) * (m_vertexZ - 1) * 6);
}

glm::vec3 engine::Terrain::calcNormal(int x, int y) {
    return glm::vec3();
}

float engine::Terrain::getHeight(const glm::vec3& pos) {
    return m_heights[(int)(pos.x + pos.z * m_vertexX)];
}

void engine::Terrain::init() {

}

void engine::Terrain::tick(const float& delta) {

}

void engine::Terrain::destroy() {

}

engine::Terrain::~Terrain() {
    delete[] m_heights;
}
