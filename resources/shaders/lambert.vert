#version 450

layout (location = 0) in vec4 position;
layout (location = 0) in vec2 texcoord;
layout (location = 3) in vec4 normal;

layout (location = 0) in vec4 proj;
layout (location = 1) in vec4 view;
layout (location = 2) in vec4 model;

out vec2 vUV;
out vec3 vNormal;

void main()
{
	gl_Position = proj * view * model * position;
	vUV = texcoord;
	vNormal = (model * normal).xyz;
}