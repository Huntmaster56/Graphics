#include "graphics\GameObject.h"
#include "graphics\Loaad.h"
#include "graphics\Vertex.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include <vector>


void main()
{
	Context context;
	context.init(1280, 720);

	std::vector<std::string> faces =
	{
		"../../resources/textures/stormydays_ft.tga",
			"../../resources/textures/stormydays_bk.tga",

			"../../resources/textures/stormydays_up.tga",
			"../../resources/textures/stormydays_dn.tga",

			"../../resources/textures/stormydays_rt.tga",
			"../../resources/textures/stormydays_lf.tga"
	};

	Cubemap cubemap = loadCubemap(faces);

	Geometry skyBoxGeo = loadGeometry("../../resources/models/cube.obj");
	
	Shader skyBoxShader = loadShader("../../resources/shaders/skyBox.vert",
		"../../resources/shaders/skyBox.frag");

	glm::mat4 skymodel = glm::scale(glm::vec3(20, 20, 20));

	Framebuffer screen = { 0, 1280, 720 };


	Camera cam;
	cam.view;
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);
	 
	int loc = 0, slot = 0;
	while (context.step())
	{
		float time = context.getTime();
		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		skymodel = glm::scale(glm::vec3(4, 4, 4)) * glm::rotate(time, glm::vec3(0, 1, 0));;

		loc = slot = 0;
		setUnifroms(skyBoxShader, loc, slot, cam.proj, cam.view, skymodel, cubemap);

		s0_draw(screen, skyBoxShader, skyBoxGeo);

	}
	context.Term();


}




   