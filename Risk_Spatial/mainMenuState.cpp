/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: mainMenuState.cpp
* Date: 2021-12-07
* But: methodes de mainMenuState qui gere le menu
* =============================================
*/

#include "mainMenuState.h"
#include "gameState.h"
#include "optionState.h"
//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
mainMenuState::mainMenuState(gameDataRef data, bool music) : _data(data)
{
	_soundActive = music;
}
//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void mainMenuState::init()
{
	if (!_musicMenuBuffer.loadFromFile(SOUND_FUTURE_MANKIND_FILEPATH)) {
		cout << "erreur loading sound effect" << endl;
	}
	_musicMenu.setBuffer(_musicMenuBuffer);
	if (_soundActive)
	{
		_musicMenu.setLoop(true);
		_musicMenu.setVolume(50);
		_musicMenu.play();
	}

	_data->assets.loadTexture("background", MENU_BACKGROUND_FILE_PATH);
	_background.setTexture(_data->assets.getTexture("background"));

	_rectangleJeu.setSize(Vector2f(1600, 150));
	_rectangleJeu.setFillColor(Color::Blue);
	_rectangleJeu.setPosition(0,750);
	_rectangleJeu.setOutlineThickness(2);
	_rectangleJeu.setOutlineColor(Color::White);
	
	RectangleShape menu;
	for (int i = 0; i < 3; i++)
	{
		_menu.push_back(menu);
	}
	_menu[0].setSize(Vector2f(400, 100));

	for (int i = 0; i < _menu.size(); i++)
	{
		_menu[i].setSize(Vector2f(400,100));
		_menu[i].setPosition(600, _menu[0].getGlobalBounds().height * i *1.5+200);
		_menu[i].setFillColor(Color::Blue);
		_menu[i].setOutlineThickness(2);
		_menu[i].setOutlineColor(Color::White);
		
	}
	
	_background.setScale(1.68, 1.5);

	_data->assets.loadFont("Risk font", GAME_FONTS);

	_nomJeu.setFont(_data->assets.getFont("Risk font"));
	_playButton.setFont(_data->assets.getFont("Risk font"));
	_optionButton.setFont(_data->assets.getFont("Risk font"));
	_quitButton.setFont(_data->assets.getFont("Risk font"));

	_nomJeu.setString("RISK SPATIAL");
	_playButton.setString("JOUER");
	_optionButton.setString("OPTIONS");
	_quitButton.setString("QUITTER");

	_nomJeu.setFillColor(Color::White);
	_playButton.setFillColor(Color::White);
	_optionButton.setFillColor(Color::White);
	_quitButton.setFillColor(Color::White);

	_nomJeu.setCharacterSize(108);
	_playButton.setCharacterSize(56);
	_optionButton.setCharacterSize(56);
	_quitButton.setCharacterSize(56);


	_nomJeu.setOrigin(_nomJeu.getGlobalBounds().width / 2, 0);
	_playButton.setOrigin(_playButton.getGlobalBounds().width / 2, 0);
	_optionButton.setOrigin(_quitButton.getGlobalBounds().width / 2, 0);
	_quitButton.setOrigin(_quitButton.getGlobalBounds().width / 2, 0);


	_nomJeu.setPosition(800, 750);
	_playButton.setPosition(800, _menu[0].getPosition().y + 10);
	_optionButton.setPosition(800, _menu[1].getPosition().y + 10);
	_quitButton.setPosition(800, _menu[2].getPosition().y + 10);

}
//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void mainMenuState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else if (_data->input.isRectangleClicked(_menu[1], Mouse::Left, _data->window))
		{
			_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
			_data->machine.addState(stateRef(new optionState(_data, _soundActive)), true);
			_musicMenu.stop();
		}
		else if (_data->input.isRectangleClicked(_menu[0], Mouse::Left, _data->window))
		{
			_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
			_data->machine.addState(stateRef(new gameState(_data, _soundActive)), true);
			_musicMenu.stop();
		}
		else if (_data->input.isRectangleClicked(_menu[2], Mouse::Left, _data->window))
		{
			_data->window.close();
		}
	}

}

void mainMenuState::update(float dt)
{

}

void mainMenuState::draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_rectangleJeu);


	for (int i = 0; i < _menu.size(); i++)
	{
		_data->window.draw(_menu[i]);
	}
	_data->window.draw(_nomJeu);
	_data->window.draw(_playButton);
	_data->window.draw(_optionButton);
	_data->window.draw(_quitButton);
	_data->window.display();
}