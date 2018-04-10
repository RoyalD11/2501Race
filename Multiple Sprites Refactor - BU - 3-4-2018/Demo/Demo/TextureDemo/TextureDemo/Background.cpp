#include "Background.h"

//Extra library so I can hold all the bullets
#include <list>

Background::Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string type, int bgType)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type), bgType(bgType)
{

}


//Updates the position of the bullet, also rotates the bullet as it moves through the air
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Background::update(double deltaTime) {
	//loads rest of background images

}


void Background::setPosition(float change) {
	position.y = change;
	position.x = change;
	velocity.x = change;
	velocity.y = change;
}


