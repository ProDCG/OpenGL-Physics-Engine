#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Camera::position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// lookAt is being used to create a vector pointing at the correct position
	view = glm::lookAt(position, position + orientation, up);

	// perspective
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// exports camera matrix to vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Camera::position += Camera::speed * Camera::orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Camera::position += Camera::speed * -Camera::orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Camera::position += Camera::speed * -glm::normalize(glm::cross(Camera::orientation, Camera::up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Camera::position += Camera::speed * glm::normalize(glm::cross(Camera::orientation, Camera::up));
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		SwitchRenderingMode();
	}
}

void Camera::SwitchRenderingMode() {
	renderMode = (renderMode == GL_FILL) ? GL_LINE : GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, renderMode);
}