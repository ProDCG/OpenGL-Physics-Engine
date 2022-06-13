#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "VAO.h"
#include "Shader.h"

#include <vector>
#include <string>
#include <cmath>

class Object {
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 linearVelocity = glm::vec3(0.0f);
	glm::vec3 angularVelocity = glm::vec3(0.0f);
	glm::vec3 netForce = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	VAO* objectType;
	Shader* shader;

	glm::vec3 color;
	float mass;

	Object(float mass, VAO* objectType, Shader* shader, glm::vec3 color);
	Object(float mass, VAO* objectType, glm::vec3 color);
	Object(float mass, VAO* objectType);

	void addForce(float x, float y, float z);

	void addForce(glm::vec3 force);

	void setForce(float x, float y, float z);

	void setForce(glm::vec3 force);

	void addForceX(float magnitude);

	void addForceY(float magnitude);

	void addForceZ(float magnitude);

	void update(float deltaTime);

	void bindObject();

	void bindShader();

private:
};