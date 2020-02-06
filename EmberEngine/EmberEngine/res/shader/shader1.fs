#version 450 core
in vec4 vertexColor;

out vec4 FragColor;

uniform float time;

void main()
{
	FragColor = vec4((sin(time * 5.0) + 1.0) / 2.0) * vertexColor;
}