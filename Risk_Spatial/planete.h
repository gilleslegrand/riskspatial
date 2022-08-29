/*
* =============================================
* Auteur: Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: planete.h
* Date: 2021-12-18
* But: objet planete qui gere les caractéristiques des planetes
* =============================================
*/

#pragma once
#include<cassert>
#include<SFML/Graphics/CircleShape.hpp>
#include"game.h"
#include"DEFINITIONS.hpp"
#include <string.h>
#include <list>


using namespace std;
using namespace sf;

class planete
{
	private:

	typedef	struct _caracteristiques {
			CircleShape _forme;
			int _nombreArmee;
			string _nom;
			string _def;
			int _nbArmeeTour;
			string _typePlanete;
			Text _nombreArmeeText;
			Text _defText;
			string _leader;
		};

	
	public:
		_caracteristiques* _planetes;

		planete();
		~planete();

		void init();

		void ajoutArmee(int nb);
		void supprimeArmee(int nb);
		int getNbArmee();

		string getNom()const;
		void setNom( string nom);

		string getDef()const;
		void setDef( string def);

		int getArmeeTour(const Color color);

		string getTypePlanete(const Color color)const;

		void setArmeeText();

		void setDefText();

		void setLeader(string leader);

		_caracteristiques* getPlanet()const;

		Color getColor(int nombre);
};

