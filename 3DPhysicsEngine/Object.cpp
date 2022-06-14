#include "Object.h"

// object constructor overloads
Object::Object(float mass, VAO* objectType, Shader* shader, glm::vec3 color, glm::vec3 position, glm::vec3 scale) {
	Object::mass = mass;
	Object::objectType = objectType;
	Object::shader = shader;
	Object::color = color;
	Object::position = position;
	Object::scale = scale;
	Object::rotation = glm::vec3(0.0f);
}

Object::Object(float mass, VAO* objectType, Shader* shader, glm::vec3 color) {
	Object::mass = mass;
	Object::objectType = objectType;
	Object::color = color;
	Object::shader = shader;
	Object::position = glm::vec3(0.0f, 0.0f, 0.0f);
	Object::scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Object::rotation = glm::vec3(0.0f);
}

Object::Object(float mass, VAO* objectType, glm::vec3 color) {
	Object::mass = mass;
	Object::objectType = objectType;
	Object::color = color;
	Object::shader = NULL;
	Object::position = glm::vec3(0.0f, 0.0f, 0.0f);
	Object::scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Object::rotation = glm::vec3(0.0f);
}

Object::Object(float mass, VAO* objectType) {
	Object::mass = mass;
	Object::objectType = objectType;
	Object::color = glm::vec3(1.0f);
	Object::shader = NULL;
	Object::position = glm::vec3(0.0f, 0.0f, 0.0f);
	Object::scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Object::rotation = glm::vec3(0.0f);
}

// physics force adding, with vectors and each individual components
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

// update the physics in the simulation
void Object::update(float deltaTime) {
	// x component
	Object::acceleration.x = Object::netForce.x / Object::mass;
	Object::linearVelocity.x = Object::linearVelocity.x + Object::acceleration.x * deltaTime;
	Object::position.x = Object::position.x + (Object::linearVelocity.x * deltaTime) + (0.5f * Object::acceleration.x * pow(deltaTime, 2));

	// y component
	Object::acceleration.y = Object::netForce.y / Object::mass;
	Object::linearVelocity.y = Object::linearVelocity.y + Object::acceleration.y * deltaTime;
	Object::position.y = Object::position.y + (Object::linearVelocity.y * deltaTime) + (0.5f * Object::acceleration.y * pow(deltaTime, 2));

	// z component
	Object::acceleration.z = Object::netForce.z / Object::mass;
	Object::linearVelocity.z = Object::linearVelocity.z + Object::acceleration.z * deltaTime;
	Object::position.z = Object::position.z + (Object::linearVelocity.z * deltaTime) + (0.5f * Object::acceleration.z * pow(deltaTime, 2));
}

// bind the objects type
void Object::bindObject() {
	Object::objectType->Bind();
}

// bind the shader
void Object::bindShader() {
	Object::shader->Activate();
	Object::shader->setVec3("objectColor", Object::color);
}