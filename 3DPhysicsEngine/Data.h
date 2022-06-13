#pragma once

// opengl required imports
#include <GLFW/glfw3.h>

// data class
extern class Data {

public:
	// delta time properties
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// delta time update
	void updateTime() {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
};