#include "Data.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Data::updateTime(float dt) {
	GLfloat currentFrame = glfwGetTime();
	Data::deltaTime = currentFrame - Data::lastFrame;
	Data::lastFrame = currentFrame;
}