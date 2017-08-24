#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;

#include "glm\fwd.hpp"

void s0_draw(const Framebuffer &f,
			 const Shader &s,
			 const Geometry &g);

void clearFramebuffer(const Framebuffer &f);

void setUniform(const Shader &s, int location, float value);
void setUniform(const Shader &s, int location, int value);


void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);


namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec3 & val);
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec4 & val);
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::mat4 & val);
}

template<typename T, typename ...U>
void setUnifroms(const Shader &s, int &loc_io, int &tex_io, const T &val, U &&... uniforms)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);

	setUnifroms(s, loc_io, tex_io, uniforms...);
}


template<typename T>
void setUnifroms(const Shader &s, int &loc_io, int &tex_io, const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);

}



