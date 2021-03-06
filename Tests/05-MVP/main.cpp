#include "graphics\context.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics/Loaad.h"
#include "glm\ext.hpp"

#include <iostream>
#include <fstream>
#include <string>

void main()
{
	Context context;
	context.init(800, 800);

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{ 0,0,0,0 },{ 0,0 } },
		{ { 1,-1,0,1 },{ 0,0,0,0 },{ 1,0 } },
		{ { 1, 1,0,1 },{ 0,0,0,0 },{ 1,1 } },
		{ { -1, 1,0,1 },{ 0,0,0,0 },{ 0,1 } }
	};


	Texture tex = loadTexture("../../resources/textures/Duck.png");


	Framebuffer f	   = { 0, 800, 800 };
	Framebuffer screen = { 0, 800, 600 };


	//unsigned quadidx[] = { 0,1,3, 1,2,3 };
	//Shader s = makeShader(fv.c_str(), ff.c_str());
	//Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	//Geometry cube = loadGeometry("../../resources/models/cube.obj");
	//Shader sq = loadShader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");
	//Shader scube = loadShader("../../resources/shaders/cube.vert", "../../resources/shaders/cube.frag");

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");

	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");

	Shader mvplite = loadShader("../../resources/shaders/mvplite.vert",
								"../../resources/shaders/mvplite.frag");

	glm::mat4 proj = glm::perspective(45.f, 800.f / 600.f, 0.01f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(0,2,-5), glm::vec3(0,1,0), glm::vec3(0,1,0));


	while (context.step())
	{
		float time = context.getTime();
		glm::mat4 model = glm::rotate(time, glm::vec3(0, 1, 0));

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, tslot = 0;
		setUnifroms(mvplite, loc, tslot, proj, view, model, ss_diffuse);
		s0_draw(screen, mvplite, ss_geo);
	}



	context.Term();


}