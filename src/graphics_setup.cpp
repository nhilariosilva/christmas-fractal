#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <stb_image.h>
#include <graphics_setup.hpp>
#include <time.h>

#include <shader.hpp>

#include <glad/glad.h>
#include <glfw3.h>

Window::Window(int width, int height, char* title){
	this->width = width;
	this->height = height;
	this->title = title;

	this->initGLFW();

	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		this->~Window();
	}

}

Window::~Window(){ }

void Window::initGLFW(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::initGLAD(){
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
 		std::cout << "Failed to initialize GLAD" << std::endl;
		this->~Window();
	}

}

void Window::processInput(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

PointImage getMidpoint(PointImage P, PointImage Q){
	PointImage PQ = PointImage( (P.x+Q.x)/2, (P.y+Q.y)/2);
	return PQ;
}

void Window::generate_points(int depth, std::vector<PointImage>* points, PointImage P, PointImage Q, PointImage R){
		if(depth <= 0){
			return;
		}
		PointImage PQ = getMidpoint(P,Q);
		PointImage QR = getMidpoint(Q,R);
		PointImage RP = getMidpoint(R,P);

		(*points).push_back(RP);
		(*points).push_back(QR);
		(*points).push_back(PQ);

		generate_points(depth-1, points, P, PQ, RP);
		generate_points(depth-1, points, Q, QR, PQ);
		generate_points(depth-1, points, R, RP, QR);
}

void Window::run(){
	glfwMakeContextCurrent(Window::window);
	glfwSetFramebufferSizeCallback(Window::window, Window::framebufferSizeCallback);

	this->initGLAD();

	// ********** Setup for Triangle **********

	std::cout << "Generating points..." << std::endl;
	std::vector<PointImage> points;

	PointImage P = PointImage( -0.9f, -0.9f );
	PointImage Q = PointImage( 0.9f, -0.9f );
	PointImage R = PointImage( 0.0f, 0.9f );

	// Generate vertices
	this->generate_points(8, &points, P, Q, R);

	// Print and pass vertices from vector to float[]
	float vertices[ points.size() * 6 ];
	unsigned int indices[ points.size() ];

	int j = 0;
	for(int i = 0; i < points.size(); i++){
		PointImage p = points[i];
		//p.print_point();
		vertices[j] = (float) p.x;
		vertices[j+1] = (float) p.y;
		vertices[j+2] = (float) p.z;
		vertices[j+3] = (float) p.color_r;
		vertices[j+4] = (float) p.color_g;
		vertices[j+5] = (float) p.color_b;

		indices[i] = i;
		j += 6;
	}
/*
	for (int i = 0; i < points.size() * 5; i++){
		std::cout << vertices[i] << ", ";
		if((i+1)%5 == 0){
			std::cout << std::endl;
		}
	}
*/
	Shader shader = Shader("resources/shader.vs", "resources/shader.fs");

	// # Buffer is basically a memory region that stores useful information during the execution of a program
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind Vertex Array Object
	glBindVertexArray(VAO);

	// Bind VBO informing its a vertex buffer object (code: GL_ARRAY_BUFFER) & Copies user information into the created buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	// Texture Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// **********

	float time;
	float speed_r = ((double) rand() / (RAND_MAX)) * 3;
	float speed_g = ((double) rand() / (RAND_MAX)) * 3;
	float speed_b = ((double) rand() / (RAND_MAX)) * 3;

	int change_interval = 6;

	while(!glfwWindowShouldClose(window)){
		this -> processInput(window);

		glClearColor(0.15f, 0.3f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		time = glfwGetTime();

		if(time > change_interval){
			speed_r = ((double) rand() / (RAND_MAX)) * 3;
		  speed_g = ((double) rand() / (RAND_MAX)) * 3;
		  speed_b = ((double) rand() / (RAND_MAX)) * 3;
			change_interval += 6;
			std::cout << "Speeds altered to:" << std::endl;
			std::cout << "Red:" << speed_r << std::endl;
			std::cout << "Green:" << speed_g << std::endl;
			std::cout << "Blue:" << speed_b << std::endl;
		}

		shader.use();
		shader.setFloat("incColor_r", sin(speed_r * time) );
		shader.setFloat("incColor_g", sin(speed_g * time) );
		shader.setFloat("incColor_b", sin(speed_b * time) );

		glBindVertexArray(VAO);
		//std::cout << "Teste" << points.size() << std::endl;
		glDrawElements(GL_TRIANGLES, points.size(), GL_UNSIGNED_INT, 0);
		//std::cout << "Teste" << std::endl;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}
