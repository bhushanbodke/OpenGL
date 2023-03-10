#include "Utils.h"


float FPS(float currentFrame, double& LastFrame, int& frames)
{
	double deltaTime = currentFrame - LastFrame;
	if (deltaTime >= 1.0f)
	{
		float fps =(float) frames / deltaTime;
		std::cout << "FPS :" << fps << "\r";
		frames = 0.0f;
		LastFrame = currentFrame;
		return fps;
	}
	return 0.0f;
}
