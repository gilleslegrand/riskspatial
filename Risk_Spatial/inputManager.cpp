/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: inputManager.cpp
* Date: 2021-12-07
* But: methodes de inputManager qui gere les inputs
* =============================================
*/

#include "inputManager.h"
//vérifie si on a cliqué sur le sprite de la fenêtre reçus en paramètre
bool inputManager::isRectangleClicked(const RectangleShape& object, Mouse::Button button, RenderWindow& window)
{
	if (Mouse::isButtonPressed(button))
	{
		IntRect tempRect(object.getPosition().x, object.getPosition().y,
			object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (tempRect.contains(Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

//retourne la position de la souris de la fenêtre reçue en paramètre
Vector2i inputManager::getMousePosition(RenderWindow& window) const
{
	return Mouse::getPosition(window);
}