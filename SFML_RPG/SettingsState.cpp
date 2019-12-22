#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
				: State(window, supportedKeys, states){

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

SettingsState::~SettingsState() {
	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it) {
		delete it->second;
	}
}

//Initializers
void SettingsState::initBackgrounds() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bg1.png")) {
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);

}
void SettingsState::initVariables() {

}
void SettingsState::initFonts() {
	if (this->font.loadFromFile("Fonts/Dosis-Light.otf")) {
		//	throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}

}

void SettingsState::initKeybinds() {

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}
	ifs.close();
}

void SettingsState::initButtons() {

	this->buttons["EXIT_STATE"] = new Button(500.f, 780.f, 250.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}



void SettingsState::updateInput(const float& dt) {

}

void SettingsState::updateButtons() {

	/*Updates buttons in the state and handles functionality*/

	for (auto it : this->buttons)
		it.second->update(this->mousePosView);


	//Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
		this->endState();


}

void SettingsState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();



}

void SettingsState::renderButtons(sf::RenderTarget& target) {
	for (auto it : this->buttons)
		it.second->render(target);

}

void SettingsState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

}
