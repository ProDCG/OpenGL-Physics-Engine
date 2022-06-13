#include <GLFW/glfw3.h>

#include "Data.h"

void Data::updateTime() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}