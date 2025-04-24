#pragma once

///ModernOpenGl Include
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "pch.h"

///ImGui include
#include "ImGui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

///Standar include
#include <iostream>

///Project Include
#include "LowRenderer/camera.h"

namespace Rendering
{
	class Application
	{
	public:
		Application(void);

		Application(int width, int height);

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		
		float getDeltaTime();

		void updateDeltaTime();

		void processInput(GLFWwindow* window);

		~Application(void) = default;

		GLFWwindow* screen;
		int width;
		int height;
		Visual::Camera* MainCamera;
	
	private:
		static Application* instance;
		float deltaTime = 0;
		float lastFrame = 0;
	};
}