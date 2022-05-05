#include "Object.h"

Object::Object(glm::vec3 position, float radius)
{
	Object::position = position;
	Object::radius = radius;
	Object::rotate = glm::vec3(1.0f);
	Object::doesRotate = false;
}

Object::Object(glm::vec3 position, float radius, glm::vec3 rotate) {
	Object::position = position;
	Object::radius = radius;
	Object::rotate = rotate;
	Object::doesRotate = true;
}
