#include "Application.h"

engine::WorldManager* engine::WORLD;
engine::StaticShader* engine::STATIC_SHADER;
engine::SceneLoader* engine::LOADER;
engine::Input* engine::INPUT;
engine::Texture* engine::DEFAULT_TEXTURE;
engine::Model* engine::MODEL_QUAD;

engine::UniformBufferObject* engine::Application::m_cameraData = nullptr;
engine::UniformBufferObject* engine::Application::m_lightData = nullptr;

engine::Application::Application(ApplicationData& appData) : m_width(appData.m_windowWidth), m_height(appData.m_windowHeight) {
	engine::logInfo(std::string(APPLICATION_NAME ":v") + std::to_string(VERSION_MAJOR(APPLICATION_VERSION)) + "." + std::to_string(VERSION_MINOR(APPLICATION_VERSION)) + "." + std::to_string(VERSION_PATCH(APPLICATION_VERSION)) +
		(" - w/" ENGINE_NAME ":v") + std::to_string(VERSION_MAJOR(ENGINE_VERSION)) + "." + std::to_string(VERSION_MINOR(ENGINE_VERSION)) + "." + std::to_string(VERSION_PATCH(ENGINE_VERSION)));

	if (!glfwInit()) {
		logErrorAndCrash("Could not initialize GLFW!!!");
	}

	m_renderer = new engine::OpenGLRenderer(m_width, m_height);

	WORLD = new WorldManager(appData.m_scene, new Camera(m_width, m_height, 0.1f, 1000.0f, 70.0f));

    INPUT = new Input(m_renderer->getWindow());

	run();
}

engine::Application::~Application() {
	delete m_renderer;
}

void engine::Application::tick(const float &delta) {
    WORLD->tick(delta);
    INPUT->tick();
    m_renderer->update();
}

void engine::Application::render() {



    if(WORLD->getFramebuffers().size() > 0) {
        m_screenBuffer->bind();
    } else {
        Framebuffer::unbind(m_width, m_height);
    }

    m_renderer->prepass(WORLD->getSkyColor());
    m_renderer->renderScene(WORLD->getScene());

    if(WORLD->getFramebuffers().size() > 0) {
        WORLD->getFramebuffers()[0]->bind();
        WORLD->getFramebuffers()[0]->render(m_screenBuffer);

        for(int i = 1; i < WORLD->getFramebuffers().size(); i++) {
            WORLD->getFramebuffers()[i]->bind();
            WORLD->getFramebuffers()[i]->render(WORLD->getFramebuffers()[i - 1]);
        }

        //WORLD->getFramebuffers()[WORLD->getFramebuffers().size()-1]->unbind(m_width, m_height);
        WORLD->getFramebuffers()[WORLD->getFramebuffers().size()-1]->resolveToScreen(m_width, m_height);
    }//*/
    //m_screenBuffer->resolveToScreen(m_width, m_height);
}

void engine::Application::run() {
	float delta = 0;
	float last = 0;
	int frames = 0;
	float timer1 = 0;

	LOADER = new SceneLoader();
	STATIC_SHADER = new StaticShader();

    DEFAULT_TEXTURE = LOADER->loadTexture("res/default.png");
    MODEL_QUAD = LOADER->loadModel(new Material(),
                                   new float[18] {-1, -1, 0, /**/
                                                  1, -1, 0, /**/
                                                  -1, 1, 0, /**/
                                                  1, -1, 0, /**/
                                                  1, 1, 0, /**/
                                                  -1, 1, 0
                                                  }, 6 * 3,
                                   new float[18] {0, 0, 0, /**/
                                                  1, 0, 0, /**/
                                                  0, 1, 0, /**/
                                                  1, 0, 0, /**/
                                                  1, 1, 0,/**/
                                                  0, 1, 0 /**/
                                                  }, 6 * 3);

    WORLD->getScene()->init();

    m_screenBuffer = new Framebuffer(WORLD->getCamera()->getWindowWidth(), WORLD->getCamera()->getWindowHeight(), true,
                                     3, new int[3] {GL_RGBA, GL_RGBA16F, GL_RGBA32F}, nullptr);



    int cameraDataSize = 48 + 4, lightDataSize = 1024 * 3 * 4 + 4;
    // Camera - Camera Matrix, Projection Matrix, Camera Projection Matrix, Camera Position
    m_cameraData = new UniformBufferObject(1, cameraDataSize);
    // Lights: 1024 * (l_pos + l_color + l_attenuation) + l_count
    m_lightData = new UniformBufferObject(2, lightDataSize);

    float* cameraData = new float[cameraDataSize];
    float* lightData = new float[lightDataSize];

	while (!m_renderer->getWindow()->shouldClose()) {
		float current = getElapsedTime();
		float currentMillis = getElapsedTimeMillis();
		delta = current - last;
		last = current;



        // ###################################################

        glm::mat4 proj = WORLD->getCamera()->getProjectionMatrix();
        glm::mat4 cam = WORLD->getCamera()->getTransformationMatrix();
        glm::mat4 camProj = proj * cam;
        glm::vec3 pos = WORLD->getCamera()->getPosition();
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cameraData[i * 4 + j] = proj[i][j];
                cameraData[i * 4 + j + 16] = cam[i][j];
                cameraData[i * 4 + j + 32] = camProj[i][j];
            }
        }
        cameraData[48] = pos.x;
        cameraData[49] = pos.y;
        cameraData[50] = pos.z;
        //cameraData[51] = pos.x; ???

        m_cameraData->update(cameraData, cameraDataSize);

        int maxLightSize = 1024;
        int lCount = WORLD->getScene()->m_lights.size() > maxLightSize ? maxLightSize : WORLD->getScene()->m_lights.size();

        for(int i = 0; i < lCount; i++) {
            lightData[4 * i + 0] = WORLD->getScene()->m_lights[i]->getPosition().x;
            lightData[4 * i + 1] = WORLD->getScene()->m_lights[i]->getPosition().y;
            lightData[4 * i + 2] = WORLD->getScene()->m_lights[i]->getPosition().z;
            lightData[4 * i + 3] = 1;//WORLD->getScene()->m_lights[i]->getPosition().x;

            lightData[4 * i + 0 + maxLightSize * 4] = WORLD->getScene()->m_lights[i]->getColor().x;
            lightData[4 * i + 1 + maxLightSize * 4] = WORLD->getScene()->m_lights[i]->getColor().y;
            lightData[4 * i + 2 + maxLightSize * 4] = WORLD->getScene()->m_lights[i]->getColor().z;
            lightData[4 * i + 3 + maxLightSize * 4] = 0;//WORLD->getScene()->m_lights[i]->getPosition().x;

            lightData[4 * i + 0 + maxLightSize * 2 * 4] = WORLD->getScene()->m_lights[i]->getAttenuation().x;
            lightData[4 * i + 1 + maxLightSize * 2 * 4] = WORLD->getScene()->m_lights[i]->getAttenuation().y;
            lightData[4 * i + 2 + maxLightSize * 2 * 4] = WORLD->getScene()->m_lights[i]->getAttenuation().z;
            lightData[4 * i + 3 + maxLightSize * 2 * 4] = 1;//WORLD->getScene()->m_lights[i]->getPosition().x;

        }
        lightData[lightDataSize - 4] = lCount;
        lightData[lightDataSize - 3] = 0;
        lightData[lightDataSize - 2] = 0;
        lightData[lightDataSize - 1] = 0;

        m_lightData->update(lightData, lightDataSize);

        // ###################################################

        render();
        tick(delta);

		frames++;
		if (currentMillis > timer1 + 1000) {
			logInfo(std::string("Fps: " + std::to_string(frames)));
			timer1 = currentMillis;
			frames = 0;
		}
	}

    delete m_screenBuffer;
    delete m_cameraData;
    delete m_lightData;

    delete cameraData;
    delete lightData;

    delete WORLD;
    delete LOADER;
    delete STATIC_SHADER;
    delete INPUT;

}

