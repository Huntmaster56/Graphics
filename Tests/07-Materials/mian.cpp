#include "graphics\context.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics/Loaad.h"
#include "glm\ext.hpp"
#include "graphics\GameObject.h"
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

	//Texture floor_normal = loadTexture("../../resources/textures/normalMap.jpg");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
		                         "../../resources/shaders/standard.frag");


	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
							   	   "../../resources/shaders/quad.frag");

	Framebuffer screen = { 0, 1280, 720 };
	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);

	SpecGloss ss;

	ss.geo = loadGeometry("../../resources/models/soulspear.obj");
	

	ss.normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	ss.diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	ss.specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	ss.gloss = 4.0f;

	SpecGloss ss2 = ss;
	ss2.model = glm::rotate(90.f, glm::vec3(0, 1, 0));


	Camera cam;

	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
									 glm::vec3(0, 2, 0), 
									 glm::vec3(0, 1, 0));

	cam.proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
	
	glm::vec3 l_dir = glm::normalize(glm::vec3(1, -1, -1));
	glm::vec4 l_color = glm::vec4(.7, .5, .9, 1);
	float l_intensity = 1.0;
	glm::vec4 l_ambient = glm::vec4(.2, .2, .01, 1);
	int l_type = 0;


	//glm::mat4 go_model;
	//glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));


	while (context.step())
	{
		float time = context.getTime();
		ss.model = glm::rotate(time, glm::vec3(0, 1, 0));
		//go_model = glm::rotate(time, glm::vec3(1, 0, 0))
		//	* glm::rotate(glm::radians(90.f), glm:: vec3(1,0,0))
		//	* glm::scale(glm::vec3(2,2,1));


		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUnifroms(standard, loc, slot,
			cam.proj, cam.view,			// Camera information
			ss.model, ss.diffuse, ss.specular, ss.normal, ss.gloss, l_dir, l_color, l_intensity, l_ambient, l_type);			// Light Information
		 
		s0_draw(fBuffer, standard, ss.geo);


		clearFramebuffer(screen);

		loc = 0, slot = 0;
		setUnifroms(fsq_shader, loc, slot, fBuffer.targets[0]);
		s0_draw(screen, fsq_shader, quad);
	}
	context.Term();
	return 0;
}