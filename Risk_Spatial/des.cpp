/*
* =============================================
* Auteur: Alberto Oviedo
* Laboratoire: Projet finale
* Nom du fichier: des.h
* Date: 2021-12-07
* But: Objet dees
* =============================================
*/

#include "des.h"

des::des()
{
	srand(time(NULL));
	_resultat = rand() % 6 + 1;
}

void des::tirer(int nbdes)
{
	assert(nbdes != 0);
	_resultat = 0;
	for (int i = 0; i < nbdes; i++)
	{
		_resultat += rand() % 6 + 1;
	}
}

int des::getResultat() const
{
	return _resultat;
}
