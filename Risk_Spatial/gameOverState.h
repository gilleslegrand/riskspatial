/*
* =============================================
* Auteur:Gilles Sinotte, Etienne Germain
* Laboratoire: Projet finale
* Nom du fichier: gameOverState.h
* Date: 2021-12-18
* But: Objet gameOverState qui est l'écran affiché lors de la fin d'une partie avec des statistiques.
* =============================================
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include <fstream>
#include"vecteur.hpp"
//#include "mainMenuState.hpp"
using namespace sf;
using namespace std;
//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera 
//un init, update, draw et handleInput différent pour chaque fenêtre.
class gameOverState : public state
{
private:
	gameDataRef _data; //chaque state recevra le pointeur sur la gameData qui 
	//donne accès au stateMachine, au RenderWindow, au 
	//assertManager et au inputManager
	Sprite _background; //le sprite pour la background
	//{_rectangleFond,_rectangleStats,_replay,_menu,_quit}
	vecteur<RectangleShape> _rectangles;
	//{_titre,_nomJoueur,_tempsPris,_partiesGagnees,_play,_menu,_quitter}
	vecteur<Text> _textJeu;

	Text _titre;					
	Text _statsText[3];
	Text _play;

	SoundBuffer _soundImperialMarchBuffer;
	Sound _soundImperialMarch;

	double _clockTime;
	int _nombrePartieGagnee;
	bool _soundActive;

	Clock _gameTime;

	string _gagnant;
	
	int _armeeGagnant;

public:
	gameOverState(gameDataRef data, bool soundActive, Clock gameTime, string gagnant, int armeeGagnant);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
	void lireFichier();
	void ecrireFichier();
};