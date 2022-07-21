#ifndef FLOODENGINE_RENDERER_H
#define FLOODENGINE_RENDERER_H

#include "Platform.h"
#include "Window.h"
#include "Scene.h"

namespace engine {

	class Renderer {
	public:
		Renderer(uint32_t width, uint32_t height);
		~Renderer();

		virtual void update() = 0;
		virtual void prepass(const glm::vec4& background) = 0;
		virtual void renderModel(Model* model) = 0;
        virtual void renderScene(Scene* scene) = 0;

		Window* getWindow();
	protected:
		uint32_t m_width, m_height;

		Window* m_window = nullptr;

	};

}

#endif // FLOODENGINE_RENDERER_H
