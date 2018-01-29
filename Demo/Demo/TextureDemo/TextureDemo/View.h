#pragma once


#include "model.hpp"

#include "renderable.hpp"

#include "updateable.hpp" // only when we start talking about dynamic casting


#include <SFML/Graphics.hpp>

class View
{

public:


	// MOVED FROM GAME.HPP
	sf::RenderWindow window;
	std::vector<Renderable *> renderables;


	Model* model;

	View(Model* model);
	//~View();

	void render();



};