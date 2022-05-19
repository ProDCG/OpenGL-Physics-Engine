#ifndef RIGIDBODY_CLASS_H
#define RIGIDBODY_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Rigidbody {
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 angularVelocity;
	
	float mass;
	float momentOfInertia;

	void calculateInertia() {
		momentOfInertia = 
	}
};

#endif