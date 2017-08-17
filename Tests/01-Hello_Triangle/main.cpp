#include "graphics\context.h"
#include <iostream>


int main()
{
	Context context;
	context.init();



	double x = 0;
	double y = 0;
	while (context.step())
	{
		std::cout << "Why are you pressing G, you should be clicking the mouse." << context.getKey('G') << std::endl;
		std::cout << "Why are you clicking the mouse, you should be pressing G." << context.getMouseButton(0) << std::endl;
		context.GetCursorPos(x, y);
	}

	context.Term();
	return 0;
}