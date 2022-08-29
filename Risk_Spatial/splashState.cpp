/*
* =============================================
* Auteur: Alberto Oviedo
* Laboratoire: Projet finale
* Nom du fichier: splashState.cpp
* Date: 2021-12-07
* But: Objet splashStage (ecran debut du jeu)
* =============================================
*/
#include "splashState.h"
#include "mainMenuState.h"

//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
splashState::splashState(gameDataRef data) : _data(data)
{

}
//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void splashState::init()
{
	_data->assets.loadTexture("background", MENU_BACKGROUND_FILE_PATH);
	_data->assets.loadFont("Risk font", GAME_FONTS);


	_backHeadJeu.setScale(1.68, 1.5);
	_backHeadJeu.setSize(Vector2f(1600, 100));
	_backHeadJeu.setFillColor(Color::Blue);
	_backHeadJeu.setPosition(0, 0);
	_backHeadJeu.setOutlineColor(Color::White);
	_backHeadJeu.setOutlineThickness(2);

	_backNomJeu.setScale(1.68, 1.5);
	_backNomJeu.setSize(Vector2f(1600, 150));
	_backNomJeu.setFillColor(Color::Blue);
	_backNomJeu.setPosition(0, 750);
	_backNomJeu.setOutlineColor(Color::White);
	_backNomJeu.setOutlineThickness(2);


	_nomJeu.setFont(_data->assets.getFont("Risk font"));
	_nomJeu.setString("RISK SPATIAL");
	_nomJeu.setFillColor(Color::White);
	_nomJeu.setCharacterSize(108);
	_nomJeu.setOrigin(_nomJeu.getGlobalBounds().width / 2, 0);
	_nomJeu.setPosition(800, 750);

	_headJeu.setFont(_data->assets.getFont("Risk font"));
	_headJeu.setString("Ce Jeu est presente par Gilles Sinotte,\n     Etienne Germain et Alberto Oviedo");
	_headJeu.setFillColor(Color::White);
	_headJeu.setCharacterSize(66);
	_headJeu.setOrigin(_nomJeu.getGlobalBounds().width / 2, 0);
	_headJeu.setPosition(460, 0);

	_background.setTexture(_data->assets.getTexture("background"));
	_background.setScale(1.68, 1.5);
}
//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void splashState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
	}
}
//gère le délai, après 3 secondes, on veut afficher la prochaine fenêtre
void splashState::update(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > LOGO_STATE_SHOW_TIME)
	{
		//cette ligne creera la nouveau menu fait par Gilles.
		_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
		_data->machine.addState(stateRef(new mainMenuState(_data, true)), true);
		cout << "Le jeu commence" << endl;
	}

}
//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void splashState::draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);
	_data->window.draw(_backNomJeu);
	_data->window.draw(_backHeadJeu);
	_data->window.draw(_headJeu);
	_data->window.draw(_nomJeu);

	_data->window.display();
}