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


	Texture tex = loadTexture("../../resources/textures/Duck.png");


	Vertex vquad[] = {
		{ { -1,-1,0,1 },{ 0,0,0,0 },{ 0,0 } },
		{ {  1,-1,0,1 },{ 0,0,0,0 },{ 1,0 } },
		{ {  1, 1,0,1 },{ 0,0,0,0 },{ 1,1 } },
		{ { -1, 1,0,1 },{ 0,0,0,0 },{ 0,1 } }
	};
	
	Framebuffer f = { 0, 800, 800 };


	unsigned quadidx[] = { 0,1,3, 1,2,3 };





	// Put all this in a load shader function!
	//std::ifstream ifsv("../../resources/shaders/test.vert");
	//std::string fv((std::istreambuf_iterator<char>(ifsv)), (std::istreambuf_iterator<char>()));
	//std::ifstream ifsf("../../resources/shaders/test.frag");
	//std::string ff((std::istreambuf_iterator<char>(ifsf)), (std::istreambuf_iterator<char>()));


	//Shader s = makeShader(fv.c_str(), ff.c_str());
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");
	
	Shader sq = loadShader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

	Shader scube = loadShader("../../resources/shaders/cube.vert", "../../resources/shaders/cube.frag");

	Framebuffer screen = { 0, 800, 800 };
	float x = 0, y = 0;
	while (context.step())
	{
		clearFramebuffer(f);
		float time = context.getTime();

		int frame = 3;
		frame += context.getKey('W') * 3;
		frame += context.getKey('A') * 2;
		frame += context.getKey('D') * 1;
		frame %= 4;

		x += context.getKey('D') * .016;
		y += context.getKey('W') * .016;
		x -= context.getKey('A') * .016;
		y -= context.getKey('S') * .016;

		int loc = 0, tslot = 0;
		//setUnifroms(sq, loc, tslot, tex, (int)(time*3) % 4 + frame*4, 4, 4,x,y);



		glm::mat4 mod_cube = glm::rotate(time, glm::vec3(1, 1, 1));
		
		setFlags(RenderFlag::DEPTH);

		
		loc = 0, tslot = 0;
		setUnifroms(scube, loc, tslot, mod_cube);
		s0_draw(screen, scube, quad);

	}



	context.Term();


}