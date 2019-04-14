#version 130

attribute vec3 Position;
attribute vec3 Normal;
attribute vec3 Color;
attribute vec3 TexCoord;

uniform mat4 MVP;
uniform mat4 MV;

out vec3 vColor;
out vec3 vL;
out vec3 vH;
out vec2 UV;

vec3 lightDirection = vec3(1.0, 0.0, 0.0);
vec3 lightPosition = vec3(0.0, 0.0, 0);

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);
	vec3 vPos = (MV * vec4(Position, 1.0)).xyz;
	//lightPosition = (MV * vec4(lightPosition, 1.0)).xyz;
	
	mat3 MV3 = mat3(MV);
	
	vec3 V = normalize(-vPos);
	vec3 L = normalize(lightPosition - vPos);
	
	vec3 vN = normalize(MV3 * Normal);
	vL = normalize(L);
	vH = normalize(V + L);

	vec3 up = normalize(MV3 * vec3(0, 1, 0));

	vec3 tg = cross(up, vN);
	vec3 bt = -cross(vN, tg);

	mat3 TBN = mat3(tg, bt, vN);

	vL = TBN * vL;
	vH = TBN * vH;

	vColor = Color;
	UV = TexCoord.xy;
}