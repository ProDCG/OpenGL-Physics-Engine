#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

class TriangularPrism {
public:
	GLfloat vertices[9] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.0f,  0.5f,  0.0f,
	};

	GLuint indices[3] = {
		0, 1, 2,
	};
};