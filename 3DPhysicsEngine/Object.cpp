#include "Object.h"
#include "Data.h"
#include <iostream>

Object::Object(glm::vec3 position, glm::vec3 velocity, float radius)
{
	//Object::position = glm::vec3(position.x, position.y - (radius / 2), position.z);
	Object::position = position;
	Object::radius = radius;
	Object::mass = 1.0f;
	Object::rotationalMultiplier = 0.0f;
	Object::velocity = velocity;
	Object::doesRotate = false;
	Object::isStatic = false;
}

Object::Object(glm::vec3 position, float radius) {
	Object::position = position;
	Object::radius = radius;
	Object::mass = 0.0f;
	Object::rotationalMultiplier = 0.0f;
	Object::velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	Object::doesRotate = false;
	Object::isStatic = true;
}

void Object::updatePhysics(float dt) {
	// x component
	Object::velocity.x = Object::velocity.x + Object::coeffKinetic * dt;
	Object::position.x = Object::position.x + Object::velocity.x * dt;

	// y component
	Object::velocity.y = Object::velocity.y + Object::gravity * dt;
	Object::position.y = Object::position.y + Object::velocity.y * dt;

	if (Object::position.y < -5) {
		Object::velocity.y = abs(Object::velocity.y) * 0.5f;
	}

	// z component
	Object::velocity.z = Object::velocity.z + Object::coeffKinetic * dt;
	Object::position.z = Object::position.z + Object::velocity.z * dt;
}