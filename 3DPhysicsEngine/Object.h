#pragma once

// opengl imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

// header imports
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

// c++ std imports
#include <vector>
#include <string>
#include <cmath>

// object class
class Object {
public:
	// vectors for physics, holding the properties of each entity
	glm::vec3 position;
	glm::vec3 scale;

	glm::vec3 linearVelocity = glm::vec3(0.0f);
	glm::vec3 angularVelocity = glm::vec3(0.0f);
	glm::vec3 netForce = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	// pointers to shader and object classes for efficiency
	VAO* objectType;
	Shader* shader;
	Texture* texture;

	// color and mass of the object
	glm::vec3 color;
	float mass;

	// object constructer overloads
	Object(float mass, VAO* objectType, Shader* shader, glm::vec3 color, glm::vec3 position, glm::vec3 scale);
	Object(float mass, VAO* objectType, Shader* shader, Texture* texture, glm::vec3 position, glm::vec3 scale);
	Object(float mass, VAO* objectType, Shader* shader, glm::vec3 color);
	Object(float mass, VAO* objectType, glm::vec3 color);
	Object(float mass, VAO* objectType);

	// physics force adding, with vectors and each individual component
	void addForce(float x, float y, float z);
	void addForce(glm::vec3 force);

	void setForce(float x, float y, float z);
	void setForce(glm::vec3 force);

	void addForceX(float magnitude);
	void addForceY(float magnitude);
	void addForceZ(float magnitude);

	// update the physics in the simulation
	void update(float deltaTime);

	// bind the shader and object type
	void bindObject();
	void bindShader();
	void bindTexture();
};