// haeder imports
#include "VAO.h"

// constructor
VAO::VAO(std::vector<GLuint> indices) {
	VAO::indices = indices;
	glGenVertexArrays(1, &ID);
}

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// memory cleanup functions + vao initialization setup
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}