#pragma once
#include "State.h"
#include "TownState.h"
#include "PauseMenu.h"

class GameState : public State {
private:
	Player* player;
	Enemy* enemy;
	PauseMenu* pMenu;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initEnemy();
	void initFonts();
	void initPauseMenu();
	void initBackground();
	void initButtons();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	virtual ~GameState();

	//Functions

	void updateButtons();
	void renderButtons(sf::RenderTarget& target);

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};