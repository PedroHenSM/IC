#version 130

attribute vec3 Position;

uniform mat4 MVP;
uniform mat4 MV;

uniform vec3 offset;
uniform vec3 uColor = vec3(1.0);
uniform float radius;

out vec3 vColor;


void main()
{
	gl_Position = MVP * vec4((Position * radius)+offset, 1.0);

	vColor = vec3(uColor);
}