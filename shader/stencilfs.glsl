#version 330 core

uniform vec4 stencilColor;

void main()
{
	gl_FragColor = stencilColor;
}
