#pragma once
class AttributeComponent
{

public:
	//Leveling
	unsigned level, exp, levelExp, attributePoints;

	//Attributes
	unsigned strength, vitality, dexterity, agility, intelligence, luck;
	//Constructors

	AttributeComponent();
	virtual ~AttributeComponent();

	//Functions
};

