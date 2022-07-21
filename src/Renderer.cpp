#include "Renderer.h"

engine::Renderer::Renderer(uint32_t width, uint32_t height) : m_width(width), m_height(height) { }

engine::Renderer::~Renderer() {
	if (m_window != nullptr) {
		delete m_window;
	}
}

engine::Window* engine::Renderer::getWindow() {
	return m_window;
}
