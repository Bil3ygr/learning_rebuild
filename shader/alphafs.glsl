#version 330 core

in vec3 outColor;
in vec2 outTexcoord;

uniform sampler2D texture1;
uniform float alpha;

void main()
{
	vec4 texColor = texture(texture1, outTexcoord);
	if (texColor.a < alpha)
		discard;
	gl_FragColor = texColor;
}
