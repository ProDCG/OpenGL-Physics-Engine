#include "Object.h"
#include "Data.h"

Object::Object(glm::vec3 position, float radius)
{
	//Object::position = glm::vec3(position.x, position.y - (radius / 2), position.z);
	Object::position = position;
	Object::radius = radius;
	Object::mass = 1.0f;
	Object::rotationalMultiplier = 0.0f;
	Object::velocity = 0.0f;
	Object::doesRotate = false;
	Object::isStatic = false;
}

void Object::updatePhysics(float dt) {
	Object::velocity = Object::velocity + Object::gravity * dt;
	Object::position.y = Object::position.y + Object::velocity * dt;
}