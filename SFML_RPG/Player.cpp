#include "stdafx.h"
#include "Player.h"
#include "Windows.h"
//Initializer functions


//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet){

	this->initVariables();
	this->initHpBars();
	this->setPosition(x, y);

	//this->createHitboxComponent(this->sprite, 22.f, 45.f, 68.f, 78.f);
//	this->createMovementComponent(400.f, 2000.f, 800.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 12, 0, 32, 32);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 7, 1, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 6.f, 0, 2, 9, 2, 32, 32);
	this->animationComponent->addAnimation("ATTACK2", 10.f, 0, 3, 9, 3, 32, 32);
	this->animationComponent->addAnimation("ATTACK3", 10.f, 0, 4, 9, 4, 32, 32);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 7, 6, 7, 32, 32);

	this->name = "Bagon";
	this->strength = this->agility = this->endurance = 5;
	this->level = 1;
	this->exp = 0;
	this->levelExp = 100;
	this->currentHp = this->maxHp = 100.f;
}

void Player::fullHeal() {
	this->currentHp = this->maxHp;
}

Player::~Player()
{
}

void Player::initHpBars() {
	this->hpBarMax.setSize(sf::Vector2f(32.f * 3.f, 10.f));
	this->hpBarMax.setOutlineThickness(1.f);
	this->hpBarMax.setOutlineColor(sf::Color::White);

	this->hpRatio = 32.f * 3.f;

	this->hpBar.setSize(sf::Vector2f(hpRatio, 10.f));
	
	this->hpBar.setFillColor(sf::Color::Red);


	this->deathText.setCharacterSize(25);
	this->deathText.setFont(this->font);
	this->deathText.setFillColor(sf::Color::Red);
	this->deathText.setOutlineThickness(1.f);
	this->deathText.setOutlineColor(sf::Color::Black);

	this->deathText.setString("DEAD");
}

void Player::initComponents(){

}
//Functions
void Player::initVariables(){
	this->attacking = false;
}

void Player::updateAttack(const float& dt){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->attacking = true;
}

void Player::updateAnimation(const float& dt){

	if (this->attacking)
		if (this->animationComponent->play("ATTACK1", dt, true))
			this->attacking = false;


	//if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	
	
//movement
	/*else if (this->movementComponent->getState(MOVING_RIGHT)) {
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
	}*/
}


void Player::deathAnimation(const float& dt) {
	this->animationComponent->play("DEATH", dt, true);
}

void Player::addExp(unsigned amount) {
	this->exp += amount;
}

void Player::updateHpBar() {
	this->hpRatio = static_cast<float>(this->currentHp / this->maxHp);
	this->hpBar.setSize(sf::Vector2f(this->hpRatio * 32.f * 3.f, 10.f));
	this->deathText.setPosition(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.f - this->deathText.getGlobalBounds().width/2.f - 5.f,
		this->sprite.getPosition().y - this->sprite.getGlobalBounds().height/4.f);
	this->hpBarMax.setPosition(sf::Vector2f(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y));
}

void Player::update(const float& dt){
	//this->movementComponent->update(dt);

	this->updateHpBar();
	this->updateAttack(dt);
	this->updateAnimation(dt);

//	this->hitboxComponent->update();
}
