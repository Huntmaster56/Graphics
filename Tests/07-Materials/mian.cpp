#include "graphics\context.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics/Loaad.h"
#include "glm\ext.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	Context context;
	context.init();

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{ 0,0,0,0 },{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{ 0,0,0,0 },{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{ 0,0,0,0 },{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{ 0,0,0,0 },{ 0,1 },{ 0,0,1,0 } } };



	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Texture floor_normal = loadTexture("../../resources/textures/normalMap.jpg");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
								"../../resources/shaders/standard.frag");

	Framebuffer screen = { 0, 800, 600 };

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 4, 5),
									 glm::vec3(0, 1, 0), 
									 glm::vec3(0, 1, 0));

	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 800.f, 0.01f, 10.f);
	
	glm::mat4 go_model;

	glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));


	while (context.step())
	{
		float time = context.getTime();

		go_model = glm::rotate(time, glm::vec3(1, 0, 0)) * glm::rotate(glm::radians(90.f), glm:: vec3(1,0,0)) * glm::scale(glm::vec3(2,2,1));


		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);



		int loc = 0, slot = 0;
		setUnifroms(standard, loc, slot,
			cam_proj, cam_view,			// Camera information
			go_model, floor_normal,		// Surface information
			light_direction);			// Light Information

		s0_draw(screen, standard, quad);

	}
	context.Term();
	return 0;
}