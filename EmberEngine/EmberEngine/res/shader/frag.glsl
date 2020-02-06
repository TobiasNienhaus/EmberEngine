	#version 150 core
	in vec3 Color;
	in vec2 Texcoord;
	out vec4 outColor;
	uniform sampler2D tex;
	uniform sampler2D tex2;
	uniform float time;
	void main()
	{
		float texX = Texcoord.x;
		float texY = Texcoord.y;
		vec4 col1 = texture(tex, vec2(texX, texY));
		vec4 col2 = texture(tex2, vec2(texX, texY));
		outColor = mix(col1, col2, 1) * vec4(Color, 1.0f);
	}