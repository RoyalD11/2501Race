#include "Bullet.h"

//Extra library so I can hold all the bullets
#include <list>

Bullet::Bullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string type, glm::vec3 &bulletVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type)
{
	bulletRotate = rotationAmount;
	velocity = bulletVelocity;
}

//Updates the position of the bullet, also rotates the bullet as it moves through the air
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Bullet::update(double deltaTime) {

	position.x += velocity.x * (float)deltaTime * cos(bulletRotate * 0.01745333);
	position.y += velocity.y * (float)deltaTime * sin(bulletRotate * 0.01745333);
	rotationAmount = bulletRotate;

	
}

//Fires the bullet based on the position of the player
void Bullet::fire(glm::vec3 playerPos, float playerRotation) {
	velocity.x = 6;
	velocity.y = 6;
	position.x = playerPos.x;
	position.y = playerPos.y;
	bulletRotate = playerRotation;
}

void Bullet::setPosition(float change) {
	position.y = change;
	position.x = change;
	velocity.x = change;
	velocity.y = change;
	bulletRotate = change;

}

bool Bullet::outOfBounds() {
	if (position.x > 20 ||
		position.x < -20 ||
		position.y > 20 ||
		position.y < -20) {
		return true;
	}
	return false;
}