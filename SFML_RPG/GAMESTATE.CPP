#include "stdafx.h"
#include "GameState.h"
//Initializer functions
void GameState::initKeybinds(){

	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}
	ifs.close();
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		//throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
		;
}

void GameState::initPauseMenu(){
	this->pMenu = new PauseMenu(*this->window, this->font);
	this->pMenu->addButton("QUIT", 900.f, "Quit");
}

void GameState::initTextures() {
	if (!this->textures["IDLE"].loadFromFile("Resources/images/sprites/player/bigSheet.png"))
		throw"ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
}

void GameState::initPlayers(){
	this->player = new Player(550.f, 800.f, this->textures["IDLE"]);
}

void GameState::initBackground() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bgArena.png")) {
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);

}

void GameState::initEnemy(){
	this->enemy = new Enemy(1550.f, 800.f, this->textures["IDLE"]);
}



//Constructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states){
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPlayers();
	this->initPauseMenu();
	this->initButtons();
}


GameState::~GameState(){
	delete this->player;
	delete this->pMenu;
	delete this->enemy;

	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it) {
		delete it->second;
	}
}


//BUTTONS
void GameState::initButtons() {

	this->buttons["ATTACK1"] = new gui::Button(
		350.f, 10.f, 200.f, 50.f,
		&this->font, "Attack", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["ENEMY"] = new gui::Button(
		600.f, 10.f, 200.f, 50.f,
		&this->font, "Enemy", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["TOWN"] = new gui::Button(
		850.f, 10.f, 180.f, 50.f,
		&this->font, "Town", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

}

void GameState::updateButtons() {

	/*Updates buttons in the state and handles functionality*/

	for (auto it : this->buttons)
		it.second->update(this->mousePosView);

	//Attack
	if (this->buttons["ATTACK1"]->isPressed())
		;

	//Spawn enemy
	if (this->buttons["ENEMY"]->isPressed())
		this->initEnemy();


	//Town state
	if (this->buttons["TOWN"]->isPressed())
		this->states->push(new TownState(this->window, this->supportedKeys, this->states, this->player));


}

void GameState::renderButtons(sf::RenderTarget& target) {
	for (auto it : this->buttons)
		it.second->render(target);

}

//Functions
//Pause / Unpause the game
void GameState::updateInput(const float& dt){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}

}

//Player movement
void GameState::updatePlayerInput(const float& dt){

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

	
}

//Pause Menu Buttons
void GameState::updatePauseMenuButtons(){
	if (this->pMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt){
	this->updateInput(dt);
	this->updateButtons();
	this->updateMousePositions();

	this->updateKeytime(dt);

	if (!this->paused) { // Unpaused update

		this->updatePlayerInput(dt);

		this->player->update(dt);
		if(this->enemy)
			this->enemy->update(dt);
	}
	else {//paused
		
		this->pMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target){
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->player->render(*target);

	if(this->enemy)
		this->enemy->render(*target);

	if (this->paused) { //Pause menu render
		this->pMenu->render(*target);
	}

	this->renderButtons(*target);
}

