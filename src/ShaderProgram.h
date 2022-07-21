#ifndef FLOODENGINE_SHADERPROGRAM_H
#define FLOODENGINE_SHADERPROGRAM_H

#include "Platform.h"
#include "UniformBufferObject.h"
#include <string>
#include <fstream>
#include <vector>

namespace engine {

    class Material;

    class ShaderProgram {
    public:
        virtual ~ShaderProgram() = 0;

        void start();
        void stop();
        void loadMaterial(const Material* material);
        
        void loadProjectionMatrix(const glm::mat4x4& projectionMatrix);
        void loadCameraMatrix(const glm::mat4x4& cameraMatrix);
        void loadTransformationMatrix(const glm::mat4x4& transformationMatrix);

    protected:
        ShaderProgram(const char* vertexFile, const char* fragmentFile, int textureCount);
        ShaderProgram(const char* vertexFile, const char* geometryFile, const char* fragmentFile, int textureCount);
        ShaderProgram(const char* vertexFile, const char* tesselationControlFile, const char* tesselationEvaluationFile, const char* fragmentFile, int textureCount);
        ShaderProgram(const char* vertexFile, const char* tesselationControlFile, const char* tesselationEvaluationFile, const char* geometryFile, const char* fragmentFile, int textureCount);

        void getUniformLocation(const char* uniformName, int& returnedLocation);
        void getUniformBufferLocation(const char* uniformBufferName, UniformBufferObject* object);
        void loadBool(const int& location, const bool& value);
        void loadInt(const int& location, const int& value);
        void loadFloat(const int& location, const float& value);
        void loadVector2(const int& location, const glm::vec2& value);
        void loadVector3(const int& location, const glm::vec3& value);
        void loadVector4(const int& location, const glm::vec4& value);
        void loadMatrix4x4(const int& location, const glm::mat4x4& value);

        virtual void setupMaterial();
        void initializeTextures();

    private:
        void loadShader(const unsigned int type, const char* path, unsigned int& shaderId);

        unsigned int m_program;

    protected:
        int m_projectionMatrix,m_transformationMatrix,m_cameraMatrix;
        int m_colorDiffuse, m_colorSpecular, m_colorAmbient, m_colorEmissive, m_colorTransparent, m_colorReflective;
        int m_reflectivity, m_opacity, m_shininess, m_shininessStrength;
        int* m_textures;
        int m_textureCount;


    };

}

#endif // FLOODENGINE_SHADERPROGRAM_H