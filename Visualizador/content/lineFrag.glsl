#version 330 core

uniform vec3 MaterialColor = vec3 (1.0, 0.0, 0.0);

out vec4 color;


void main()
{
	color = vec4(MaterialColor, 1.0);
}