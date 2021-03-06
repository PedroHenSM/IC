#version 130

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

	color = vec4(1.0, 1.0, 1.0, texture( myTextureSampler, UV ).r);
}
