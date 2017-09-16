#version 450
layout (location = 3) uniform samplerCube skybox;
out vec4 outColor;

in vec3 vPos;


void main()
{
	outColor = texture(skybox, vPos);
}
