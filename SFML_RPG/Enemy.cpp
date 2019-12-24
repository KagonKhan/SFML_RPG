#include "stdafx.h"
#include "Enemy.h"
//Initializer functions
void Enemy::initVariables() {
	this->attacking = false;
}

void Enemy::initComponents() {

}



//Constructors
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet) {

	this->initVariables();
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 22.f, 45.f, 68.f, 78.f);
	this->createMovementComponent(400.f, 2000.f, 800.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 20.f, 0, 8, 12, 8, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 6.f, 0, 10, 9, 10, 32, 32);


}


Enemy::~Enemy()
{
}

//Functions

void Enemy::updateAttack(const float& dt) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->attacking = true;
}

void Enemy::updateAnimation(const float& dt) {

	if (this->attacking)
		if (this->animationComponent->play("ATTACK1", dt, true))
			this->attacking = false;


	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);


	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		if (this->sprite.getScale().x < 0.f) {
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(4.f, 4.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		if (this->sprite.getScale().x > 0.f) {
			this->sprite.setOrigin(28.f, 0.f);
			this->sprite.setScale(-4.f, 4.f);
		}
		this->animationComponent->play("WALK", dt, -this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP)) {
		this->animationComponent->play("WALK", dt, -this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Enemy::update(const float& dt) {
	this->movementComponent->update(dt);

	this->updateAttack(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}
