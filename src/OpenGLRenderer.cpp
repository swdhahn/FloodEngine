#include "OpenGLRenderer.h"

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            engine::logError(std::string(message));
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            engine::logWarning(std::string(message));
            break;
        case GL_DEBUG_SEVERITY_LOW:
            engine::logWarning(std::string(message));
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            //engine::logInfo(std::string(message));
            break;
        default:
            engine::logError("Unknown OpenGL Error: " + std::string(message));
    }
}

engine::OpenGLRenderer::OpenGLRenderer(uint32_t width, uint32_t height) : Renderer(width, height) {
	m_window = new Window(width, height, APPLICATION_NAME);
    glewInit();

#ifdef _DEBUG
    engine::logInfo("Debugging enabled!");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif // _DEBUG

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

engine::OpenGLRenderer::~OpenGLRenderer() {
    delete m_window;
}



void engine::OpenGLRenderer::prepass(const glm::vec4& bg) {
	glViewport(0, 0, m_width, m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(bg.x, bg.y, bg.z, bg.w);
}

void engine::OpenGLRenderer::update() {
    m_window->update();
}

void engine::OpenGLRenderer::renderModel(Model* model) {

    glBindVertexArray(model->getVao());
    for (int i = 0; i < model->getVboCount(); i++) {
        glEnableVertexArrayAttrib(model->getVao(), i);
    }

    glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, 0);

    for (int i = 0; i < model->getVboCount(); i++) {
        glDisableVertexArrayAttrib(model->getVao(), i);
    }
}


void engine::OpenGLRenderer::renderScene(Scene *scene) {

    for(auto pair : scene->m_renderQueue) {
        Material* material = pair.first;
        std::unordered_map<ModelEntity*, Model*> map2 = pair.second;

        ShaderProgram *shader = material->m_shader;
        shader->start();

        shader->loadCameraMatrix(WORLD->getCamera()->getTransformationMatrix());
        shader->loadMaterial(material);

        for(auto pair2 : map2) {
            ModelEntity *entity = pair2.first;
            Model *model = pair2.second;

            glBindVertexArray(model->getVao());
            for (int i = 0; i < model->getVboCount(); i++) {
                glEnableVertexArrayAttrib(model->getVao(), i);
            }

            shader->loadTransformationMatrix(entity->getTransformationMatrix());
            entity->updateShaderParams(shader, model);

            if (model->hasIndices()) {
                glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, 0);
            } else {
                glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
            }

            for (int i = 0; i < model->getVboCount(); i++) {
                glDisableVertexArrayAttrib(model->getVao(), i);
            }
        }
    }
    STATIC_SHADER->stop();

    for(int i = 0; i < scene->m_children.size(); i++) {
        renderScene(scene->m_children[i]);
    }

}




