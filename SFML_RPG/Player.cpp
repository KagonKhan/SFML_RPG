#include "stdafx.h"
#include "Player.h"
#include "Windows.h"
//Initializer functions

void Player::initComponents(sf::Texture& texture_sheet) {
	this->createAnimationComponent(texture_sheet);
}

void Player::initAnimations() {
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 12, 0, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 6.f, 0, 2, 9, 2, 32, 32);
	this->animationComponent->addAnimation("ATTACK2", 10.f, 0, 3, 9, 3, 32, 32);
	this->animationComponent->addAnimation("ATTACK3", 10.f, 0, 4, 9, 4, 32, 32);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 7, 6, 7, 32, 32);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet){
	this->initComponents(texture_sheet);
	this->initAnimations();
	this->setPosition(x, y);
	this->attributeComponent->name = "Kagon";
}


Player::~Player() {}

//Functions

void Player::fullHeal() {
	this->attributeComponent->hp = this->attributeComponent->hpMax;
}


void Player::updateAnimation(const float& dt) {

	if (this->attacking)
		if (this->animationComponent->play("ATTACK1", dt, true))
			this->attacking = false;

	this->animationComponent->play("IDLE", dt);
}




void Player::addExp(unsigned amount) {
	this->attributeComponent->gainExp(amount);
}


void Player::update(const float& dt){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->attributeComponent->gainExp(20);
	


	this->updateHpBar();
	this->updateAnimation(dt);

}
