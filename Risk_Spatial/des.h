/*
* =============================================
* Auteur: Alberto Oviedo
* Laboratoire: Projet finale
* Nom du fichier: des.cpp
* Date: 2021-12-07
* But: Objet dees
* =============================================
*/

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <assert.h>

#pragma once
class des
{
private:
	int _resultat;				// valeur du dernier tirage des des ou de sa creation.

public:

	des();
	void tirer(int nbdes);		// tire un nombre de fois les des passe en parametre et accumule le resultat.
	int getResultat() const;	// retourne le resultat du dernier tirage. 
};

