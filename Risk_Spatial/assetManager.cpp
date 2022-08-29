/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: assetManager.cpp
* Date: 2021-12-07
* But: methodes de assetManager
* =============================================
*/
#include "assetManager.h"

//load la texture et la met dans la map
void assetManager::loadTexture(string name, string fileName)
{
	Texture tex;
	if (tex.loadFromFile(fileName)) {
		_textures[name] = tex;
	}
}
//retourne la texture de la map correspondant au nom reçu
Texture& assetManager::getTexture(string name)
{
	return _textures.at(name);
}

void assetManager::loadFont(string name, string fileName)
{
	Font fon;
	if (fon.loadFromFile(fileName)) {
		_fonts[name] = fon;
	}
}

Font& assetManager::getFont(string name)
{
	return _fonts.at(name);
}
