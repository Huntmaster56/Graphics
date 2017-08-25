#version 450

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec4 tex;
layout(location = 3) in vec4 norm;

layout(location = 0) uniform mat4 model;

out vec4 vCol;

void main()
{
	gl_Position = model * pos;
	vCol = pos;
}