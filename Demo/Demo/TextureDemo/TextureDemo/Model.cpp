#include "model.h"

Model::Model()
{
}

// the method for updating those game objects that are updateable
void Model::update()
{

	// any updateable game object has an update method
	for (int i = 0; i < this->Updateables.size(); i++)
	{
		Updateables[i]->update(delta_time);
	}

}

