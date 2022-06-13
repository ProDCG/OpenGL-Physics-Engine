#include "Camera.h"
#include "Engine.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Camera::position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	//model = glm::translate(model, glm::vec3(0.0f));
	//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	
	//if (!obj.isStatic) {
	//	model = glm::scale(model, glm::vec3(1.0f) * obj.radius * 0.1f);
	//	model = glm::translate(model, obj.position);
	//} else {
	//	//model = glm::scale(model, glm::vec3(1.0f * obj.radius, 0.01f, 1.0f * obj.radius));
	//	model = glm::translate(model, obj.position);
	//	model = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f * obj.radius));
	//	model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//}
	//obj.updatePhysics(Camera::dt);
	//if (obj.doesRotate) {
	//	float time1 = cos((float)glfwGetTime());
	//	float time2 = sin((float)glfwGetTime());
	//	model = glm::translate(model, obj.position * glm::vec3(time1, time2, 0.0f));
	//	//model = glm::rotate(model, (float)glfwGetTime(), obj.rotate);
	//}

	/*if (obj.doesRotate) {
		model = glm::translate(model, glm::vec3(sin((float)glfwGetTime()) * obj.rotate.x , cos((float)glfwGetTime()) * obj.rotate.y, sin((float)glfwGetTime()) * obj.rotate.z) * obj.rotationalMultiplier);
		model = glm::rotate(model, (float)glfwGetTime(), obj.rotate);
	} else {
		model = glm::translate(model, obj.position);
	}*/

	// lookAt is being used to create a vector pointing at the correct position
	view = glm::lookAt(position, position + orientation, up);

	// perspective
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// exports camera matrix to vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view * model));
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform, Rigidbody obj) {};

void Camera::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		Camera::position += Camera::speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Camera::position += Camera::speed * -up;
	}
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, width / 2, height / 2);
			firstClick = false;
		}

		double mouseX, mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		if (abs(glm::angle(orientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			orientation = newOrientation;
		}
		else {
			orientation = glm::rotate(orientation, glm::radians(-0.01f), up);
		}

		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		glfwSetCursorPos(window, width / 2, height / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}