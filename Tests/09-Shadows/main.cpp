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

	// Scene

	// Floor
	Vertex vquad[] =
	{
		{ { -1,-1, 0, 1 }, {}, { 0,0 }, { 0,0,1,0 } },
		{ {  1,-1, 0, 1 }, {}, { 1,0 }, { 0,0,1,0 } },
		{ {  1, 1, 0, 1 }, {}, { 1,1 }, { 0,0,1,0 } },
		{ { -1, 1, 0, 1 }, {}, { 0,1 }, { 0,0,1,0 } } 
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));

	// Soulspear
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;

	// Cube
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_modle = glm::translate(glm::vec3(2, 1, -1));
	
	// Camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);

	// Light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::vec3 light_dir1 = glm::normalize(glm::vec3(-.8, -1, -1));
	glm::mat4 light_proj1 = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view1 = glm::lookAt(-light_dir1, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// Soulspear
	Shader shdr_shadow = loadShader("../../resources/shaders/shadow.vert",
		"../../resources/shaders/shadow.frag");
	Shader shdr_direct = loadShader("../../resources/shaders/direct.vert",
		"../../resources/shaders/direct.frag");


	
	// Buffers
	Framebuffer fb_shadow = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer fb_shadow1 = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer screen = { 0,1280, 720 };


	int loc, slot;
	while (context.step())
	{
		float time = context.getTime();

		ss_model = glm::translate(glm::vec3(sin(time), cos(time), 0)) * glm::rotate(time, glm::vec3(0, 1, 0));

		// Shadow
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow, false, true);

		loc = slot = 0;
		setUnifroms(shdr_shadow, loc, slot, light_proj, light_view, floor_model);
		s0_draw(fb_shadow, shdr_shadow, floor_geo);

		loc = slot = 0;
		setUnifroms(shdr_shadow, loc, slot, light_proj, light_view, ss_model);
		s0_draw(fb_shadow, shdr_shadow, ss_geo);

		loc = slot = 0;
		setUnifroms(shdr_shadow, loc, slot, light_proj, light_view, cube_modle);
		s0_draw(fb_shadow, shdr_shadow, cube_geo);

		// Light
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow1, false, true);

		loc = slot = 0;
		setUnifroms(shdr_shadow, loc, slot, light_proj1, light_view1, floor_model);
		s0_draw(fb_shadow1, shdr_shadow, floor_geo);

		setUnifroms(shdr_shadow, loc, slot, light_proj1, light_view1, ss_model);
		s0_draw(fb_shadow1, shdr_shadow, floor_geo);

		setUnifroms(shdr_shadow, loc, slot, light_proj1, light_view1, cube_modle);
		s0_draw(fb_shadow1, shdr_shadow, floor_geo);


		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);


		loc = slot = 0;
		setUnifroms(shdr_direct, loc, slot, cam_proj, cam_view, floor_model,
																			light_proj, light_view, fb_shadow.depthTarget, 
																			light_proj1, light_view1, fb_shadow1.depthTarget);
		
		s0_draw(screen, shdr_direct, floor_geo);


		loc = slot = 0;
		setUnifroms(shdr_direct, loc, slot, cam_proj, cam_view, ss_model,
																			light_proj, light_view, fb_shadow.depthTarget, 
																			light_proj1, light_view1, fb_shadow1.depthTarget); 
		s0_draw(screen, shdr_direct, ss_geo);


		loc = slot = 0;
		setUnifroms(shdr_direct, loc, slot, cam_proj, cam_view, cube_modle,
																			light_proj, light_view, fb_shadow.depthTarget, 
																			light_proj1, light_view1, fb_shadow1.depthTarget); 
		s0_draw(screen, shdr_direct, cube_geo);
	}


		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);
	
	context.Term();
	return 0;
}