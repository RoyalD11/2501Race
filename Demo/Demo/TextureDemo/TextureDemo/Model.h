#pragma once

#include "updateable.h"

#include "background.h"

class Model
{

public:


	// MOVED FROM GAME.HPP
	std::vector<Updateable *> Updateables;

	Background*** backgroundSprites;


	Model();
	//~Model();

	void update();

};
