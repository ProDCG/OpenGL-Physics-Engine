// header imports
#include "Texture.h"

// constructor
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	// set the type of texture being drawn
	type = texType;
	glGenTextures(1, &ID);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set the resolution of the texture, standard image flip due to default value
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);

	// image import
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// set properties of each texture
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	// memory cleanup and binding
	stbi_image_free(bytes);

	// generate and bind texture
	
	


	/*glActiveTexture(slot);*/
	

	// set texture type
	

	//glTexParameteri(texType, GL_TEXTURE_WRAP_R, GL_REPEAT);
	

	glBindTexture(texType, 0);
}

// set the type of texture unit
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

// memory cleanup and bind functons
void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}