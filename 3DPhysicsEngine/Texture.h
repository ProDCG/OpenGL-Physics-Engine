#pragma once

// opengl imports
#include <glad/glad.h>
#include <stb/stb_image.h>

// header imports
#include "Shader.h"

// texture class
class Texture {
public:
	// unique id for texture objects
	GLuint ID;

	// type of texture (repeat, mirror, etc)
	GLenum type;

	// constructor
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// texture override-style functions
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};