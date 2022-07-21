#ifndef FLOODENGINE_OPENGL_RENDERER_H
#define FLOODENGINE_OPENGL_RENDERER_H

#include "Logger.h"
#include "Renderer.h"
#include "Model.h"

namespace engine {

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer(uint32_t width, uint32_t height);
		~OpenGLRenderer();

		void renderModel(Model* model) override;
        void renderScene(Scene* scene) override;

		void update() override;

		void prepass(const glm::vec4& bg) override;

	private:


	};



}

#endif // FLOODENGINE_OPENGL_RENDERER_H