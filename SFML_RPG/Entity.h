#pragma once

#include"MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity{
private:
	void initVariables();



protected:

	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);


	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};


