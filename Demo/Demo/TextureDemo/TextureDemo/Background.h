#pragma once

#include "renderable.hpp"
#include "updateable.hpp"

class Background : public Renderable
{

public:
	Background();
	Background(int, int, int, int);
	~Background();
	sf::Vector2i position;
	int mode;
	int type;

};
