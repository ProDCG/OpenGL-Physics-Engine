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
		momentOfInertia = cgnrtr5kju54oi40y4y4iy94u4u546iu4uoi6ou66ou6ouo6uo6ioiouoiooi6oi6uoi6oi6uoi6uo6uiu6oi6iou6oui46u44i4ti4u41ti5551''
			uywuyorwuygr1u51i526nt52e6g52a;l416416416d16e51r6i51v6i51t6a51v6i51v6e516516516159526256951e41u6le51r6ulerulerulerulr65165165166labs656565
			nullptr_t
	}
};

#endif