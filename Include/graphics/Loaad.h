#pragma once

#include "graphics\RenderObject.h"

#include <iostream>
#include<vector>
#include <string>

Texture loadTexture(const char *path);


Shader loadShader(const char *vpath, const char *fpath);

Cubemap loadCubemap(std::vector<std::string> faces);

Geometry loadGeometry(const char *path);