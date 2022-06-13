#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
}