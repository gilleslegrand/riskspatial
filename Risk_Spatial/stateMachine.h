/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: stateMachine.cpp
* Date: 2021-12-07
* But: Objet state machine qui gere les changements de states
* =============================================
*/

#pragma once
#include <memory>
#include <stack>
#include "state.hpp"
using namespace std;
typedef unique_ptr<state> stateRef; //un smartPointer de state
class stateMachine {
private:
	stack<stateRef> _states; //pile de pointeur pour empiler les fenêtres du jeu
	stateRef _newState; //la fenêtre active
	bool _isRemoving; //flag pour savoir ce qui se passe ds la fenêtre
	bool _isAdding;
	bool _isReplacing;
public:
	void addState(stateRef newState, bool isReplacing = true);        //permet de changer d'etat
	void removeState();
	void processStateChanges();
	stateRef& getActiveState(); //pas de const pour ce getteur, car il est setteur aussi
};