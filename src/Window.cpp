#include "Window.h"

/*engine::Window::Window(uint32_t width, uint32_t height, const char* title, VkInstance* instance) : m_width(width), m_height(height), m_instance(instance) {

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (glfwCreateWindowSurface(*instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
		logErrorAndCrash("Could not create Window Surface!!!");
	}

}*/

engine::Window::Window(uint32_t width, uint32_t height, const char* title) : m_width(width), m_height(height)/*, m_instance(nullptr)*/ {

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(0);

}

engine::Window::~Window() {
	if (!isOpenGL) {
		//vkDestroySurfaceKHR(*m_instance, m_surface, nullptr);
	}

	glfwDestroyWindow(m_window);
}

void engine::Window::update() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void engine::Window::setTitle(const char* title) {
	glfwSetWindowTitle(m_window, title);
}

bool engine::Window::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

GLFWwindow* engine::Window::getWindow() {
	return m_window;
}

/**VkSurfaceKHR* engine::Window::getSurface() {
	return &m_surface;
}*/

uint32_t engine::Window::getWidth() {
	return m_width;
}

uint32_t engine::Window::getHeight() {
	return m_height;
}

void engine::Window::setSize(uint32_t width, uint32_t height) {
	logError("Window resize method needs to be finished!!");
}

