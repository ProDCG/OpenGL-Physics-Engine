#version 420 core

// RGBA
out vec4 FragColor;

// Inputs color from Vertex Shader
in vec3 color;
// Inputs texture coords from Vertex Shader
in vec2 texCoord;

// Texture unit
uniform sampler2D tex0;

void main() 
{
	FragColor = texture(tex0, texCoord);
}