#pragma once
#include "Entity.h"

class Player :	public Entity{
private:

	//Variables


	//Initializer functions
	void initVariables();
	void initHpBars();
	void initComponents();

public:
	//constructors
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	virtual void update(const float& dt);
	virtual void updateAttack(const float& dt);
	virtual void updateAnimation(const float& dt);
	void updateHpBar();


	void fullHeal();
	void deathAnimation(const float& dt);
	bool isAnimationDone(std::string key) { return this->animationComponent->isDone(key); };
	void addExp(unsigned amount);
};

