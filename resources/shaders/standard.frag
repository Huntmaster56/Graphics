#version 450


out vec4 outColor;

in vec2 vUV;
in vec3 vPos;
in mat4 vTBN;

layout(location = 1)uniform mat4 view;

layout(location = 3)uniform sampler2D diffuseMap;
layout(location = 4)uniform sampler2D specularMap;
layout(location = 5)uniform sampler2D normalMap;
layout(location = 6)uniform float gloss;

layout(location = 7) uniform vec3 l_data;
layout(location = 8) uniform vec4 l_color;
layout(location = 9) uniform float l_intensity;
layout(location = 10)uniform vec4 l_ambient;
layout(location = 11)uniform int light_type;



layout(location = 0) out vec4 outFinal;
layout(location = 1) out vec4 outDiffuse;
layout(location = 2) out vec4 outSpecular;
layout(location = 3) out vec4 outNormal;

float calc_lambert(in vec3 N, in vec3 L);
float calc_phong(in vec3 N, in vec3 L, in vec3 V, in float specPower);

void main()
{
	vec3 normal = (vTBN*(2*texture(normalMap, vUV)-1)).xyz;
	vec4 diffuse = texture(diffuseMap, vUV);
	vec4 specular = texture(specularMap, vUV);
	
	if(vPos.x < 0) normal = vTBN[2].xyz;

	vec3 lDir = l_data;
	if(light_type == 1)
		lDir = normalize(vPos - l_data);


	float lamb = calc_lambert(normal, lDir);
	float ambi = 1;

	
	float spec = calc_phong(normal, lDir, normalize(view[3].xyz - vPos), gloss);

	vec4 outAmbient = diffuse * ambi * l_ambient;
	vec4 outDiffuse = diffuse * lamb * l_color * l_intensity;
	vec4 outSpecular = specular * spec * l_color * l_intensity;

	outNormal = vec4(normal, 0);
	
	outFinal = outAmbient + outDiffuse + outSpecular;

}



float calc_lambert(in vec3 N, in vec3 L)
{
	return max(0,dot(N,-L));
}

float calc_phong(in vec3 N, in vec3 L, in vec3 V, in float specPower)
{
	if(dot(N,-L) <= 0) return 0;
	vec3 R = reflect(-L,N);
	return pow(max(0, dot(V, -R)), specPower);
}







   


























