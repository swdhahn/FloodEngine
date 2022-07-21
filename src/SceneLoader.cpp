#include "SceneLoader.h"

engine::SceneLoader::SceneLoader() {

}

#define STB_IMAGE_IMPLEMENTATION
#include <img/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <img/stb_image_write.h>

engine::Texture* engine::SceneLoader::loadTexture(const char* path) {
    unsigned int* tex = new unsigned int;
    int width = 0, height = 0, channels = 0;

    glGenTextures(1, tex);

    glBindTexture(GL_TEXTURE_2D, *tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Assimp::Importer importer;

    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        engine::logInfo("Failed to load texture: " + std::string(path));
    }

    stbi_image_free(data);

    return new engine::Texture(tex, width, height, channels);
}

engine::Model* engine::SceneLoader::loadModel(Material* mat, float* positions, unsigned int positionsLength, float* normals, unsigned int normalLength, float* textureCoords, unsigned int textureCoordsLength, unsigned int* indices, unsigned int indicesLength) {
    unsigned int vao = genVao();
    unsigned int elementBuffer = genElementBuffer(indicesLength, indices);
    unsigned int* vbos = new unsigned int[3];
    glGenBuffers(3, vbos);
    bufferVertexData(vbos[0], 0, 3, GL_FLOAT, sizeof(float) * positionsLength, positions);
    bufferVertexData(vbos[1], 1, 3, GL_FLOAT, sizeof(float) * normalLength, normals);
    bufferVertexData(vbos[2], 2, 3, GL_FLOAT, sizeof(float) * textureCoordsLength, textureCoords);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete[] positions;
    delete[] normals;
    delete[] textureCoords;

    return new Model(mat, vao, positionsLength, vbos, 3, indices, indicesLength);
}

engine::Model* engine::SceneLoader::loadModel(Material* mat, float* positions, int positionsLength, float* textureCoords, int textureCoordsLength) {
    unsigned int vao = genVao();
    unsigned int* vbos = new unsigned int[2];
    glGenBuffers(2, vbos);
    bufferVertexData(vbos[0], 0, 3, GL_FLOAT, positionsLength * sizeof(float), positions);
    bufferVertexData(vbos[1], 1, 3, GL_FLOAT, sizeof(float) * textureCoordsLength, textureCoords);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    delete[] positions;
    delete[] textureCoords;

    return new Model(mat, vao, positionsLength, vbos, 2);
}

engine::Model* engine::SceneLoader::loadModel(Material* mat, float* positions, int positionsLength) {
    unsigned int vao = genVao();
    unsigned int* vbos = new unsigned int[1];
    glGenBuffers(1, vbos);
    bufferVertexData(vbos[0], 0, 3, GL_FLOAT, positionsLength, positions);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return new Model(mat, vao, positionsLength, vbos, 1);
}

engine::Model* engine::SceneLoader::loadModel(Material* mat, float* positions, int positionsLength, unsigned int* indices, unsigned int indicesLength) {
    unsigned int vao = genVao();
    unsigned int elementBuffer = genElementBuffer(indicesLength, indices);
    unsigned int* vbos = new unsigned int[1];
    glGenBuffers(1, vbos);
    bufferVertexData(vbos[0], 0, 3, GL_FLOAT, sizeof(float) * positionsLength, positions);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return new Model(mat, vao, positionsLength, vbos, 1, indices, indicesLength);
}

engine::ModelArray engine::SceneLoader::loadModel(const char* path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    Model** models = new Model*[scene->mNumMeshes];
    Material* mats[scene->mNumMaterials];

    for(int i = 0; i < scene->mNumMaterials; i++) {
        mats[i] = new Material();

        aiColor3D diffuse;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
        mats[i]->m_colorDiffuse = glm::vec3(diffuse.r, diffuse.g, diffuse.b);

        aiColor3D specular;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, specular);
        mats[i]->m_colorSpecular = glm::vec3(specular.r, specular.g, specular.b);

        aiColor3D ambient;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
        mats[i]->m_colorAmbient = glm::vec3(ambient.r, ambient.g, ambient.b);

        aiColor3D emissive;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
        mats[i]->m_colorEmissive = glm::vec3(emissive.r, emissive.g, emissive.b);

        aiColor3D transparent;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_TRANSPARENT, transparent);
        mats[i]->m_colorTransparent = glm::vec3(transparent.r, transparent.g, transparent.b);

        aiColor3D reflective;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_REFLECTIVE, reflective);
        mats[i]->m_colorReflective = glm::vec3(reflective.r, reflective.g, reflective.b);

        scene->mMaterials[i]->Get(AI_MATKEY_REFLECTIVITY, mats[i]->m_reflectivity);
        scene->mMaterials[i]->Get(AI_MATKEY_TWOSIDED, mats[i]->m_twoSided);
        scene->mMaterials[i]->Get(AI_MATKEY_OPACITY, mats[i]->m_opacity);
        scene->mMaterials[i]->Get(AI_MATKEY_SHININESS, mats[i]->m_shininess);
        scene->mMaterials[i]->Get(AI_MATKEY_SHININESS_STRENGTH, mats[i]->m_shininessStrength);
    }

    for(int k = 0; k < scene->mNumMeshes; k++) {
        aiMesh* mesh = scene->mMeshes[k];

        unsigned int indicesCount = 0;
        for (int i = 0; i < mesh->mNumFaces; i++) {
            indicesCount += mesh->mFaces[i].mNumIndices;
        }

        unsigned int *indices = new unsigned int[indicesCount];
        int p = 0;
        for (int i = 0; i < mesh->mNumFaces; i++) {
            for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
                indices[p++] = mesh->mFaces[i].mIndices[j];
            }
        }
        float *vertices = new float[mesh->mNumVertices * 3];
        float *normals = new float[mesh->mNumVertices * 3];
        float *uvs = new float[mesh->mNumVertices * 3];
        for (int i = 0; i < mesh->mNumVertices; i++) {
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
            normals[i * 3] = mesh->mNormals[i].x;
            normals[i * 2 + 1] = mesh->mNormals[i].y;
            normals[i * 2 + 2] = mesh->mNormals[i].z;
            uvs[i * 3] = mesh->mTextureCoords[0][i].x;
            uvs[i * 3 + 1] = mesh->mTextureCoords[0][i].y;
            uvs[i * 3 + 2] = mesh->mTextureCoords[0][i].z;
        }

        int vao = genVao();
        genElementBuffer(mesh->mNumFaces * 3, indices);
        unsigned int *vbos = new unsigned int[3];
        glGenBuffers(3, vbos);
        bufferVertexData(vbos[0], 0, 3, GL_FLOAT, mesh->mNumVertices * 3 * sizeof(float), vertices);
        bufferVertexData(vbos[1], 1, 3, GL_FLOAT, mesh->mNumVertices * 3 * sizeof(float), normals);
        bufferVertexData(vbos[2], 2, 3, GL_FLOAT, mesh->mNumVertices * 3 * sizeof(float), uvs);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        delete[] vertices;
        delete[] normals;
        delete[] uvs;

        models[k] = new Model(mats[mesh->mMaterialIndex], vao, mesh->mNumVertices, vbos, 3, indices, indicesCount);
    }

    return ModelArray(models, scene->mNumMeshes);
}


int engine::SceneLoader::genVao() {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

int engine::SceneLoader::genElementBuffer(unsigned int indicesLength, unsigned int* indices) {
    unsigned int elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    return elementBuffer;
}

void engine::SceneLoader::bufferVertexData(unsigned int& vbo, int position, int dimensions, int typeOfData, unsigned int sizeOfData, void* data) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);
    glVertexAttribPointer(position, dimensions, typeOfData, false, 0, 0);
}
