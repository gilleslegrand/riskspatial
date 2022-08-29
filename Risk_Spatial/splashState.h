/*
* =============================================
* Auteur: Alberto Oviedo, 
* Laboratoire: Projet finale
* Nom du fichier: splashState.h
* Date: 2021-12-07
* But: Objet splashState (ecran debut du jeu)
* =============================================
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
//#include "mainMenuState.hpp"
using namespace sf;
using namespace std;
//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera 
//un init, update, draw et handleInput différent pour chaque fenêtre.
class splashState : public state
{
private:
	gameDataRef _data; //chaque state recevra le pointeur sur la gameData qui 
	//donne accès au stateMachine, au RenderWindow, au 
	//assertManager et au inputManager
	Clock _clock; //1re fenêtre a besoin d’une clock car elle disparait 
	//au bout de quelques secondes
	Sprite _background; //le sprite pour la background

	Text _nomJeu;
	Text _headJeu;
	RectangleShape _backHeadJeu;
	RectangleShape _backNomJeu;
public:
	splashState(gameDataRef data);								//constructeur
	void init();												//initialise l'etat
	void handleInput();											//gere les actions du joueur
	void update(float dt);
	void draw(float dt);										//affiche l'état
};