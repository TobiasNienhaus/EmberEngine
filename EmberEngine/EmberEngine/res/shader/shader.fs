#version 450 core
in vec4 vertexColor;

out vec4 FragColor;

uniform vec4 color;

uniform float time;

void main()
{
	FragColor = color;
}