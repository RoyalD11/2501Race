#include "Enemy.h"


Enemy::Enemy(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), player(playerEntity)
{
	//variables added to help with implementation of methods below
	bool check = true;
	float calc = rotationAmount;
}

//methods to make the enemies move, once they hit the borders of the screen they reverse their direction
void Enemy::update(double deltaTime) {
	
	position.x += calc*(float)deltaTime;
	if (check) {
		calc = 0.4;
		if (position.x > 1) check = false;
	}
	else {
		calc = -0.4;
		if (position.x <= -1) check = true;
	}
	rotationAmount++;
}

//Changes the sprite currently being displayed
void Enemy::animate(GLuint t) {
	texture = t;
}

//method added to check collision, if the bullet radius is within the enemy radius then the enemy is removed from the screen
void Enemy::collision(Bullet bullet) {
	float colDetect = pow((bullet.getPosition().x - position.x), 2) + pow((bullet.getPosition().y - position.y), 2);
	if (pow(colDetect, 0.5) <= scale.x) {
		bullet.setPosition(10000.0); 
		position.y = 10000;
		hit = true;
	}
}

bool Enemy::getIfHit() {
	return hit;
}