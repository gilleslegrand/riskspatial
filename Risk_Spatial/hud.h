/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: hud.h
* Date: 2021-12-18
* But: Gerer les changement de texte.
* =============================================
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"

class hud
{
private:
	gameDataRef _data;
	Text _texte;

public:
	hud(gameDataRef data);

	void setPosition(int x, int y);					//set la position du texte
	void setOrigin(int x, int y);					//set l'origine du texte
	void updateStats(int stats);					//met a jour les statistiques
	void updateString(string s);					//met a jour les chaines de caractere
	void draw();									//affiche les huds
};
