#ifndef FLOODENGINE_SCENE_LOADER_H
#define FLOODENGINE_SCENE_LOADER_H

#include <vector>
#include <fstream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture.h"
#include "Model.h"

namespace engine {

	class SceneLoader {
	public:
		SceneLoader();

        Texture* loadTexture(const char* path);

		Model* loadModel(Material* mat, float* positions, unsigned int positionsLength, float* normals, unsigned int normalLength, float* textureCoords, unsigned int textureCoordsLength, unsigned int* indices, unsigned int indicesLength);
		Model* loadModel(Material* mat, float* positions, int positionsLength, float* textureCoords, int textureCoordsLength);
		Model* loadModel(Material* mat, float* positions, int positionsLength);
		Model* loadModel(Material* mat, float* positions, int positionsLength, unsigned int* indices, unsigned int indicesLength);

        ModelArray loadModel(const char* path);

	private:

        int genVao();
        void bufferVertexData(unsigned int& vbo, int position, int dimensions, int typeOfData, unsigned int sizeOfData, void* data);
        int genElementBuffer(unsigned int indicesLength, unsigned int* indices);


	};

}

#endif // FLOODENGINE_SCENE_LOADER_H