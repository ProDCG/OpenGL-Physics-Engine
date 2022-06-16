#pragma once

// opengl libraries
#include <glad/glad.h>
#include <glm/glm.hpp>

// vbo class declaration
class VBO {
public:
	// unique id for buffer objects
	GLuint ID;

	// constructor and override-style functions
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(const GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};