#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
	// vectors of the camera
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	// input prevention
	bool firstClick = true;
	int renderFill = 1;
	GLenum renderMode = GL_FILL;

	// width and height of the window (for optical math)
	int width;
	int height;

	// speed of the camera + sensitivity
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// camera constructor
	Camera(int width, int height, glm::vec3 position);

	// update camera matrix to the vertex shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

	// camera inputs
	void Inputs(GLFWwindow* window);

	// switch rendering mode
	void SwitchRenderingMode();
};

#endif