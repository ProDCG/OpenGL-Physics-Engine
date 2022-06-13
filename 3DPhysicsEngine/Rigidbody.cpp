#include "Rigidbody.h"
#include <cmath>

Rigidbody::Rigidbody(float mass, Texture* textureType, VAO* objectType) {
	Rigidbody::mass = mass;
	Rigidbody::textureType = textureType;
	Rigidbody::objectType = objectType;
}

Rigidbody::Rigidbody(float mass, VAO* objectType) {
	Rigidbody::mass = mass;
	Rigidbody::objectType = objectType;
}

void Rigidbody::addForce(float x, float y, float z) {
	Rigidbody::netForce += glm::vec3(x, y, z);
}

void Rigidbody::addForce(glm::vec3 force) {
	Rigidbody::netForce += force;
}

void Rigidbody::setForce(float x, float y, float z) {
	Rigidbody::netForce = glm::vec3(x, y, z);
}

void Rigidbody::setForce(glm::vec3 force) {
	Rigidbody::netForce = force;
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
	/*Rigidbody::acceleration = Rigidbody::netForce / Rigidbody::mass;
	Rigidbody::linearVelocity = Rigidbody::linearVelocity + acceleration * deltaTime;
	Rigidbody::position = Rigidbody::position + Rigidbody::linearVelocity * deltaTime + 0.5f * Rigidbody::acceleration * exp2(deltaTime);*/

	Rigidbody::acceleration.x = Rigidbody::netForce.x / Rigidbody::mass;
	Rigidbody::linearVelocity.x = Rigidbody::linearVelocity.x + Rigidbody::acceleration.x * deltaTime;
	Rigidbody::position.x = Rigidbody::position.x + (Rigidbody::linearVelocity.x * deltaTime) + (0.5f * Rigidbody::acceleration.x * pow(deltaTime, 2));

	Rigidbody::acceleration.y = Rigidbody::netForce.y / Rigidbody::mass;
	Rigidbody::linearVelocity.y = Rigidbody::linearVelocity.y + Rigidbody::acceleration.y * deltaTime;
	Rigidbody::position.y = Rigidbody::position.y + (Rigidbody::linearVelocity.y * deltaTime) + (0.5f * Rigidbody::acceleration.y * pow(deltaTime, 2));

	Rigidbody::acceleration.z = Rigidbody::netForce.z / Rigidbody::mass;
	Rigidbody::linearVelocity.z = Rigidbody::linearVelocity.z + Rigidbody::acceleration.z * deltaTime;
	Rigidbody::position.z = Rigidbody::position.z + (Rigidbody::linearVelocity.z * deltaTime) + (0.5f * Rigidbody::acceleration.z * pow(deltaTime, 2));
}