#include "graphics\GameObject.h"
#include "graphics\Loaad.h"
#include "graphics\Vertex.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"

Vertex vquad[] =
{
	{ { -1,-1, 0, 1 },{},{ 0,0 },{ 0,0,1,0 } },
	{ { 1,-1, 0, 1 },{},{ 1,0 },{ 0,0,1,0 } },
	{ { 1, 1, 0, 1 },{},{ 1,1 },{ 0,0,1,0 } },
	{ { -1, 1, 0, 1 },{},{ 0,1 },{ 0,0,1,0 } }
};

	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_modle = glm::translate(glm::vec3(2, 1, -1));

void Shaders()
{

}





 