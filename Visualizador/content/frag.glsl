#version 130

uniform vec3 MaterialColor;
uniform int DrawMode;
uniform sampler2D NormalMap;
uniform sampler2D WireMap;
uniform float tilling = 1.0f;

in vec3 vColor;
in vec3 vL;
in vec3 vH;
in vec2 UV;

out vec4 color;


void main()
{
	vec3 L = normalize(vL);
	vec3 H = normalize(vH);
	vec3 N = vec3(0, 0, 1);
	
	/*N = texture(NormalMap, -UV * tilling).xyz * 2.0 - 1.0;
	N.r *= (-0.2f / tilling);*/
	normalize(N);

	N *= (gl_FrontFacing) ? 1.0 : -1.0;

	//vec3 col = texture(WireMap, tilling * UV).xyz;
	vec3 ambient = vec3(0.2);

	vec3 c = (DrawMode==0) ? vColor : MaterialColor;
	vec3 diff = c * dot(N,L);
	vec3 specular = vec3(0.6) * pow(max(dot(N, H), 0.0), 20.0);

	color = vec4(diff + ambient , 0.1);
}