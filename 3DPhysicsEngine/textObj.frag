#version 420 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D bTexture;

void main()
{
	FragColor = texture(bTexture, TexCoord);
}