#version 450 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform float time;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vec4 col = vec4(1.0, 0.0, 0.0, 1.0);
	vertexColor = vec4(gl_Position.xyz, 1.0);
}