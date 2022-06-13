#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 camMatrix;

void main()
{
	FragPos = vec3(vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(mat4(1.0)))) * aNormal;  

	gl_Position = camMatrix * vec4(aPos, 1.0);
}