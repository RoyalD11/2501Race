#pragma once
#include "Window.h"
#include "Player.h"

class HUD{

public:

	void initText2D(const char * texturePath);
	void printText2D(const char * text, int x, int y, int size);
	void cleanupText2D();
private:

};
