#pragma once

// opengl required imports
#include <GLFW/glfw3.h>

// cube class
class Cube {
public:
	// cube vertices
	GLfloat vertices[144] = {
		// front face
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // bottom left
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // top left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // bottom right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // top right

		// right face
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f, 0.0f, // bottom left
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f, 0.0f, // top left
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f, 0.0f, // bottom right
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f, 0.0f, // top right

		// back face
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // bottom left
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // top left
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // bottom right
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // top right

		// left face
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f, 0.0f, // top left
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f, 0.0f, // bottom right
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f, 0.0f, // top right

		// bottom face
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, // bottom left
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, // top left
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, // bottom right
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, // top right

		// top face
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f, // bottom left
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f, // top left
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f, // bottom right
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f, // top right
	};

	// cube indices
	GLuint indices[36] = {
		// front face
		0, 1, 3,
		0, 2, 3,

		// right face
		4, 5, 7,
		4, 6, 7,

		// back face
		8, 9, 11,
		8, 10, 11,

		// left face
		12, 13, 15,
		12, 14, 15,

		// bottom face
		16, 17, 19,
		16, 18, 19,

		// top face
		20, 21, 23,
		20, 22, 23,
	};
};