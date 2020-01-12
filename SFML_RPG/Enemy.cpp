#include "stdafx.h"
#include "Enemy.h"
//Initializer functions
void Enemy::initVariables() {
	this->wasKilled = false;
	this->attributeComponent->name = "dummy";
}

void Enemy::initComponents(sf::Texture& texture_sheet) {
	this->createAnimationComponent(texture_sheet);
}


void Enemy::initAnimations() {
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 8, 12, 8, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 6.f, 0, 10, 9, 10, 32, 32);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 7, 6, 7, 32, 32);
}

//Constructors
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet) {
	this->initVariables();
	this->initComponents(texture_sheet);
	this->setPosition(x, y);
	this->initAnimations();
}


Enemy::~Enemy() {}

//Functions


void Enemy::updateAnimation(const float& dt) {

	if (this->attacking)
		if (this->animationComponent->play("ATTACK1", dt, true))
			this->attacking = false;

		this->animationComponent->play("IDLE", dt);

}

void Enemy::update(const float& dt) {
	this->updateHpBar();
	this->updateAnimation(dt);
}
