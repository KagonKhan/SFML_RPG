#pragma once

#include "AnimationComponent.h"
#include "AttributeComponent.h"

class Entity{
private:
	virtual void initVariables();
	virtual void initHpBars();


protected:

	virtual void updateHpBar();
	bool attacking;
	sf::Sprite sprite;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;

	sf::Font font;
	sf::Text deathText;
	sf::Text missText;
	sf::RectangleShape hpBarMax;
	sf::RectangleShape hpBar;
	float hpRatio;

	/*Entity variables*/


public:

	virtual void deathAnimation(const float& dt);

	Entity();
	virtual ~Entity();

	//Component functions
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);
	void setTexture(sf::Texture& texture);



	//Functions
	virtual int doDamage();
	void getDamage(int damage);
	void setIsAttacking() { this->attacking = true; };
	bool getIsAttacking() { return this->attacking; };
	virtual void setPosition(const float x, const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
	double getHp();

	std::stringstream getStatistics();
};


