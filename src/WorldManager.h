#ifndef FLOODENGINE_WORLDMANAGER_H
#define FLOODENGINE_WORLDMANAGER_H

#include "Platform.h"
#include "Framebuffer.h"

namespace engine {

    class Scene;
    class Camera;

	class WorldManager {
	public:
		WorldManager(Scene* mainScene, Camera* camera);
		~WorldManager();

		void tick(const float& delta);

        unsigned long getNewId();

        void changeCamera(Camera* camera);

		Camera* getCamera();
        Scene* getScene();
        glm::vec4 getSkyColor();
        void setSkyColor(glm::vec4 skyColor);

        void addFramebuffer(Framebuffer* framebuffer);
        std::vector<Framebuffer*>& getFramebuffers();

	private:
        std::vector<Framebuffer*> m_framebuffers;
        unsigned long m_lastIDAssigned = 0;

	    Camera* m_mainCamera = nullptr;
        Scene* m_scene = nullptr;

        glm::vec4 m_skyColor = glm::vec4(0.0f, 0.56f, 0.96f, 1.0f);
	};

}

#endif // FLOODENGINE_WORLDMANAGER_H