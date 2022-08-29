/*
* =============================================
* Auteur: Gilles Sinotte
* Laboratoire: Projet finale
* Nom du fichier: main.cpp
* Date: 2021-12-07
* But: Demarrer le jeu de Risk
* =============================================
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "game.h"
#include "DEFINITIONS.hpp"

using namespace sf;

int main(void) 
{
	game risk(SCREEN_WIDTH, SCREEN_HEIGHT, "Risk Spatial");
	return EXIT_SUCCESS;
}