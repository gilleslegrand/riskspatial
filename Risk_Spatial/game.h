/*
* =============================================
* Auteur:Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: Game.h
* Date: 2021-12-18
* But: Objet game qui ressemble tous les objets et methodes utilisés dans le jeu.
* =============================================
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include "stateMachine.h"
#include "assetManager.h"
#include "inputManager.h"

using namespace sf;
struct gameData {											
	stateMachine machine;
	RenderWindow window;
	assetManager assets;
	inputManager input;
};
typedef shared_ptr<gameData> gameDataRef;
class game
{
private:
	const float dt = 1.0f / 60.0f; //temps pour chaque frame (60 frames par sec.)
	Clock _clock;
	gameDataRef _data; //Le pointeur sur la struct gameData
public:
	game(int width, int height, string title);				//constructeur
	void run();												//demarre la partie
};

