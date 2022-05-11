#include "Data.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Data::updateTime() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}