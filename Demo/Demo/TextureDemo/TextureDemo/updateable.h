#pragma once

#include <SFML/Graphics.hpp>

class Updateable
{

public:

	virtual void update(sf::Time) = 0;

	sf::Vector2i position;

};
