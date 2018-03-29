#pragma once
#include "GameEntity.h"
#include "Player.h"

class Item : public GameEntity {
public:
	Item(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint entityNumElements);

	void animate(GLuint t);

	void collision(Player player);

	int getCurrentItem();

	int randomItem();

	void resetBox(float x, float y);

private:
	int currentItem;
	bool hit;
};