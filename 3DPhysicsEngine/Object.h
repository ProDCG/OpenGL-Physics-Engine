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

	const float gravity = -4.81f;
	float radius;
	float velocity = 20.0f;
	float mass;
	float rotationalMultiplier;

	bool doesRotate;
	bool isStatic;

	Object(glm::vec3 position, float radius);

	void updatePhysics(float dt);
};

#endif