#pragma once

// Forward declare GLFW's windows
// handling pointer type
class GLFWwindow;

class Context
{
private:
	GLFWwindow *handle;

public:
	bool getKey(int key);
	bool getMouseButton(int button);
	void GetCursorPos(double &x_out, double &y_out);
	double getTime();

	bool init(size_t width = 800, size_t hight = 600, const char *title = "Graphics");

	bool step();

	bool Term();
};