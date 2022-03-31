#ifndef GRAPHICSSETUP_HPP
#define GRAPHICSSETUP_HPP


#include <string>
#include <vector>

#include <point_image.hpp>

#include <glad/glad.h>
#include <glfw3.h>

class Window{
	public:
		// Attributes
		GLFWwindow* window;

		// Methods
		Window(int width, int height, char* title);
		~Window();

		void initGLFW();
		void initGLAD();
		static void processInput(GLFWwindow *window);
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
		void run();
	private:
		int width;
		int height;
		char* title;

		void generate_points(int depth, std::vector<PointImage>* points, PointImage P, PointImage Q, PointImage R);

};



#endif
