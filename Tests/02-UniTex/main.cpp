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

	Geometry g = makeGeometry(verts, 7, idxs, 18);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 0) uniform float time;\n"
		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = position;\n"
		"gl_Position.x += sin(time*5+position.x)/5.0;\n"
		"gl_Position.y += sin(time*3*position.y)/5.0;\n"
		" vColor = color;\n"
		"vUV = position.xy;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		//"layout(location = 0) uniform float time;\n"
		//"layout(location = 1) uniform int tog;\n"
		"layout(location = 2) uniform sampler2D map;\n"	
		"layout(location = 3) uniform sampler2D mask;\n"

		"in vec4 vColor;\n"
		"in vec2 vUV;\n"
		"void main ()\n"
		"{\n "
		"outColor = texture(map, vUV);\n"
		//"outColor = vec4(vUV,0,1);\n"
		//"if(tog == 1)\n"
		//"outColor = 1.0 - vColor;\n"
		//"else outColor = vColor;\n"
		//"outColor.r = 0.5+sin(time*50+gl_FragCoord.x/10)/2.0;\n"
		""
		"}\n";
	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };

	unsigned char pixels[] = {0,255,0,
							  0,0,255};

	Texture t_mask = makeTexture(4, 4, 1, pixels);
	Texture t_magyel = makeTexture(2, 1, 3, pixels);

	
	while (context.step())
	{ //draw call
		clearFramebuffer(f); 
		
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, context.getKey(' '));
		
		setUniform(s, 2, t_magyel, 0);
		setUniform(s, 2, t_mask, 0);

		s0_draw(f, s, g);
	}

	// delete everything!

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	freeTexture(t_mask);

	context.Term();
	return 0;
}