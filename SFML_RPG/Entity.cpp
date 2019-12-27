#include "stdafx.h"
#include "Entity.h"

//Constructors
Entity::Entity(){
	this->initVariables();
	this->initHpBars();
	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	this->attacking = false;
}


Entity::~Entity(){
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
	delete this->attributeComponent;
}


void Entity::initHpBars() {
	/*this->hpBarMax.setSize(sf::Vector2f(32.f*3.f, 10.f));
	this->hpBarMax.setPosition(sf::Vector2f(560, 820));
	this->hpBarMax.setOutlineThickness(1.f);
	this->hpBarMax.setOutlineColor(sf::Color::White);

	this->hpRatio = 32.f * 3.f;

	this->hpBar.setSize(sf::Vector2f(hpRatio, 10.f));
	this->hpBar.setPosition(sf::Vector2f(560, 820));
	this->hpBar.setFillColor(sf::Color::Red);


	this->deathText.setCharacterSize(25);
	this->deathText.setFont(this->font);
	this->deathText.setFillColor(sf::Color::Red);
	this->deathText.setOutlineThickness(1.f);
	this->deathText.setOutlineColor(sf::Color::Black);

	this->deathText.setString("DEAD");*/
}


void Entity::initVariables() {
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
	this->attributeComponent = nullptr;

}

//Component Functions



void Entity::setTexture(sf::Texture& texture){
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height){
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration){
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet){
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent() {
	//this->attributeComponent = new AttributeComponent();
}


//Functions
void Entity::move(const float dir_x, const float dir_y, const float& dt){
	if (this->movementComponent) {
		this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
	}
}

void Entity::setPosition(const float x, const float y){

		this->sprite.setPosition(x, y);
}


double Entity::getHp()
{
	 return this->currentHp;
}

std::stringstream Entity::getStatistics() {
	std::stringstream ss;
	ss << "\tName: " << this->name <<
		"\n\t\tHp: " << this->currentHp << "/" << this->maxHp <<
		"\n\t\tStrength: " << this->strength <<
		"\n\t\tEndurance: " << this->endurance <<
		"\n\t\tAgility: " << this->agility <<
		"\n\t\tLevel: " << this->level <<
		"\n\t\texp: " << this->exp << "/" << this->levelExp;
	return ss;
}

double Entity::doDamage() {
	return 20.f;
}

void Entity::getDamage(double damage) {
	this->currentHp -= damage;
}

void Entity::update(const float& dt) {

	if (this->movementComponent)
		this->movementComponent->update(dt);

}

void Entity::render(sf::RenderTarget& target){
	target.draw(this->sprite);
	//target.draw(this->missText);
	
	target.draw(this->hpBarMax);
	if(this->hpRatio >=0)
		target.draw(this->hpBar);
	if(this->hpRatio <= 0)
		target.draw(this->deathText);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);

}