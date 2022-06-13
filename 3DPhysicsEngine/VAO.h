#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <array>
#include "VBO.h"

//template <size_t size>
class VAO {
public:

	GLuint ID;
	std::vector<GLuint> indices;
	//std::array<GLuint, size> sdkffds;

	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();

	void Unbind();

	void Delete();
};

#endif