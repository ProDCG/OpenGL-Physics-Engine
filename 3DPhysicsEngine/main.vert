#version 420 core

layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;

void main() 
{
	gl_Position = camMatrix * vec4(aPos, 1.0);
}