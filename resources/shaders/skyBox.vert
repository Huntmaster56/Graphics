#version 450

layout (location = 0) in vec4 position;

out vec3 vPos; 

layout (location = 0)uniform mat4 projection;
layout (location = 1)uniform mat4 view;
layout (location = 2)uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * position;
	vPos = (position).xyz;
} 