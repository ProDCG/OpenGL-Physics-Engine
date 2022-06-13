#pragma once

// opengl imports
#include <glad/glad.h>

// c++ std imports
#include <vector>
#include <array>

// header imports
#include "VBO.h"

// vao class declaration
class VAO {
public:

	// unique id for array objects + indice storage
	GLuint ID;
	std::vector<GLuint> indices;

	// constructor
	VAO(std::vector<GLuint> indices);

	// VAO override-style functions
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};