#include "stdafx.h"
#include "Entity.h"

//Constructors
Entity::Entity(){
	this->initVariables();
	this->initHpBars();

	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");

	this->createAttributeComponent(0);
}


Entity::~Entity(){
	delete this->animationComponent;
	delete this->attributeComponent;
}


void Entity::initHpBars() {
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

void Entity::updateHpBar() {
	this->hpRatio = static_cast<float>(this->attributeComponent->hp / this->attributeComponent->hpMax);
	this->hpBar.setSize(sf::Vector2f(this->hpRatio * 32.f * 3.f, 10.f));
	this->deathText.setPosition(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.f - this->deathText.getGlobalBounds().width / 2.f - 5.f,
		this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 4.f);
	this->hpBarMax.setPosition(sf::Vector2f(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y));
}

void Entity::deathAnimation(const float& dt) {
	this->animationComponent->play("DEATH", dt, true);
}


void Entity::initVariables() {
	this->animationComponent = nullptr;
	this->attributeComponent = nullptr;
	this->attacking = false;
}

//Component Functions



void Entity::setTexture(sf::Texture& texture){
	this->sprite.setTexture(texture);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet){
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level) {
	this->attributeComponent = new AttributeComponent(level);
}


//Functions
void Entity::setPosition(const float x, const float y){
	this->sprite.setPosition(x, y);
}


std::stringstream Entity::getStatistics() {
	std::stringstream ss;
	ss << "\tName: " << this->attributeComponent->name <<
		"\n\t\tHp: " << this->attributeComponent->hp << "/" << this->attributeComponent->hpMax <<
		"\n\t\tStrength: " << this->attributeComponent->strength <<
		"\n\t\tVitality: " << this->attributeComponent->vitality <<
		"\n\t\tAgility: " << this->attributeComponent->agility <<
		"\n\t\tLevel: " << this->attributeComponent->level;
	if (this->attributeComponent->attributePoints)
		ss << " (+)";
	ss << "\n\t\texp: " << this->attributeComponent->exp << "/" << this->attributeComponent->levelExp;
	return ss;
}

int Entity::doDamage() {
	return 20;
}

void Entity::getDamage(int damage) {
	this->attributeComponent->hp-= damage;
}

void Entity::update(const float& dt) {

}

void Entity::render(sf::RenderTarget& target){
	target.draw(this->sprite);
	//target.draw(this->missText);
	
	target.draw(this->hpBarMax);
	if(this->hpRatio >=0)
		target.draw(this->hpBar);
	if(this->hpRatio <= 0)
		target.draw(this->deathText);
}

double Entity::getHp() {
	return this->attributeComponent->hp;
}
