#ifndef FLOODENGINE_WINDOW_H
#define FLOODENGINE_WINDOW_H

#include "Platform.h"

namespace engine {

	class Window
	{
	public:
		//Window(uint32_t width, uint32_t height, const char* title, VkInstance* instance);
		Window(uint32_t width, uint32_t height, const char* title);
		~Window();

		void update();
		void setTitle(const char* title);
		bool shouldClose();

		GLFWwindow* getWindow();
		//VkSurfaceKHR* getSurface();

		uint32_t getWidth();
		uint32_t getHeight();

		void setSize(uint32_t width, uint32_t height);

	private:
		bool isOpenGL = true;

		GLFWwindow* m_window = nullptr;

		//VkInstance* m_instance = nullptr;
		//VkSurfaceKHR m_surface;
		uint32_t m_width, m_height;

	};

}

#endif // FLOODENGINE_WINDOW_H