#include "Entity.h"
void Entity::initVariables(){
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;

}
//Constructors
Entity::Entity(){
	this->initVariables();
	
}

Entity::~Entity(){
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
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


//Functions
void Entity::move(const float dir_x, const float dir_y, const float& dt){
	if (this->movementComponent) {
		this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
	}
}

void Entity::setPosition(const float x, const float y){

		this->sprite.setPosition(x, y);
}

void Entity::update(const float& dt){
	if (this->movementComponent)
		this->movementComponent->update(dt);
	
}

void Entity::render(sf::RenderTarget& target){
	target.draw(this->sprite);
		
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
