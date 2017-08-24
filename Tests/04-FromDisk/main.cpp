#include "graphics\context.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics/Loaad.h"


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

	Geometry cube = loadGeometry("../../resources/shaders/Duck.obj");
	
	Shader sq = loadShader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

	Framebuffer screen = { 0, 800, 800 };

	while (context.step())
	{
		clearFramebuffer(f);

		int loc = 0, tslot = 0;
		setUniform(sq, 0, tex, 0);

		s0_draw(screen, sq, quad);

	}



	context.Term();


}