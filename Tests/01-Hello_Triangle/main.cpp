#include "graphics\context.h"
#include <iostream>
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"

int main()
{
	Context context;
	context.init(800,600);

	 //make all of our penGL stuff
	Vertex verts[7] = {{ { .0f, .0f, 0, 1 }  , {1,0,0,0} },
						 { { .5f, .0f, 0, 1 }  , {1,1,0,0} },
						 { { .25f, .5f, 0, 1 } , {0,1,0,0} },
					     { {-.25f, .5f, 0, 1 } , {0,1,1,0} },
						 { {-.5f, .0f, 0, 1 }  , {0,0,1,0} },
						 { {-.25f,-.5f, 0, 1 } , {0,0,1,1} },
						 { { .25f,-.5f, 0, 1 } , {0,0,0,1} }};
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
		"out vec4 vColor;\n"
		"void main () { gl_Position = position; vColor = color; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec4 vColor;\n"
		"void main () { outColor = vColor; }\n";
	//vec4(0.0, 1.0, 0.0, 1.0)
	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };


	while (context.step())
	{ //draw call
		s0_draw(f, s, g);
	}

	// delete everything!

	context.Term();
	return 0;
}