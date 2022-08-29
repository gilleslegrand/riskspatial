/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: planete.cpp
* Date: 2021-12-07
* But: methodes de planete qui gere le menu
* =============================================
*/


#include "planete.h"

planete::planete() {
	_planetes = new _caracteristiques;
	_planetes->_def = "";
	_planetes->_nbArmeeTour = 0;
	_planetes->_nom = "";
	_planetes->_nombreArmee = 0;
	_planetes->_typePlanete = "";
}

planete::~planete() {
	delete _planetes;
}

void planete::init() {


	_planetes->_nombreArmee = 0;
	_planetes->_forme.setRadius(30.0);

}

void planete::ajoutArmee(int nb) {
	assert(nb >= 0);

	_planetes->_nombreArmee += nb;
}

void planete::supprimeArmee(int nb) {

	assert(nb >= 0 && nb <= _planetes->_nombreArmee);


	_planetes->_nombreArmee -= nb;
}

int planete::getNbArmee() {

	return _planetes->_nombreArmee;
}

Color planete::getColor(int nombre){
	switch (nombre) {
	case 1:
		return COULEUR_PLANETE_HABITABLE;
		break;
	case 2:
		return COULEUR_PLANETE_INHABITABLE;
		break;
	case 3:
		return COULEUR_DE_COMMENCEMENT;
		break;
	case 4:
		return COULEUR_PLANETE_PARADISIAQUE;
		break;
	}
}

string planete::getNom()const {
	return _planetes->_nom;
}

void planete::setNom(string nom) {
	_planetes->_nom = nom;
}

string planete::getDef()const {
	return _planetes->_def;
}

void planete::setDef(string def) {
	_planetes->_def = def;
}

int planete::getArmeeTour(const Color color) {

	if (color == COULEUR_DE_COMMENCEMENT) {
		return 3;
	}
	else if (color == COULEUR_PLANETE_INHABITABLE) {
		return 1;
	}
	else if (color == COULEUR_PLANETE_HABITABLE) {
		return 2;
	}
	else if (color == COULEUR_PLANETE_PARADISIAQUE) {
		return 6;
	}
	else {
		return 0;
	}
}

string planete::getTypePlanete( const Color color)const {

	if (color == COULEUR_DE_COMMENCEMENT) {
		return "Tempérée";
	}
	else if (color == COULEUR_PLANETE_INHABITABLE) {
		return "Inhabitable";
	}
	else if (color == COULEUR_PLANETE_HABITABLE) {
		return "Habitable";
	}
	else if (color == COULEUR_PLANETE_PARADISIAQUE) {
		return "Paradisiaque";
	}
	else {
		return "";
	}
}

void planete::setArmeeText() {
	_planetes->_nombreArmeeText.setString(to_string(_planetes->_nombreArmee));
}

void planete::setDefText() {
	_planetes->_defText.setString(_planetes->_def);
}

planete::_caracteristiques* planete::getPlanet()const {
	return _planetes;
}

void planete::setLeader(string leader) {
	_planetes->_leader = leader;
}