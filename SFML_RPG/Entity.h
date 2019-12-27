#pragma once

#include"MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"

class Entity{
private:
	void initVariables();



protected:

	bool attacking;
	sf::Sprite sprite;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	AttributeComponent* attributeComponent;

	sf::Font font;

	sf::Text deathText;
	sf::Text missText;

	sf::RectangleShape hpBarMax;
	sf::RectangleShape hpBar;
	float hpRatio;

	/*Entity variables*/
	std::string name;
	int strength, agility, endurance, level, exp, levelExp;
	double currentHp, maxHp;


public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent();
	double doDamage();
	void getDamage(double damage);
	virtual void initHpBars();


	//Functions
	void setIsAttacking() { this->attacking = true; };
	bool getIsAttacking() { return this->attacking; };
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
	double getHp();

	std::stringstream getStatistics();
};


