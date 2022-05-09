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
	glm::vec3 rotate;

	const float gravity = 9.81f;
	float radius;
	float velocity;
	float mass;
	float rotationalMultiplier;

	bool doesRotate;

	Object(glm::vec3 position, float radius);

	Object(glm::vec3 position, float radius, glm::vec3 rotate, float rotationalMultiplier);
};

#endif