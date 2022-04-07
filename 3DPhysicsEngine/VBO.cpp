#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}

void VBO::ChangePosition(GLfloat* vertices, GLsizeiptr size, glm::vec3 newPos) {
	for (int i = 0; i < ((sizeof(vertices) / sizeof(vertices[0])) / 8); i++) {
		vertices[0 + (i * 8)] += newPos.x;
		vertices[1 + (i * 8)] += newPos.y;
		vertices[2 + (i * 8)] += newPos.z;
	}
	glBufferData(GL_ARRAY_BUFFER, size, vertices , GL_STATIC_DRAW);
}