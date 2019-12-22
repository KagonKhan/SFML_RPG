#pragma once
#include "Entity.h"

class Player :	public Entity{
private:

	//Variables
	bool attacking;

	//Initializer functions
	void initVariables();
	void initComponents();

public:
	//constructors
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	virtual void update(const float& dt);
	virtual void updateAttack(const float& dt);
	virtual void updateAnimation(const float& dt);

};

