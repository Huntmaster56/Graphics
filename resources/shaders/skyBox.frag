#version 450
out vec4 FragColor;

in vec3 TexCoords;

layout (location = 2) uniform smaplerCube skybox;

void main()
{
	FragColor = texture(skybox, TexCoords);
}