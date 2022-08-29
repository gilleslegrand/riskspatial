/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: joueur.h
* Date: 2021-12-18
* But: Objet joueur.
* =============================================
*/

#pragma once
#include "des.h"
#include <string>

using namespace std;
class joueur
{
private:
	des* _des;
	int _nbDes;
	string _nom;

public:
	joueur();
	~joueur();
	void setNom(string nom);
	string getNom(string nom)const;
	void setNbDes(int nb);
	int getNbDes() const;
	void tirerDes(int nbdes);
	int getResultatTirage()const;

};

