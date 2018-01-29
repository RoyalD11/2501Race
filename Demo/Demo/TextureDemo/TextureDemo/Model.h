#pragma once

#include "updateable.hpp"

#include "player.hpp"
#include "background.hpp"

class Model
{

public:


	// MOVED FROM GAME.HPP
	std::vector<Updateable *> updateables;
	Player* the_player;
	Background*** backgroundSprites;


	Model();
	//~Model();

	void update(sf::Time);

};
