#pragma once

#include "GameEntity.h"
#include "Player.h"


class Menu : public GameEntity {
public:
	Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity);
	Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity, Player* p);



	void setPosition(float x,float y);
	virtual void update(double deltaTime) override;


private:
	Player* player;
};