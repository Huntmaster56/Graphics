#include "graphics\context.h"
#include <iostream>
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"

int main()
{
	Context context;
	context.init(800, 600);

	//make all of our penGL stuff
	Vertex verts[7] = { { { .0f , .0f, 0, 1 }  ,{ 1,0,0,0 } },
						{ { .5f , .0f, 0, 1 }  ,{ 1,1,0,0 } },
						{ { .25f, .5f, 0, 1 }  ,{ 0,1,0,0 } },
						{ {-.25f, .5f, 0, 1 }  ,{ 0,1,1,0 } },
						{ {-.5f , .0f, 0, 1 }  ,{ 0,0,1,0 } },
						{ {-.25f,-.5f, 0, 1 }  ,{ 0,0,1,1 } },
						{ { .25f,-.5f, 0, 1 }  ,{ 0,0,0,1 } } };

	unsigned idxs[18] = { 0,1,2,
		0,2,3,
		0,3,4,
		0,4,5,
		0,5,6,
		0,6,1 };
	unsigned char pixels[] = { 0,255,128,255,
							 255,128,255,0,
							   0,255,128,255,
							 255,128,255,0 };




	Geometry g = makeGeometry(verts, 7, idxs, 18);


	Framebuffer f = { 0, 800, 800 };

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		//"layout(location = 2) in vec2 uv;\n"
		"layout(location = 1) uniform float time;\n"
		//"out vec2 vUV;\n"
		//"out float timer;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = model * position;\n"
		//"gl_Position.x += sin(time*5+position.x)/5.0;\n"
		//"gl_Position.y += sin(time*3*position.y)/5.0;\n"
		//"vUV = uv;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"

		"layout(location = 0) uniform int k0;\n"
		"layout(location = 1) uniform int k1;\n"
		"layout(location = 2) uniform int k2;\n"

		"layout(location = 3) uniform vec4 c0 = vec4(1,0,0,1);\n"
		"layout(location = 4) uniform vec4 c1 = vec4(0,1,0,1);\n"
		"layout(location = 5) uniform vec4 c2 = vec4(0,0,1,1);\n"

		//"in vec2 vUV;\n"
		//"layout(location = 0) uniform sampler2D map;\n" 
		//"layout(location = 2) uniform int key;\n"
		//"in float timer;\n"
		"void main ()\n"
		"{\n "

		"outColor = c0*(1-k8) + cl*(1-k1) + cl*(1-k1); //vec4(k0, k1, k2, 1);\n"

		"}\n";
	Shader s = makeShader(vsource, fsource);

	Texture t_mask = makeTexture(4, 4, 1, pixels);
	Texture t_magyel = makeTexture(4, 1, 3, pixels);

	while (context.step())
	{ 
		clearFramebuffer(f);
		glm::mat4 mod1 = glm::translate(glm::vec3(.5, 0, 0)) *
						glm::rotate((float)context.getTime(), glm::vec3(0.f, 0.f, 1.f)) *
						glm::scale(glm::vec3(.5, .5, 1));

		//draw call
		//setUniform(s, 0, (float)context.getTime());
		//setUniform(s, 1, context.getKey(' '));
		//setUniform(s, 2, t_magyel, 0);
		//setUniform(s, 2, t_mask, 0);
		int loc = 0, tex = 0;
		setUnifroms(s, loc, tex, (int)context.getKey('A'), (int)context.getKey('S'), (int)context.getKey('D'), glm::vec4(1,1,1,1), glm::vec4(1, 0, 1, 1), glm::vec4(.5,.5,.5,1), mod1);
		s0_draw(f, s, g);
	}

	// delete everything!
	freeTexture(t_magyel);
	freeTexture(t_mask);
	freeGeometry(g);
	freeShader(s);
	context.Term();
	return 0;
}