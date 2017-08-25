#version 450

out vec4 outColor;

in vec4 vCol;

void main()
{
	outColor = dot(vNormal, -normalize(1,1,1,0)) * outColor;
}