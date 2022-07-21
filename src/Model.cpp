#include "Model.h"

engine::Model::Model(Material* material, unsigned int vao, unsigned int vertexCount, unsigned int* vbos, unsigned int vboCount, unsigned int* indices, unsigned int indicesCount)
        : m_material(material), m_vao(vao), m_vertexCount(vertexCount * 3), m_vbos(vbos), m_vboCount(vboCount), m_indices(indices), m_indicesCount(indicesCount) {

}

engine::Model::Model(Material* material, unsigned int vao, unsigned int vertexCount, unsigned int* vbos, unsigned int vboCount)
        : m_material(material), m_vao(vao), m_vertexCount(vertexCount * 3), m_vbos(vbos), m_vboCount(vboCount), m_indices(nullptr), m_indicesCount(0) {

}

engine::Model::~Model() {
    if(m_material != nullptr) {
        delete m_material;
        m_material = nullptr;
    }

    glDeleteBuffers(m_vboCount, m_vbos);
    glDeleteVertexArrays(1, &m_vao);

    if(m_indicesCount > 0) {
        delete[] m_indices;
    }
    delete[] m_vbos;
}

unsigned int engine::Model::getVao() {
    return m_vao;
}

unsigned int engine::Model::getVboCount() {
    return m_vboCount;
}

unsigned int engine::Model::getVertexCount() {
    return m_vertexCount;
}

unsigned int* engine::Model::getIndices() {
    return m_indices;
}

unsigned int engine::Model::getIndicesCount() {
    return m_indicesCount;
}

bool engine::Model::hasIndices() {
    return getIndicesCount() > 0;
}

engine::Material* engine::Model::getMaterial() {
    return m_material;
}

engine::ModelArray::ModelArray(engine::Model **models, unsigned int modelCount) : m_models(models), m_modelCount(modelCount) {

}
