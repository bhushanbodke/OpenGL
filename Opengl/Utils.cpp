#include "Utils.h"


int FPS(float currentFrame, double& LastFrame, int& frames)
{
	static int lastFps;
	double deltaTime = currentFrame - LastFrame;
	if (deltaTime >= 1.0f)
	{
		int fps =(float) frames / deltaTime;
		fps = fps;
		std::cout << "FPS :" << fps << "\r";
		frames = 0.0f;
		LastFrame = currentFrame;
		lastFps = fps;
		return fps;
	}
	return lastFps;
}
