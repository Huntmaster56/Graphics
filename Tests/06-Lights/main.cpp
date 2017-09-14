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
	// did stuff

	Texture tex = loadTexture("../../resources/textures/Duck.png");


	Framebuffer f = { 0, 800, 800 };
	Framebuffer screen = { 0, 1280, 800 };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Shader standard = loadShader("../../resources/shaders/mvplite.vert",
								 "../../resources/shaders/mvplite.frag");

	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");

	Texture soil_diffuse = loadTexture("../../resources/textures/soil.jpg");

	/*Shader lambert = loadShader("../resources/shaders/lambert.vert",
		"../resources/shaders/lambert.frag");*/

	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 800.f, 0.01f, 10.f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 4, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 go_model;

	glm::vec3 lightDir = glm::normalize(glm::vec3(1, -1, 1));
	glm::vec4 lightColor = glm::vec4(.7f, .6f, .2f, 1.f);



	while (context.step())
	{
		float time = context.getTime();
		glm::mat4 model = glm::rotate(time, glm::vec3(0, 1, 0));
		glm::mat4 modquad = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
			* glm::scale(glm::vec3(5, 5, 1));

		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		int loc = 0, slot = 0;
		setUnifroms(standard, loc, slot, cam_proj, view, model, ss_diffuse, lightDir, lightColor);
		s0_draw(screen, standard, ss_geo);

		loc = 0, slot = 0;
		setUnifroms(standard, loc, slot, cam_proj, view, modquad, soil_diffuse, lightDir, lightColor);
		s0_draw(screen, standard, quad);
	}



	context.Term();


}