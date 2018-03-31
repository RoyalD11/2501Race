#include "Enemy.h"


Enemy::Enemy(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity, glm::vec3 maxSpeed, glm::vec3 acceleration)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), player(playerEntity)
{
	//variables added to help with implementation of methods below
	bool check = true;
	float calc = rotationAmount;
	//Sets the initial position and velocity
	targetPosition = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);

	this->maxSpeed = maxSpeed;//glm::vec3(2, 2, 0);

	this->acceleration = acceleration;// glm::vec3(1, 1, 0);
	max_accel = glm::vec3(2, 2, 0);

	dVelocity = glm::vec3(0, 0, 0);
	iVelocity = glm::vec3(0, 0, 0);
	rotationAmount = -90;

	spriteCount = 0;
	time = 100;
}

//methods to make the enemies move, once they hit the borders of the screen they reverse their direction
void Enemy::update(double deltaTime) {

	//targetPosition = player->getPosition();
	rotateTo(player->getPosition().x, player->getPosition().y);
	//rotateTo(targetPosition.x,targetPosition.y);

	//dVelocity = (targetPosition - position);
	dVelocity.x = (targetPosition.x - position.x) / deltaTime;
	dVelocity.y = (targetPosition.y - position.y) / deltaTime;
	targetPosition = position;
	acceleration = (max_accel * (dVelocity - velocity));// / (glm::abs(dVelocity - velocity));

	velocity.x += (acceleration.x * deltaTime);
	velocity.y += (acceleration.y * deltaTime);


	if (velocity.x > maxSpeed.x || velocity.x < (-1 * maxSpeed.x)) {
		velocity.x = (maxSpeed.x*velocity.x) / (glm::abs(velocity.x));
	}
	if (velocity.y > maxSpeed.y || velocity.y < (-1 * maxSpeed.y)) {
		velocity.y = (maxSpeed.y*velocity.y) / (glm::abs(velocity.y));
	}

	

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	//position.x += cos(rotationAmount * 0.01745333) * deltaTime * velocity.y;
	//position.y += sin(rotationAmount * 0.01745333) * deltaTime * velocity.y;

	animate();
}

//Changes the sprite currently being displayed
void Enemy::animate() {
	if (spriteCount == tex.size()) {
		spriteCount = 0;
	}

	if (time <= 0) {
		texture = tex[spriteCount];
		time = 100;
		spriteCount++;
	}

	time--;
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

void Enemy::rotateTo(float x, float y) {

	rotationAmount = atan2(y, x) * (180 / 3.14);
	rotationAmount *= -1;
}

void Enemy::setTarget(glm::vec3 pos) {
	targetPosition = pos;
}