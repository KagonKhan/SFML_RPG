#pragma once
#include "Entity.h"

class Enemy : public Entity {
private:

	//Variables
	bool attacking, wasKilled;

	//Initializer functions
	void initVariables();
	void initComponents();

	void initHpBars();

public:
	//constructors
	Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();

	//Functions

	bool getWasKilled() { return this->wasKilled; };
	void setWasKilled(bool killed) { this->wasKilled = killed; };

	virtual void update(const float& dt);
	virtual void updateAttack(const float& dt);
	virtual void updateAnimation(const float& dt);
	void updateHpBar();
	void deathAnimation(const float& dt);
	bool isAnimationDone(std::string key) { return this->animationComponent->isDone(key); };
};

