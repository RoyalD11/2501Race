#pragma once
#include "GameEntity.h"
#include "Player.h"

class Item : public GameEntity {
public:
	Item(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint entityNumElements);

	void collision(Player player);

	int randomItem();

	void animate(GLuint t);

	int getCurrentItem();

private:
	int currentItem;
	bool hit;
};