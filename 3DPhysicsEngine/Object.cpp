#include "Object.h"

Object::Object(float mass, VAO* objectType, glm::vec3 color) {
	Object::mass = mass;
	Object::objectType = objectType;
	Object::color = color;
}

void Object::addForce(float x, float y, float z) {
	Object::netForce += glm::vec3(x, y, z);
}

void Object::addForce(glm::vec3 force) {
	Object::netForce += force;
}

void Object::setForce(float x, float y, float z) {
	Object::netForce = glm::vec3(x, y, z);
}

void Object::setForce(glm::vec3 force) {
	Object::netForce = force;
}

void Object::addForceX(float magnitude) {
	Object::netForce += glm::vec3(magnitude, 0.0f, 0.0f);
}

void Object::addForceY(float magnitude) {
	Object::netForce += glm::vec3(0.0f, magnitude, 0.0f);
}

void Object::addForceZ(float magnitude) {
	Object::netForce += glm::vec3(0.0f, 0.0f, magnitude);
}

void Object::update(float deltaTime) {
	/*Object::acceleration = Object::netForce / Object::mass;
	Object::linearVelocity = Object::linearVelocity + acceleration * deltaTime;
	Object::position = Object::position + Object::linearVelocity * deltaTime + 0.5f * Object::acceleration * exp2(deltaTime);*/

	Object::acceleration.x = Object::netForce.x / Object::mass;
	Object::linearVelocity.x = Object::linearVelocity.x + Object::acceleration.x * deltaTime;
	Object::position.x = Object::position.x + (Object::linearVelocity.x * deltaTime) + (0.5f * Object::acceleration.x * pow(deltaTime, 2));

	Object::acceleration.y = Object::netForce.y / Object::mass;
	Object::linearVelocity.y = Object::linearVelocity.y + Object::acceleration.y * deltaTime;
	Object::position.y = Object::position.y + (Object::linearVelocity.y * deltaTime) + (0.5f * Object::acceleration.y * pow(deltaTime, 2));

	Object::acceleration.z = Object::netForce.z / Object::mass;
	Object::linearVelocity.z = Object::linearVelocity.z + Object::acceleration.z * deltaTime;
	Object::position.z = Object::position.z + (Object::linearVelocity.z * deltaTime) + (0.5f * Object::acceleration.z * pow(deltaTime, 2));
}