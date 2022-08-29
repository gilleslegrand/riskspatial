/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo
* Laboratoire: Projet finale
* Nom du fichier: optionState.cpp
* Date: 2021-12-07
* But: methodes de optionState
* =============================================
*/

#include "optionState.h"

//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
optionState::optionState(gameDataRef data, bool soundActive) : _data(data)
{
	
	_musicIsOn = soundActive;

}
//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void optionState::init()
{
	_data->assets.loadTexture("background", MENU_BACKGROUND_FILE_PATH);
	_background.setTexture(_data->assets.getTexture("background"));

	_rectangleJeu.setSize(Vector2f(1600, 150));
	_rectangleJeu.setFillColor(Color::Blue);
	_rectangleJeu.setPosition(0, 750);

	_rectangleState.setSize(Vector2f(1600, 150));
	_rectangleState.setFillColor(Color::Blue);

	RectangleShape options;
	for (int i = 0; i < 2; i++)
	{
		_options.push_back(options);
	}

	for (int i = 0; i < _options.size(); i++)
	{
		_options[i].setSize(Vector2f(400, 100));
		_options[i].setPosition(600, _options[0].getGlobalBounds().height * i * 1.5 + 325);
		_options[i].setFillColor(Color::Blue);
		_options[i].setOutlineThickness(2);
		_options[i].setOutlineColor(Color::White);

	}

	_nomJeu.setFont(_data->assets.getFont("Risk font"));
	_nomJeu.setString("RISK SPATIAL");
	_nomJeu.setFillColor(Color::White);
	_nomJeu.setCharacterSize(108);
	_nomJeu.setOrigin(_nomJeu.getGlobalBounds().width / 2, 0);
	_nomJeu.setPosition(800, 750);

	_nomState.setFont(_data->assets.getFont("Risk font"));
	_nomState.setString("OPTIONS");
	_nomState.setFillColor(Color::White);
	_nomState.setCharacterSize(108);
	_nomState.setOrigin(_nomJeu.getGlobalBounds().width / 2, 0);
	_nomState.setPosition(950, 0);

	
	_menuButton.setFont(_data->assets.getFont("Risk font"));
	_musicButtonOn.setFont(_data->assets.getFont("Risk font"));
	_menuButton.setString("MENU");

	if (_musicIsOn)
	{
		_musicButtonOn.setString("MUSIC ON");

	}
	else
	{
		_musicButtonOn.setString("MUSIC OFF");
	}

	_menuButton.setFillColor(Color::White);
	_musicButtonOn.setFillColor(Color::White);

	_menuButton.setCharacterSize(56);
	_musicButtonOn.setCharacterSize(56);

	_menuButton.setOrigin(_menuButton.getGlobalBounds().width / 2, 0);
	_musicButtonOn.setOrigin(_musicButtonOn.getGlobalBounds().width / 2, 0);

	_menuButton.setPosition(800, _options[0].getPosition().y + 10);
	_musicButtonOn.setPosition(800, _options[1].getPosition().y + 10);

	_background.setScale(1.68, 1.5);
}
//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void optionState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else if (_data->input.isRectangleClicked(_options[0], Mouse::Left, _data->window))
		{
			_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
			_data->machine.addState(stateRef(new mainMenuState(_data,_musicIsOn)), true);
		}
		else if (_data->input.isRectangleClicked(_options[1], Mouse::Left, _data->window))
		{
			if (_musicButtonOn.getString()=="MUSIC ON")
			{
				_musicButtonOn.setString("MUSIC OFF");
				_musicButtonOn.setPosition(780, _options[1].getPosition().y + 10);
				_musicIsOn = false;
			}
			else
			{
				_musicButtonOn.setString("MUSIC ON");
				_musicButtonOn.setPosition(800, _options[1].getPosition().y + 10);
				_musicIsOn = true;
			}
		}
	}
}
//gère le délai, après 3 secondes, on veut afficher la prochaine fenêtre
void optionState::update(float dt)
{

}
//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void optionState::draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_rectangleJeu);
	_data->window.draw(_rectangleState);
	_data->window.draw(_nomState);
	_data->window.draw(_nomJeu);
	for (int i = 0; i < _options.size(); i++)
	{
		_data->window.draw(_options[i]);
	}
	_data->window.draw(_menuButton);
	_data->window.draw(_musicButtonOn);

	_data->window.display();
}