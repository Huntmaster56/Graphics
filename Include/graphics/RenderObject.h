#pragma once


struct Vertex;

struct Geometry
{
	unsigned handle, // Vertex Array Object
		vbo,    // Vertex Buffer
		ibo,	 // Index Buffer
		size;	 // How many indices make up this model
};


Geometry makeGeometry(const Vertex *verts, size_t vsize,
					const unsigned *idxs, size_t isize);

	void freeGeometry(Geometry &g);


struct Shader
{
	unsigned handle;
};

Shader makeShader(const char * vert_src, const char *frag_src);
void freeShader(Shader &s);


struct Framebuffer
{
	unsigned handle, width, height;
};