#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include "Button.h"

class PauseMenu
{

private:
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font& font;
	sf::Text menuText;
	
	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();


	//Accessors
	std::map<std::string, Button*>& getButtons();

	//Functions
	void addButton(const std::string& key, float y, const std::string& text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

