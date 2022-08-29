/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: hud.cpp
* Date: 2021-12-07
* But: methodes de hud
* =============================================
*/

#include "hud.h"

hud::hud(gameDataRef data) :_data(data)
{
	_texte.setFont(_data->assets.getFont("Risk font"));
	_texte.setString(" ");
	_texte.setCharacterSize(20);
	_texte.setFillColor(Color::White);
}

void hud::setPosition(int x, int y)
{
	_texte.setPosition(x, y);
}

void hud::setOrigin(int x, int y)
{
	_texte.setOrigin(x,y);
}



void hud::updateStats(int stats)
{
	_texte.setString(to_string(stats));
}

void hud::updateString(string s)
{
	_texte.setString(s);
}

void hud::draw() 
{
	_data->window.draw(_texte);
}