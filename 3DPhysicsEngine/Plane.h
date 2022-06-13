#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

class Plane {
public:
	float vertices[12]{
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, 0.5f,
	};

	unsigned int indices[6]{
		0, 1, 2,
		1, 2, 3
	};
};