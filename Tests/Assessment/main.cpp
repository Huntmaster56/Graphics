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

	std::vector<std::string> faces;
	{
		"../../resources/textures/stormydays_ft.jpg";
		"../../resources/textures/stormydays_bk.jpg";

		"../../resources/textures/stormydays_up.jpg";
		"../../resources/textures/stormydays_dn.jpg";
		
		"../../resources/textures/stormydays_rt.jpg";
		"../../resources/textures/stormydays_lf.jpg";
	}
	Cubemap cubemap = loadCubemap(faces);

	Geometry skyBoxGeo;
	
	Shader skyBoxShader;

	glm::mat4 skyBoxScale;

	skyBoxGeo = loadGeometry("../../resources/models/cube.obj");

	skyBoxShader = loadShader("../../resources/shaders/skyBox.vert",
							  "../../resources/shaders/skyBox.frag");

	Framebuffer screen = { 0, 1280, 720 };
	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);




	Camera cam;

	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
		glm::vec3(0, 2, 0),
		glm::vec3(0, 1, 0));

	cam.proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	while (context.step())
	{
		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUnifroms(skyBoxShader, loc, slot, cam.proj, cam.view, skyBoxGeo);			// Light Information

		s0_draw(fBuffer, skyBoxShader, skyBoxGeo);

		clearFramebuffer(screen);


	}



}




 