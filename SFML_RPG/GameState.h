#pragma once
#include "State.h"
#include "PauseMenu.h"

class GameState : public State {
private:
	Player* player;
	PauseMenu* pMenu;
	sf::Font font;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
	void initBackground();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	virtual ~GameState();

	//Functions

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};