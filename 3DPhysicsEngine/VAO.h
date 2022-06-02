#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include <vector>
#include "VBO.h"

class VAO {
public:

	GLuint ID;
	std::vector<GLuint> indices;

	VAO(std::vector<GLuint> indices);

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();

	void Unbind();

	void Delete();
};

#endif