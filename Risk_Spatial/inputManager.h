/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: inputManager.h
* Date: 2021-12-18
* But: Gerer les boutons
* =============================================
*/

#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class inputManager
{
public:
	bool isRectangleClicked(const RectangleShape& object, Mouse::Button button, RenderWindow& window);				//si le rectangle est cliquer
	Vector2i getMousePosition(RenderWindow& window) const;															//cherche la position de la souris
};