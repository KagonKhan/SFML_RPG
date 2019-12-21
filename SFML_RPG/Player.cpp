#include "Player.h"
//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents(){

}



//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet){

	this->initVariables();
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 22.f, 45.f, 68.f, 78.f);
	this->createMovementComponent(400.f, 2000.f, 800.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 12, 0, 32, 32);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 7, 1, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 10.f, 0, 2, 9, 2, 32, 32);
	this->animationComponent->addAnimation("ATTACK2", 10.f, 0, 3, 9, 3, 32, 32);
	this->animationComponent->addAnimation("ATTACK3", 10.f, 0, 4, 9, 4, 32, 32);

}


Player::~Player()
{
}

void Player::update(const float& dt){
	Entity::update(dt);

	
	if(this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);


	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->sprite.setOrigin(28.f, 0.f);
		this->sprite.setScale(-4.f, 4.f);
		this->animationComponent->play("WALK", dt, -this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP)) {
		this->animationComponent->play("WALK", dt, -this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}


	this->hitboxComponent->update();
}