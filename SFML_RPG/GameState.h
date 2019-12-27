#pragma once
#include "State.h"
#include "TownState.h"
#include "PauseMenu.h"
#include "GameOverState.h"

class GameState : public State {
private:


	Player* player;
	Enemy* enemy;
	PauseMenu* pMenu;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	sf::RectangleShape background;
	sf::RectangleShape statBox;
	sf::Texture backgroundTexture;
	sf::Text statText;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initEnemy();
	void initFonts();
	void initPauseMenu();
	void initBackground();
	void initButtons();
	void initStatBox();
	void attack();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	virtual ~GameState();

	//Functions

	void updateButtons(const float& dt);
	void renderButtons(sf::RenderTarget& target);

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void updateStat(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};