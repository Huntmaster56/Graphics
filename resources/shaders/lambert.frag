#version 450

in vec2 vUV;
in vec3 vNormal;

(layout location = 3) uniform smapler2D diffuse;
(layout location = 4) uniform vec3 lightDirection;
(layout location = 5) uniform vec4 lightColor;

out vec4 outColor;

void main()
{
	vec4 surfaceColor = texture(diffuse, vUV);

	float lambertianFactor = texture(diffuse, vUV);

	vec4 lambertianTerm = surfaceColro * lambertianFactor * lightColor;

	outColor = lambertarian;
}