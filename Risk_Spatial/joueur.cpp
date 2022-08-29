/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: joueur.cpp
* Date: 2021-12-07
* But: methodes de joueur
* =============================================
*/

#include "joueur.h"

joueur::joueur()
{
	_des = new des;
	_nbDes = 0;
	_nom = "";
}

joueur::~joueur()
{
	delete _des;
	_nbDes = 0;
	_nom = "";
}

void joueur::setNom(string nom)
{
	_nom = nom;
}

string joueur::getNom(string nom) const
{
	return _nom;
}

void joueur::setNbDes(int nb)
{
	_nbDes = nb;
}

int joueur::getNbDes() const
{
	return _nbDes;
}

void joueur::tirerDes(int nbdes)
{
	_des->tirer(nbdes);
}

int joueur::getResultatTirage() const
{
	return _des->getResultat();
}
