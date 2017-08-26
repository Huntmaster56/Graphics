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
		{ { -1, 1,0,1 },{ 0,0,0,0 },{ 0,1 } }};


	Texture tex = loadTexture("../../resources/textures/Duck.png");


	Framebuffer f = { 0, 800, 800 };
	Framebuffer screen = { 0, 800, 600 };


	//unsigned quadidx[] = { 0,1,3, 1,2,3 };
	//Shader s = makeShader(fv.c_str(), ff.c_str());
	//Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	//Geometry cube = loadGeometry("../../resources/models/cube.obj");
	//Shader sq = loadShader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");
	//Shader scube = loadShader("../../resources/shaders/cube.vert", "../../resources/shaders/cube.frag");

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");

	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");

	Shader lambert = loadShader("../resources/shaders/lambert.vert",
		"../resources/shaders/lambert.frag");

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, 0.01f, 100.f);
	glm::mat4 go_model;

	glm::vec3 dl_dir = glm::normalize(glm::vec3(1, -1, 1));
	glm::vec4 dl_col = glm::vec4(.7f, .6f, .2f, 1.f);



	while (context.step())
	{
		float time = context.getTime();
		glm::mat4 model = glm::rotate(time, glm::vec3(0, 1, 0));

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, tslot = 0;
		setUnifroms(lambert, loc, tslot, cam_view, cam_proj, go_model, ss_diffuse, dl_dir, dl_col);
		s0_draw(screen, lambert, ss_geo);
	}



	context.Term();


}