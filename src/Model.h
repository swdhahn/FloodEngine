#ifndef FLOODENGINE_MODEL_H
#define FLOODENGINE_MODEL_H

#include "Platform.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ShaderProgram.h"
#include "StaticShader.h"
#include "Material.h"

namespace engine {

    extern StaticShader* STATIC_SHADER;

	class Model {
	public:
        Model(Material* mat, unsigned int vao, unsigned int vertexCount, unsigned int* vbos, unsigned int vboCount, unsigned int* indices, unsigned int indicesCount);
        Model(Material* mat, unsigned int vao, unsigned int vertexCount, unsigned int* vbos, unsigned int vboCount);
		~Model();

		unsigned int getVao();
		unsigned int getVertexCount();
		unsigned int getVboCount();
		unsigned int* getIndices();
		unsigned int getIndicesCount();
		bool hasIndices();
        Material* getMaterial();

	private:
        Material* m_material = nullptr;
		unsigned int m_vao;
		unsigned int m_vertexCount;
		unsigned int m_indicesCount;
		unsigned int* m_indices = nullptr;
		unsigned int* m_vbos = nullptr;
		unsigned int m_vboCount;

	};

    class ModelArray {
    public:
        ModelArray(Model **models, unsigned int modelCount);

        Model** m_models;
        unsigned int m_modelCount;
    };

    extern Model* MODEL_QUAD;

}

#endif // FLOODENGINE_MODEL_H