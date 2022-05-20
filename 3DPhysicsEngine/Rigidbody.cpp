#include "Rigidbody.h"

Rigidbody::Rigidbody(float mass)
{
	Rigidbody::mass = mass;
}

void Rigidbody::addForce(float x, float y, float z) {
	Rigidbody::netForce += glm::vec3(x, y, z);
}

void Rigidbody::addForceX(float magnitude) {
	Rigidbody::netForce += glm::vec3(magnitude, 0.0f, 0.0f);
}

void Rigidbody::addForceY(float magnitude) {
	Rigidbody::netForce += glm::vec3(0.0f, magnitude, 0.0f);
}

void Rigidbody::addForceZ(float magnitude) {
	Rigidbody::netForce += glm::vec3(0.0f, 0.0f, magnitude);
}

void Rigidbody::update(float deltaTime) {
	Rigidbody::acceleration = Rigidbody::netForce / Rigidbody::mass;
	Rigidbody::linearVelocity = Rigidbody::linearVelocity + acceleration * deltaTime;
	Rigidbody::position = Rigidbody::position + Rigidbody::linearVelocity * deltaTime + 0.5f * Rigidbody::acceleration * exp2(deltaTime);

	Rigidbody::acceleration.x = Rigidbody::netForce.x / Rigidbody::mass;
	Rigidbody::linearVelocity.x = Rigidbody::linearVelocity.x + Rigidbody::acceleration.x * deltaTime;
	Rigidbody::position.x = Rigidbody::position.x + (Rigidbody::linearVelocity.x * deltaTime) + (0.5f * Rigidbody::acceleration.x * exp2(deltaTime));

	
}