#ifndef FLOODENGINE_CAMERA_H
#define FLOODENGINE_CAMERA_H

#include "Entity.h"

namespace engine {
    /**
     * a good fov is 70.0f :)
     *

     */
	class Camera : public Entity {
	public:
        Camera();
        //a good fov is 70.0f :)
	    Camera(uint32_t windowWidth, uint32_t windowHeight, float near, float far, float fov);
		~Camera();

        //a good fov is 70.0f :)
        void updateProjection(uint32_t windowWidth, uint32_t windowHeight, float nearPlane, float farPlane, float fov);
        void updateProjection(glm::mat4x4 projectionMatrix, Camera* cam);

		glm::mat4x4 getProjectionMatrix();

        void init() override;

        uint32_t getWindowWidth();
        uint32_t getWindowHeight();
        float getNearPlane();
        float getFarPlane();
        float getFOV();


	protected:
        glm::mat4x4 recreateProjectionMatrix(uint32_t windowWidth, uint32_t windowHeight, float nearPlane, float farPlane, float fov);

		void tick(const float& delta);

        void destroy() override;

		uint32_t m_windowWidth = 0, m_windowHeight = 0;
		float m_near = 0, m_far = 0, m_fov = 0;
		glm::mat4x4 m_projectionMatrix;

	};
}

#endif // FLOODENGINE_CAMERA_H