#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Object {
public:
	glm::vec3 position;
	glm::vec3 velocity;
	 
	float gravity = -9.81 / 2;
	float radius;
	float mass;
	float rotationalMultiplier;
	float coeffKinetic = 0.3;

	bool doesRotate;
	bool isStatic;

	Object(glm::vec3 position, glm::vec3 velocity, float radius, float mass);

	Object(glm::vec3 position, glm::vec3 velocity, float radius);

	Object(glm::vec3 position, float radius);

	void updatePhysics(float dt);
};

#endif