#include "MovementComponent.h"






//Constructors
MovementComponent::MovementComponent
		(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
		: sprite(sprite),
		maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration){

	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent(){

}

//Accessors
const float& MovementComponent::getMaxVelocity() const {
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const {
	return this->velocity;
}





//functions


const bool MovementComponent::getState(const short unsigned state) const {
	switch (state) {
	case IDLE:
		if (this->velocity.x == 0.f and this->velocity.y == 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0)
			return true;
		break;
	default:
		break;
	}
	return false;
}


const bool MovementComponent::moving() const {
	if (this->velocity.x != 0.f or this->velocity.y != 0.f)
		return true;

	return false;
}


void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
	
	
	
	//Acceleration
	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
}


void MovementComponent::update(const float& dt){

	/*
	Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/

	if (this->velocity.x > 0.f) //Check for positive x
	{
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //Check for negative x
	{
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //Check for positive y
	{
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Check for negative y
	{
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(this->velocity * dt); //Uses velocity
}