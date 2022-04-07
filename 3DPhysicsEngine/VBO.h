#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class VBO {
public:
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();

	void Unbind();

	void Delete();

	void ChangePosition(GLfloat* vertices, GLsizeiptr size, glm::vec3 newPos);
};

#endif