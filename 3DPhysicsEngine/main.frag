#version 420 core

// RGBA
out vec4 FragColor;

// Inputs color from Vertex Shader
uniform vec3 color;

void main() 
{
	FragColor = vec4(color, 1.0);
}