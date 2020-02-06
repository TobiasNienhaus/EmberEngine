#version 450 core
in vec2 Texcoord;

out vec4 FragColor;

uniform float time;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	FragColor = mix(texture(tex, Texcoord), texture(tex2, Texcoord), 0.2);
}