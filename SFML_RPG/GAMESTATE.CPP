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
	this->pMenu->addButton("QUIT", 400.f, "Quit");
}

void GameState::initTextures() {
	if (!this->textures["IDLE"].loadFromFile("Resources/images/sprites/player/textureSheet.png"))
		throw"ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
}

void GameState::initPlayers(){
	this->player = new Player(1920 / 2 - 100, 1080 / 2 - 100, this->textures["IDLE"]);
}

//Constructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states){
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPlayers();
	this->initPauseMenu();
}


GameState::~GameState(){
	delete this->player;
	delete this->pMenu;
}



//Functions

void GameState::updateInput(const float& dt){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}

}

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

void GameState::update(const float& dt){
	this->updateInput(dt);
	this->updateMousePositions();
	if (!this->paused) { // Unpaused update
	

		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else {//paused
		
		this->pMenu->update(this->mousePosView);
	}

}

void GameState::render(sf::RenderTarget* target){
	if (!target)
		target = this->window;

	this->player->render(*target);

	if (this->paused) { //Pause menu render
		this->pMenu->render(*target);
	}
}
