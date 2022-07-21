#include "ShaderProgram.h"
#include "Material.h"

engine::ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile, int textureCount) : m_textureCount(textureCount) {
    unsigned int vertexId, fragmentId;
    loadShader(GL_VERTEX_SHADER, vertexFile, vertexId);
    loadShader(GL_FRAGMENT_SHADER, fragmentFile, fragmentId);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexId);
    glAttachShader(m_program, fragmentId);

    glLinkProgram(m_program);
    glDetachShader(m_program, vertexId);
    glDetachShader(m_program, fragmentId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    glValidateProgram(m_program);

    setupMaterial();
}

engine::ShaderProgram::ShaderProgram(const char* vertexFile, const char* geometryFile, const char* fragmentFile, int textureCount) : m_textureCount(textureCount) {
    unsigned int vertexId, fragmentId, geometryId;
    loadShader(GL_VERTEX_SHADER, vertexFile, vertexId);
    loadShader(GL_FRAGMENT_SHADER, fragmentFile, fragmentId);
    loadShader(GL_GEOMETRY_SHADER, geometryFile, geometryId);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexId);
    glAttachShader(m_program, fragmentId);
    glAttachShader(m_program, geometryId);

    glLinkProgram(m_program);
    glDetachShader(m_program, vertexId);
    glDetachShader(m_program, fragmentId);
    glDetachShader(m_program, geometryId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    glDeleteShader(geometryId);

    glValidateProgram(m_program);

    setupMaterial();
}

engine::ShaderProgram::ShaderProgram(const char* vertexFile, const char* tesselationControlFile, const char* tesselationEvaluationFile, const char* fragmentFile, int textureCount) : m_textureCount(textureCount) {
    unsigned int vertexId, fragmentId, tesselationControlId, tesselationEvaluationId;
    loadShader(GL_VERTEX_SHADER, vertexFile, vertexId);
    loadShader(GL_FRAGMENT_SHADER, fragmentFile, fragmentId);
    loadShader(GL_TESS_CONTROL_SHADER, tesselationControlFile, tesselationControlId);
    loadShader(GL_TESS_EVALUATION_SHADER, tesselationEvaluationFile, tesselationEvaluationId);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexId);
    glAttachShader(m_program, fragmentId);
    glAttachShader(m_program, tesselationControlId);
    glAttachShader(m_program, tesselationEvaluationId);

    glLinkProgram(m_program);
    glDetachShader(m_program, vertexId);
    glDetachShader(m_program, fragmentId);
    glDetachShader(m_program, tesselationControlId);
    glDetachShader(m_program, tesselationEvaluationId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    glDeleteShader(tesselationControlId);
    glDeleteShader(tesselationEvaluationId);

    glValidateProgram(m_program);

    setupMaterial();
}

engine::ShaderProgram::ShaderProgram(const char* vertexFile, const char* tesselationControlFile, const char* tesselationEvaluationFile, const char* geometryFile, const char* fragmentFile, int textureCount) : m_textureCount(textureCount) {
    unsigned int vertexId, fragmentId, geometryId, tesselationControlId, tesselationEvaluationId;
    loadShader(GL_VERTEX_SHADER, vertexFile, vertexId);
    loadShader(GL_FRAGMENT_SHADER, fragmentFile, fragmentId);
    loadShader(GL_TESS_CONTROL_SHADER, tesselationControlFile, tesselationControlId);
    loadShader(GL_TESS_EVALUATION_SHADER, tesselationEvaluationFile, tesselationEvaluationId);
    loadShader(GL_GEOMETRY_SHADER, geometryFile, geometryId);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexId);
    glAttachShader(m_program, fragmentId);
    glAttachShader(m_program, tesselationControlId);
    glAttachShader(m_program, tesselationEvaluationId);
    glAttachShader(m_program, geometryId);

    glLinkProgram(m_program);
    glDetachShader(m_program, vertexId);
    glDetachShader(m_program, fragmentId);
    glDetachShader(m_program, tesselationControlId);
    glDetachShader(m_program, tesselationEvaluationId);
    glDetachShader(m_program, geometryId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    glDeleteShader(tesselationControlId);
    glDeleteShader(tesselationEvaluationId);
    glDeleteShader(geometryId);

    glValidateProgram(m_program);

    setupMaterial();
}

engine::ShaderProgram::~ShaderProgram() {
    delete[] m_textures;
    glDeleteProgram(m_program);
}

void engine::ShaderProgram::start() {
    glUseProgram(m_program);
}

void engine::ShaderProgram::stop() {
    glUseProgram(0);
}

void engine::ShaderProgram::loadShader(const unsigned int type, const char* path, unsigned int &shaderId) {
    // Reading file
    logInfo("Loading shader: " + std::string(path));
    std::string data;
    std::ifstream infile(path);
    if(!infile.good()) {
        logError(std::string("Could not access file in path: \"" + std::string(path) + std::string("\"")).c_str());
    }
    std::string line;
    while(std::getline(infile, line)) {
        data.append(line + "\n");
    }
    infile.close();

    // Actual shader and opengl stuffies!!
    shaderId = glCreateShader(type);

    int dataLength = data.length();
    const char* shaderData = data.c_str();
    glShaderSource(shaderId, 1, &shaderData, &dataLength);
    glCompileShader(shaderId);

    int value;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &value);
    
    if(value == GL_FALSE) {
        int len = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &len);
        GLsizei length;
        std::vector<GLchar> infoLog(len);
        glGetShaderInfoLog(shaderId, len, NULL, infoLog.data());
        logErrorAndCrash(std::string("Error with shader: " + std::string(path) + std::string("\n") + std::string(infoLog.data())).c_str());
    }
    
}

void engine::ShaderProgram::getUniformLocation(const char* uniformName, int &returnedLocation) {
    returnedLocation = glGetUniformLocation(m_program, uniformName);
    switch(returnedLocation) {
        case GL_INVALID_VALUE:
            logError(std::string("Invalid value from " + std::to_string(returnedLocation)).c_str());
        break;
        case GL_INVALID_OPERATION:
            logError(std::string("Invalid value from " + std::to_string(returnedLocation) + std::string(" is not using a proper program, or it has not been linked properly")).c_str());
        break;
    }
}

void engine::ShaderProgram::getUniformBufferLocation(const char* uniformBufferName, UniformBufferObject* object) {
    int uniformIndex = glGetUniformBlockIndex(m_program, uniformBufferName);
    switch(uniformIndex) {
        case GL_INVALID_VALUE:
            engine::logError(std::string("UniformBufferObject \"") + uniformBufferName + std::string("\" has an invalid value!"));
            break;
        case GL_INVALID_OPERATION:
            engine::logError("The program entered is not a valid, usable program, or it has not been linked successfully");
            break;
        case -1:
            engine::logError(std::string("UniformBufferObject \"") + uniformBufferName + std::string("\" is not used"));
            break;
    }

    glUniformBlockBinding(m_program, uniformIndex, object->getIndex());
}

void engine::ShaderProgram::loadBool(const int &location, const bool &value) {
    glUniform1i(location, value);
}

void engine::ShaderProgram::loadInt(const int &location, const int &value) {
    glUniform1i(location, value);
}

void engine::ShaderProgram::loadFloat(const int &location, const float &value) {
    glUniform1f(location, value);
}

void engine::ShaderProgram::loadVector2(const int &location, const glm::vec2 &value) {
    glUniform2f(location, value.x, value.y);
}

void engine::ShaderProgram::loadVector3(const int &location, const glm::vec3 &value) {
    glUniform3f(location, value.x, value.y, value.z);
}

void engine::ShaderProgram::loadVector4(const int &location, const glm::vec4 &value) {
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void engine::ShaderProgram::loadMatrix4x4(const int &location, const glm::mat4x4 &value) {
    glUniformMatrix4fv(location, 1, false, &value[0][0]);
}

void engine::ShaderProgram::loadMaterial(const Material* material) {
    loadVector3(m_colorDiffuse, material->m_colorDiffuse);
    loadVector3(m_colorSpecular, material->m_colorSpecular);
    loadVector3(m_colorAmbient, material->m_colorAmbient);
    loadVector3(m_colorEmissive, material->m_colorEmissive);
    loadVector3(m_colorTransparent, material->m_colorTransparent);
    loadVector3(m_colorReflective, material->m_colorReflective);

    loadFloat(m_reflectivity, material->m_reflectivity);
    loadFloat(m_opacity, material->m_opacity);
    loadFloat(m_shininess, material->m_shininess);
    loadFloat(m_shininessStrength, material->m_shininessStrength);

    for(int i = 0; i < material->m_textureCount; i++) {
        material->m_textures[i]->bind(i);
    }

}

void engine::ShaderProgram::setupMaterial() {
    getUniformLocation("projectionMatrix", m_projectionMatrix);
    getUniformLocation("transformationMatrix", m_transformationMatrix);
    getUniformLocation("cameraMatrix", m_cameraMatrix);

    getUniformLocation("colorDiffuse", m_colorDiffuse);
    getUniformLocation("colorSpecular", m_colorSpecular);
    getUniformLocation("colorAmbient", m_colorAmbient);
    getUniformLocation("colorEmissive", m_colorEmissive);
    getUniformLocation("colorTransparent", m_colorTransparent);
    getUniformLocation("colorReflective", m_colorReflective);
    getUniformLocation("reflectivity", m_reflectivity);
    getUniformLocation("opacity", m_opacity);
    getUniformLocation("shininess", m_shininess);
    getUniformLocation("shininessStrength", m_shininessStrength);

    initializeTextures();

}

void engine::ShaderProgram::initializeTextures() {
    if(m_textureCount > 0) {
        m_textures = new int[m_textureCount];
    }

    for(int i = 0; i < m_textureCount; i++) {
        getUniformLocation(std::string("texture" + std::to_string(i)).c_str(), m_textures[i]);
    }
    start();
    for(int i = 0; i < m_textureCount; i++) {
        loadInt(m_textures[i], i);
    }
    stop();
}

void engine::ShaderProgram::loadProjectionMatrix(const glm::mat4x4 &projectionMatrix) {
    loadMatrix4x4(m_projectionMatrix, projectionMatrix);
}

void engine::ShaderProgram::loadCameraMatrix(const glm::mat4x4 &cameraMatrix) {
    loadMatrix4x4(m_cameraMatrix, cameraMatrix);
}

void engine::ShaderProgram::loadTransformationMatrix(const glm::mat4x4 &transformationMatrix) {
    loadMatrix4x4(m_transformationMatrix, transformationMatrix);
}
