
#include "graphics\RenderObject.h"
#include "Graphics\Loaad.h"
#include <iostream>
#include <fstream>
#include <string>

#include "graphics\Vertex.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "obj\tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb\stb_image.h"


Texture loadTexture(const char *path)
{
	Texture retval = { 0 };

	int w, h, c;
	unsigned char *pixels;

	stbi_set_flip_vertically_on_load(true);

	pixels = stbi_load(path, &w, &h, &c, STBI_default);

	retval = makeTexture(w, h, c, pixels);

	stbi_image_free(pixels);

	return retval;
}

std::string fileToString(const char *path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	return str;
}




Shader loadShader(const char *vpath, const char *fpath)
{
	Shader retval = { 0 };


	//std::ifstream ifsv("../../resources/shaders/test.vert");
	//std::string fv((std::istreambuf_iterator<char>(ifsv)), (std::istreambuf_iterator<char>()));

	std::string vsource = fileToString(vpath);
	std::string fsource = fileToString(fpath);

	retval = makeShader(vsource.c_str(), fsource.c_str());

	return retval;
}




#include <random>
glm::vec4 randColor()
{
	return	{
		rand() / (float)RAND_MAX,
		rand() / (float)RAND_MAX,
		rand() / (float)RAND_MAX, 1 }; 

}




Geometry loadGeometry(const char *path)
{
	Geometry retval = { 0,0,0,0 };
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;




	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);







	size_t isize = attrib.vertices.size() / 3; //number of vertices
	size_t *indices = new unsigned[isize];



	//size_t isize = shapes[0].mesh.indices.size();
	//size_t *indices = new unsigned[isize];

	for (size_t i = 0; i < isize; ++i)
	{
		indices[i] = shapes[0].mesh.indices[i].vertex_index;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (size_t i = 0; i < vsize; ++i)
	{
		const float *p = &attrib.vertices[i * 3];
		verts[i].position = {p[0], p[1], p[2], 1};
		verts[i].color = randColor();
	}


	for (int i = 0; i < isize; ++i)
	{
		indices[i] = i;

		int pi = shapes[0].mesh.indices[0].vertex_index;
		int ni = shapes[0].mesh.indices[0].vertex_index;
		int ti = shapes[0].mesh.indices[0].vertex_index;

		attrib.vertices;
		attrib.normals;
		attrib.texcoords;

		verts[i].position;
		verts[i].texcoord;
		verts[i].normal;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;
	return retval;
}
