// header import
#include "Shader.h"

// file contents grabber, utilizing c++ std libraries
std::string get_file_contents(const char* filename) {
	
	// throws error if file read errors occur
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw (errno);
}

// constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile) {

	Shader::vertexName += vertexFile;
	Shader::fragmentName += fragmentFile;

	// gets the file contents of .frag and .vert files, converts to a .c string
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// creates the vertex shader and the shader source, then compiles
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// creates the fragment shader and the shader source, then compiles
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// creates the parent shader and attaches the vertex and fragment shader
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// check for errors
	compileErrors(ID, "PROGRAM");

	// delete shaders for memory purposes
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// binders and unbinders for memory management
void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

// check for errors
void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;

	// prints based on success/failure of compilation of the program
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

// sets a uniform value in the .vert or .frag variables
void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}