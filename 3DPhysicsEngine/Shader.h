#pragma once

// opengl imports
#include <glad/glad.h>
#include <glm/glm.hpp>

// c++ std imports
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// file contents grabber
std::string get_file_contents(const char* filename);

// shader 
class Shader {
public:
	// unique id for shader objects
	GLuint ID;

	// constructor
	Shader(const char* vertexFile, const char* fragmentFile);

	// memory cleanup and binding
	void Activate();
	void Delete();

	// functions for interaction with .frag and .vert files
	void setVec3(const std::string& name, const glm::vec3& value);
	void setMat4(const std::string& name, const glm::mat4& value);
private:
	// error management
	void compileErrors(unsigned int shader, const char* type);
};