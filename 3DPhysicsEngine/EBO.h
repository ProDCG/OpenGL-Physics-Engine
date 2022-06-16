#pragma once

// opengl required import
#include <glad/glad.h>

// EBO class
class EBO {
public:
	// id reference
	GLuint ID;

	// constructor
	EBO(GLuint* indices, GLsizeiptr size);
	EBO(const GLuint* indices, GLsizeiptr size);

	// bindings and memory management
	void Bind();
	void Unbind();
	void Delete();
};