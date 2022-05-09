#include "Object.h"

Object::Object(glm::vec3 position, float radius)
{
	//Object::position = glm::vec3(position.x, position.y - (radius / 2), position.z);
	Object::position = position;
	Object::radius = radius;
	Object::mass = 0.0f;
	Object::velocity = 0.0f;
	Object::rotate = glm::vec3(1.0f);
	Object::doesRotate = false;
}

Object::Object(glm::vec3 position, float radius, glm::vec3 rotate, float rotationalMultiplier) {
	//Object::position = glm::vec3(position.x, position.y - (radius / 2), position.z);
	Object::position = position;
	Object::radius = radius;
	Object::mass = 0.0f;
	Object::rotationalMultiplier = rotationalMultiplier;
	Object::velocity = 0.0f;
	Object::rotate = rotate;
	Object::doesRotate = true;
}
