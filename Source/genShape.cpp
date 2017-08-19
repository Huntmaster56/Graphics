#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"

//#include "genShape.h"
#include <cmath>

Geometry makeCheckerboard(int dim, float size)
{
	//unsigned vdim = dim +1;
	//unsigned vsize = vdim*vdim;
	//unsigned isize = 3 * 2 * dim * dim;
	//Vertex *verts = new Vertex[isize];
	//unsigned *idxs = new unsigned[isize];

	//float step = size / dim;
	//float offset = size / 2;
	//int l = 0;
	//
	//for (int i = 0; i < vsize; ++i)
	//{
	//	float x = (i % vdim)*step - offset;
	//	float y = (i / vdim)*step - offset;

	//	verts[i].position = { x,y,0,1 };
	//	verts[i].color = { rand(/ (float)RAND_MAX,rand(/ (float)RAND_MAX,rand(/ (float)RAND_MAX,1) };

	//		if (i % vdim != vdim - 1 && i / vdim != vdim - 1)
	//		{

	//	}


	//	verts[i] = { {x,y,0,1},{x,y,0,1} };

	//	idxs[i * 3 + 0] = N;
	//	idxs[i * 3 + 0] = i;
	//	idxs[i * 3 + 0] = i + 1;


	//}

	//Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	//delete[] verts;






	return Geometry{};
}