#ifndef FLOODENGINE_APPLICATION_H
#define FLOODENGINE_APPLICATION_H

#include "Window.h"
//#include "VulkanRenderer.h"
#include "OpenGLRenderer.h"
#include "Logger.h"
#include "SceneLoader.h"
#include "StaticShader.h"
#include "WorldManager.h"
#include "Scene.h"

namespace engine {

    extern WorldManager* WORLD;

    struct ApplicationData {
        std::string m_windowTitle = "Prototype Application";
        uint32_t m_windowWidth = 1024, m_windowHeight = 720;
        uint32_t m_versionMajor = 1, m_versionMinor = 0, m_versionPatch = 0;
        bool m_windowResizable = false;
        Scene* m_scene = nullptr;
    };

	class Application {
	public:
		Application(ApplicationData& appData);
		~Application();

        static UniformBufferObject* m_cameraData;
        static UniformBufferObject* m_lightData;

	private:
		void run();
        void render();
        void tick(const float& delta);

		uint32_t m_width, m_height;

        Framebuffer* m_screenBuffer = nullptr;

		Window* m_window = nullptr;
		Renderer* m_renderer = nullptr;
	};

}

#endif //FLOODENGINE_APPLICATION_H