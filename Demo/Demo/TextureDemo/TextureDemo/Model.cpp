#include "model.h"

Model::Model()
{
}

// the method for updating those game objects that are updateable
void Model::update(sf::Time delta_time)
{

	// any updateable game object has an update method
	for (int i = 0; i < this->updateables.size(); i++)
	{
		updateables[i]->update(delta_time);
	}

}

