#version 450

out vec4 outColor;

//in vec4 vCol;
in vec4 vNormal;

void main()
{
	outColor = dot(vNormal, -normalize(vec4(1,0,1,0))) * vec4(1,1,0,1);

	//outColor = vec4(1,1,0,1);
}