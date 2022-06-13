#ifndef RIGIDBODY_CLASS_H
#define RIGIDBODY_CLASS_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Texture.h"
#include "VAO.h"

#include <cstring>
#include <string>

class Rigidbody {
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 linearVelocity = glm::vec3(0.0f);
	glm::vec3 angularVelocity = glm::vec3(0.0f);
	glm::vec3 netForce = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	float mass;
	
	/*std::vector<char> objType;
	std::vector<char> textureType;*/
	Texture *textureType;
	VAO *objectType;

	Rigidbody(float mass, Texture* textureType, VAO* objType);

	Rigidbody(float mass, VAO* objType);

	void addForce(float x, float y, float z);

	void addForce(glm::vec3 force);

	void setForce(float x, float y, float z);

	void setForce(glm::vec3 force);

	void addForceX(float magnitude);

	void addForceY(float magnitude);

	void addForceZ(float magnitude);

	void update(float deltaTime);
};

#endif