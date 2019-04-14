#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 MVP;
uniform mat4 MV;

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);
}