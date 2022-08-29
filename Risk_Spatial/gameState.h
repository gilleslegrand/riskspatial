/*
* =============================================
* Auteur: Gilles Sinotte, Etienne Germain, Alberto Oviedo
* Laboratoire: Projet finale
* Nom du fichier: gameState.h
* Date: 2021-12-18
* But: Etat qui gere ce qui se passe durant le jeu
* =============================================
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "vecteur.hpp"
#include "mainMenuState.h"
#include "gameOverState.h"
#include "mapGilles.hpp"
#include "hud.h"
#include "planete.h"
#include "liste.hpp"
#include "des.h"

//#include "mainMenuState.hpp"
using namespace sf;
using namespace std;
//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera 
//un init, update, draw et handleInput différent pour chaque fenêtre.
class gameState : public state
{
private:
	gameDataRef _data; //chaque state recevra le pointeur sur la gameData qui 
	//donne accès au stateMachine, au RenderWindow, au 
	//assertManager et au inputManager
	Sprite _background; //le sprite pour la background

	RectangleShape _description;											//Le rectangle bleu pour la description de la planete
	RectangleShape _endTurnButton;											//Le rectangle bleu pour le boutton fin de tour
	
	vecteur<RectangleShape> _topMenuButtons;								//Les rectangles bleus pour le menu du haut
	vecteur<RectangleShape> _leftInfoButtons;								//Les rectangles bleus pour les informations du joueur
	vecteur<RectangleShape> _rightInfoButtons;								//Les rectangles bleus pour les informations de la planete
	vecteur<RectangleShape> _leftGameButtons;								//Les rectangles bleus pour les bouttons du jeu

	vecteur<Text> _topMenuTexts;											//Les textes pour le menu du haut
	vecteur<Text> _leftInfoTexts;											//Les textes pour les informations du joueur
	vecteur<Text> _rightInfoTexts;											//Les textes pour les informations de la planete
	vecteur<Text> _leftGameTexts;											//Les textes pour les bouttons du jeu

	Text _descriptionTitle;													//Le titre pour la description de la planete
	Text _endTurnText;														//Le texte pour le boutton fin de tour

	mappe<RectangleShape> _grill;											//la mappe contenant les cases de la grille du jeu
	mappe<planete> _planeteJeu;												//la mappe contenant les planetes du jeu

	liste<string> _nomliste;												//liste contenant les noms des planete avant de les répartir
	liste<string> _descPlanete;												//liste contenant les descriptions des planete avant de les répartir
	liste<string>::Iterator it;												//l'itérateur pour les listes de string

	SoundBuffer _soundHopeLoungeBuffer;										//musique de la partie
	SoundBuffer _soundDeesBuffer;											//bruit de dee lors des attaques
	SoundBuffer _soundExplosionBuffer;										//bruit de dee lors des attaques

	Sound _soundHopeLounge;													//musique de la partie
	Sound _soundDees;														//bruit de dee lors des attaques
	Sound _soundExplosion;													//bruit de dee lors des attaques

	des _attaque;															//dee pour l'attaque
	des _defense;															//des pour la defense

	int _noJoueur;															//int pour le joueur actif
	hud* _textJoueur;														//hud pour afficher le joueur actif
	int _nbAction;															//int pour le nombre d'action restant
	hud* _textAction;														//hud pour afficher le nombre d'action restant
	int _nbTroupe;															//int pour le nombre de troupe restant a placer
	hud* _textTroupe;														//hud pour afficher le nombre de troupe restant a placer

	hud* _leader;															//hud pour afficher le leader de la planete
	hud* _nomPlanete;														//hud pour afficher le nom de la planete
	hud* _typePlanete;														//hud pour afficher le type de la planete
	hud* _soldat;															//hud pour afficher le nombre de soldat de la planete
	hud* _croissance;														//hud pour afficher la croissance de soldat de la planete
	hud* _descriptionPlanete;												//Le texte pour la description de la planete



	bool _soundActive;														//booléen pour vérifier si le son doit etre allumer

	Clock _gameTime;														//Clock pour calculer la duree de la partie

public:
	gameState(gameDataRef data, bool soundActive);							//constructeur
	~gameState();															//destructeur

	void init();															//initialise les données de la partie
	void initPlanets(int& random);											//initialise les planete
	void initGameButton(sf::RectangleShape& rectangle, sf::Text& text);		//initialise les bouttons de jeu
	void initRightInfo(sf::RectangleShape& rectangle, sf::Text& text);		//initialise les informations de la planete
	void initPlayerInfo(sf::RectangleShape& rectangle, sf::Text& text);		//initialise les informations du joueur actif
	void initTopMenu(sf::RectangleShape& rectangle, sf::Text& text);		//initialise les bouttons du menu
	void initGrill();														//initialise la grille du jeu
	void initEndTurnButton();												//initialise le boutton de fin de tour
	void initDescription();													//initialise la description de la planete
	void initBackground();													//initialise l'image de fond
	void initSound();														//initialise le le son de la partie
	void initPlanetNameList();												//initialise la liste de planete
	void initDescList();													//initialise la liste de description

	void handleInput();														//gere les actions des joueurs
	void attack(int i, int j);												//gere les attaques des joueurs
	void deplaceTroupes(int i, int j);										//gere les deplacements de troupes
	void placeTroupe(int i, int j);											//gere les placements de troupes
	void selectChangeTroopPlaceButton();									//gere l'affichage du boutton de deplacement de troupe
	void selectPutNewTroopsButton();										//gere l'affichage du boutton des placements de troupes
	void selectAttackButton();												//gere l'affichage du boutton d'attaque
	void initNewTurn();														//initialise les données s'il y a un changement de tour
	void endTheGame();														//met fin à la partie
	void returnToMenu();													//retourne au menu

	void update(float dt);													//met à jour certaines données
	void draw(float dt);													//affiche la partie
};