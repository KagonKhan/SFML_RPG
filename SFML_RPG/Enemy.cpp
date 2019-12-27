#include "stdafx.h"
#include "Enemy.h"
//Initializer functions
void Enemy::initVariables() {
	this->attacking = false;
	this->name = "dummy";
	this->strength = this->agility = this->endurance = 5;
	this->level = 1;
	this->exp = 0;
	this->levelExp = 100;
	this->currentHp = this->maxHp = 100.f;
	this->wasKilled = false;
}

void Enemy::initComponents() {

}



void Enemy::initHpBars() {
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


//Constructors
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet) {
	this->initHpBars();
	this->initVariables();
	this->setPosition(x, y);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 20.f, 0, 8, 12, 8, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 6.f, 0, 10, 9, 10, 32, 32);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 7, 6, 7, 32, 32);
}

void Enemy::updateHpBar() {
	this->hpRatio = static_cast<float>(this->currentHp / this->maxHp);
	this->hpBar.setSize(sf::Vector2f(this->hpRatio * 32.f * 3.f, 10.f));
	this->deathText.setPosition(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.f - this->deathText.getGlobalBounds().width / 2.f - 5.f,
		this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 4.f);
	this->hpBarMax.setPosition(sf::Vector2f(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y));
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

		this->animationComponent->play("IDLE", dt);

}

void Enemy::update(const float& dt) {
	this->updateAttack(dt);
	this->updateHpBar();
	this->updateAnimation(dt);

}

void Enemy::deathAnimation(const float& dt) {
	this->animationComponent->play("DEATH", dt, true);
}