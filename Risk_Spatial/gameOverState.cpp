/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: gameOverState.cpp
* Date: 2021-12-07
* But: methodes de gameOverState
* =============================================
*/


#include "gameOverState.h"
#include "gameState.h"
#include <fstream>


//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
gameOverState::gameOverState(gameDataRef data, bool soundActive, Clock gameTime, string gagnant, int armeeGagnant) : _data(data), _gameTime(gameTime), _gagnant(gagnant), _armeeGagnant(armeeGagnant)
{
	_soundActive = soundActive;
	if (!_soundImperialMarchBuffer.loadFromFile(SOUND_IMPERIAL_MARCH_FILEPATH)) {
		cout << "erreur loading sound effect" << endl;
	}
	_soundImperialMarch.setBuffer(_soundImperialMarchBuffer);
	_clockTime = 0;
	_nombrePartieGagnee = 0;
	_rectangles.clear();
}
//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void gameOverState::init()
{
	if (_soundActive)
	{
		_soundImperialMarch.setLoop(true);
		_soundImperialMarch.setVolume(50);
		_soundImperialMarch.play();
	}
	_data->assets.loadTexture("background", MENU_BACKGROUND_FILE_PATH);
	_background.setTexture(_data->assets.getTexture("background"));
	_background.setScale(1.68, 1.5);

	_data->assets.loadFont("font background", GAME_FONTS);

	//lireFichier();
	//ecrireFichier();

	_rectangles.resize(5);
	for (int i = 0; i < _rectangles.size(); i++)
	{
		_rectangles.at(i).setFillColor(Color::Blue);
		_rectangles.at(i).setOutlineColor(Color::White);
		_rectangles.at(i).setOutlineThickness(2);
	}


	_rectangles[0].setPosition(0, 750);
	_rectangles[0].setSize(Vector2f(1600, 160));

	_rectangles[1].setSize(Vector2f(1300, 300));
	_rectangles[1].setPosition((_data->window.getSize().x / 2) - (_rectangles[1].getGlobalBounds().width / 2), 50);

	_rectangles[2].setSize(Vector2f(400, 100));
	_rectangles[2].setPosition((_data->window.getSize().x / 2) - (_rectangles[2].getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_rectangles[2].getGlobalBounds().height / 2));

	_rectangles[3].setSize(Vector2f(400, 100));
	_rectangles[3].setPosition(_data->window.getSize().x / 4 - 10, (_data->window.getSize().y / 2) + (_rectangles[2].getGlobalBounds().height / 2) * 1.20);

	_rectangles[4].setSize(Vector2f(400, 100));
	_rectangles[4].setPosition(_rectangles[3].getPosition().x + _rectangles[3].getPosition().x + 20, _rectangles[3].getPosition().y);

	_textJeu.resize(7);
	for (int i = 0; i < _textJeu.size(); i++)
	{
		_textJeu[i].setFillColor(Color::White);
		_textJeu[i].setFont(_data->assets.getFont("font background"));
	}

	_textJeu[0].setString("RISK SPATIAL");
	_textJeu[0].setCharacterSize(108);
	_textJeu[0].setOrigin(_textJeu[0].getGlobalBounds().width / 2, 0);
	_textJeu[0].setPosition(800, 750);

	_textJeu[1].setCharacterSize(35);
	_textJeu[1].setString("LE JOUEUR GAGNANT EST : " + _gagnant);
	_textJeu[1].setPosition(_rectangles[1].getPosition().x + _rectangles[1].getGlobalBounds().width / 6, _rectangles[1].getPosition().y + 40);

	_textJeu[2].setCharacterSize(35);
	_textJeu[2].setString("LA PARTIE A DUREE : " + to_string(_gameTime.getElapsedTime().asSeconds()) + " SECONDES");
	_textJeu[2].setPosition(_textJeu[1].getPosition().x, _textJeu[1].getPosition().y + (_textJeu[1].getPosition().y / 2) + 20);

	_textJeu[3].setCharacterSize(35);
	_textJeu[3].setString("LE NOMBRE DE SOLDATS VAIQUEURS : " + to_string(_armeeGagnant));
	_textJeu[3].setPosition(_textJeu[2].getPosition().x, _textJeu[2].getPosition().y + (_textJeu[2].getPosition().y / 3) + 20);

	_textJeu[4].setString("REJOUER");
	_textJeu[4].setCharacterSize(56);
	_textJeu[4].setOrigin(_rectangles[2].getGlobalBounds().width / 2, 0);
	_textJeu[4].setPosition(_rectangles[2].getPosition().x + _rectangles[2].getGlobalBounds().width / 2 + 40, _data->window.getSize().y / 2 - 40);

	_textJeu[5].setString("MENU");
	_textJeu[5].setCharacterSize(56);
	_textJeu[5].setOrigin(_rectangles[3].getGlobalBounds().width / 2, 0);
	_textJeu[5].setPosition(_rectangles[3].getPosition().x * 1.8, _rectangles[3].getPosition().y + 10);

	_textJeu[6].setString("QUITTER");
	_textJeu[6].setCharacterSize(56);
	_textJeu[6].setOrigin(_rectangles[4].getGlobalBounds().width / 2, 0);
	_textJeu[6].setPosition(_rectangles[4].getPosition().x * 1.33, _rectangles[4].getPosition().y + 10);
}
//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void gameOverState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else if (_data->input.isRectangleClicked(_rectangles[4], Mouse::Left, _data->window)) {
			//create new state main screen
			_data->window.close();
		}
		else if (_data->input.isRectangleClicked(_rectangles[3], Mouse::Left, _data->window)) {
			//create new state main screen
			_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
			_data->machine.addState(stateRef(new mainMenuState(_data, _soundActive)), true);
			_soundImperialMarch.stop();
			cout << "aller au menu" << endl;
		}
		else if (_data->input.isRectangleClicked(_rectangles[2], Mouse::Left, _data->window)) {
			//create new state main screen
			_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
			_data->machine.addState(stateRef(new gameState(_data, _soundActive)), true);
			_soundImperialMarch.stop();
			cout << "rejouer" << endl;
		}

	}
}


void gameOverState::update(float dt)
{

}

void gameOverState::draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	for (int i = 0; i < _rectangles.size(); i++)
	{
		_data->window.draw(_rectangles.at(i));
	}
	for (int i = 0; i < 7; i++)
	{
		_data->window.draw(_textJeu[i]);
	}
	_data->window.display();
}

void gameOverState::lireFichier() {
	ifstream fichier(FICHIER_SCORE);
	if (!fichier.is_open()) {
		cout << "ERREUR" << endl;
		system("pause");
		exit(0);
	}

	fichier >> _nombrePartieGagnee;
	fichier.close();
}

void gameOverState::ecrireFichier() {
	ofstream fichier(FICHIER_SCORE);
	if (!fichier.is_open()) {
		cout << "ERREUR" << endl;
		system("pause");
		exit(0);
	}
	fichier << _nombrePartieGagnee;
	fichier.close();
}