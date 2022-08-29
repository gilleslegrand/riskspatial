/*
* =============================================
* Auteur: Gilles Sinotte, Alberto Oviedo, Étienne Germain
* Laboratoire: Projet finale
* Nom du fichier: gameState.cpp
* Date: 2021-12-07
* But: methodes de gameState qui gere ce qui se passe durant la partie
* =============================================
*/

#include "gameState.h"
#include "gameOverState.h"

//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
gameState::gameState(gameDataRef data, bool soundActive) : _data(data)
{
	_gameTime.restart();


	_soundActive = soundActive;
	_noJoueur = 1;
	_nbAction = 2;
	_nbTroupe = 3;

	_textJoueur = nullptr;
	_textAction = nullptr;
	_textTroupe = nullptr;

	_leader = nullptr;
	_nomPlanete = nullptr;
	_typePlanete = nullptr;
	_soldat = nullptr;
	_croissance = nullptr;
	_descriptionPlanete = nullptr;
}
gameState::~gameState()
{
	_noJoueur = 0;
	_nbAction = 0;
	_nbTroupe = 0;

	delete _textJoueur;
	delete _textAction;
	delete _textTroupe;

	delete _leader;
	delete _nomPlanete;
	delete _typePlanete;
	delete _soldat;
	delete _croissance;
	delete _descriptionPlanete;

}
//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void gameState::init()
{
	srand(time(NULL));
	int random=0;

	initDescList();
	initPlanetNameList();

	initSound();
	
	initBackground();

	initDescription();
	initEndTurnButton();

	RectangleShape rectangle;
	Text text;

	initGrill();

	initTopMenu(rectangle, text);

	initPlayerInfo(rectangle, text);

	initGameButton(rectangle, text);

	initRightInfo(rectangle, text);

	initPlanets(random);
}



//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void gameState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event)) {
		if (event.type == Event::Closed)
			_data->window.close();
		else if (_data->input.isRectangleClicked(_topMenuButtons[0], Mouse::Left, _data->window))
		{
			returnToMenu();
		}
		else if (_data->input.isRectangleClicked(_topMenuButtons[1], Mouse::Left, _data->window))
		{
			endTheGame();
		}
		else if (_data->input.isRectangleClicked(_topMenuButtons[2], Mouse::Left, _data->window))
		{
			_data->window.close();
		}
		else if (_data->input.isRectangleClicked(_endTurnButton, Mouse::Left, _data->window))
		{
			initNewTurn();
			if (_noJoueur==1)
			{
				_description.setFillColor(Color::Blue);
				_endTurnButton.setFillColor(Color::Blue);
				for (int i = 0; i < _topMenuButtons.size(); i++)
				{
					_topMenuButtons[i].setFillColor(Color::Blue);
				}
				for (int i = 0; i < _leftInfoButtons.size(); i++)
				{
					_leftInfoButtons[i].setFillColor(Color::Blue);
				}
				for (int i = 0; i < _leftGameButtons.size(); i++)
				{
					_leftGameButtons[i].setFillColor(Color::Blue);
				}
				for (int i = 0; i < _rightInfoButtons.size(); i++)
				{
					_rightInfoButtons[i].setFillColor(Color::Blue);
				}
			}
			else
			{
				_description.setFillColor(Color{152,59,59});
				_endTurnButton.setFillColor(Color{ 152,59,59 });
				for (int i = 0; i < _topMenuButtons.size(); i++)
				{
					_topMenuButtons[i].setFillColor(Color{ 152,59,59 });
				}
				for (int i = 0; i < _leftInfoButtons.size(); i++)
				{
					_leftInfoButtons[i].setFillColor(Color{ 152,59,59 });
				}
				for (int i = 0; i < _leftGameButtons.size(); i++)
				{
					_leftGameButtons[i].setFillColor(Color{ 152,59,59 });
				}
				for (int i = 0; i < _rightInfoButtons.size(); i++)
				{
					_rightInfoButtons[i].setFillColor(Color{ 152,59,59 });
				}
			}
		}
		else if (_data->input.isRectangleClicked(_leftGameButtons[1], Mouse::Left, _data->window))
		{
			selectAttackButton();
		}
		else if (_data->input.isRectangleClicked(_leftGameButtons[2], Mouse::Left, _data->window))
		{
			selectPutNewTroopsButton();
		}
		else if (_data->input.isRectangleClicked(_leftGameButtons[0], Mouse::Left, _data->window))
		{
			selectChangeTroopPlaceButton();
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
					placeTroupe(i, j);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				deplaceTroupes(i, j);
			}
		}

		if (_nbAction == 0)
		{
			if (_noJoueur==1)
			{
				_leftGameButtons[1].setFillColor(Color::Blue);
			}
			else
			{
				_leftGameButtons[1].setFillColor(Color{ 152,59,59 });
			}
			
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				attack(i, j);
			}
		}

	}
}

void gameState::attack(int i, int j)
{
	if (_data->input.isRectangleClicked(_grill.at(i, j), Mouse::Left, _data->window)	//si la case est cliqué 
		&& _leftGameButtons[1].getFillColor() == Color::Red								//si le bouton d'attaque est cliqué
		&& ((_noJoueur == 1 && _grill.at(i, j).getOutlineColor() == Color::Blue) || (_noJoueur == 2 && _grill.at(i, j).getOutlineColor() == Color::Red)))   //si la case appartient au joueur actif
	{
		_grill.at(i, j).setOutlineColor(Color::White);
	}
	else if (!(_leftGameButtons[0].getFillColor() == Color::Red)						//s'assure que l'action de soit pas fait en cliquant sur un autre bouton
		&& _data->input.isRectangleClicked(_grill.at(i, j), Mouse::Left, _data->window) //si la case est cliqué
		&& _grill.at(i, j).getOutlineColor() == Color::White)							//si la case est selectionnee
	{
		if (_noJoueur == 1)
		{
			_grill.at(i, j).setOutlineColor(Color::Blue);
		}
		else
		{
			_grill.at(i, j).setOutlineColor(Color::Red);
		}
	}


	if (_planeteJeu.at(i, j)._planetes->_nombreArmee >= 2)
	{
		if (i != 4 && _leftGameButtons[1].getFillColor() == Color::Red								//si le bouton d'attaque est cliqué
			&& _data->input.isRectangleClicked(_grill.at(i + 1, j), Mouse::Left, _data->window)		//si la case est cliqué 
			&& _grill.at(i, j).getOutlineColor() == Color::White 
			&&((_noJoueur == 1 && _grill.at(i + 1, j).getOutlineColor() == Color::Red)				//pour ne pas attaquer une case qui nous appartiens
				|| (_noJoueur == 2 && _grill.at(i + 1, j).getOutlineColor() == Color::Blue) 
				|| _grill.at(i + 1, j).getOutlineColor() == Color::Transparent))
		{
			if (_soundActive) {
				_soundDees.play();
			}
			while (_planeteJeu.at(i + 1, j)._planetes->_nombreArmee > 0 && _planeteJeu.at(i, j)._planetes->_nombreArmee > 1)
			{
				_attaque.tirer(3);
				_defense.tirer(3);

				if (_attaque.getResultat() > _defense.getResultat())
				{
					_planeteJeu.at(i + 1, j).supprimeArmee(1);
				}
				else
				{
					_planeteJeu.at(i, j).supprimeArmee(1);
				}
			}
			if (_planeteJeu.at(i + 1, j)._planetes->_nombreArmee == 0)
			{
				if (_soundActive) {
					_soundExplosion.play();
				}
				_planeteJeu.at(i + 1, j)._planetes->_nombreArmee = _planeteJeu.at(i, j)._planetes->_nombreArmee - 1;
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 1;
				if (_noJoueur == 1)
				{
					_grill.at(i, j).setOutlineColor(Color::Blue);
					_grill.at(i + 1, j).setOutlineColor(Color::Blue);
				}
				else
				{
					_grill.at(i, j).setOutlineColor(Color::Red);
					_grill.at(i + 1, j).setOutlineColor(Color::Red);
				}
			}

			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i + 1, j).setArmeeText();

			_nbAction--;
			_textAction->updateStats(_nbAction);
			if (_noJoueur==1)
			{
				_leftGameButtons[1].setFillColor(Color::Blue);
			}
			else
			{
				_leftGameButtons[1].setFillColor(Color{ 152,59,59 });
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i + 1, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i + 1, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i + 1, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
		else if (i != 0 && _leftGameButtons[1].getFillColor() == Color::Red && _data->input.isRectangleClicked(_grill.at(i - 1, j), Mouse::Left, _data->window) && _grill.at(i, j).getOutlineColor() == Color::White && ((_noJoueur == 1 && _grill.at(i - 1, j).getOutlineColor() == Color::Red) || (_noJoueur == 2 && _grill.at(i - 1, j).getOutlineColor() == Color::Blue) || _grill.at(i - 1, j).getOutlineColor() == Color::Transparent))
		{
			if (_soundActive) {
				_soundDees.play();
			}
			while (_planeteJeu.at(i - 1, j)._planetes->_nombreArmee > 0 && _planeteJeu.at(i, j)._planetes->_nombreArmee > 1)
			{
				_attaque.tirer(3);
				_defense.tirer(3);

				if (_attaque.getResultat() > _defense.getResultat())
				{
					_planeteJeu.at(i - 1, j).supprimeArmee(1);
				}
				else
				{
					_planeteJeu.at(i, j).supprimeArmee(1);
				}
			}
			if (_planeteJeu.at(i - 1, j)._planetes->_nombreArmee == 0)
			{
				if (_soundActive) {
					_soundExplosion.play();
				}
				_planeteJeu.at(i - 1, j)._planetes->_nombreArmee = _planeteJeu.at(i, j)._planetes->_nombreArmee - 1;
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 1;
				if (_noJoueur == 1)
				{
					_grill.at(i, j).setOutlineColor(Color::Blue);
					_grill.at(i - 1, j).setOutlineColor(Color::Blue);
				}
				else
				{
					_grill.at(i, j).setOutlineColor(Color::Red);
					_grill.at(i - 1, j).setOutlineColor(Color::Red);
				}
			}

			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i - 1, j).setArmeeText();

			_nbAction--;
			_textAction->updateStats(_nbAction);
			if (_noJoueur == 1)
			{
				_leftGameButtons[1].setFillColor(Color::Blue);
			}
			else
			{
				_leftGameButtons[1].setFillColor(Color{ 152,59,59 });
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i - 1, j )._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i - 1, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i - 1, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
		else if (j != 4 && _leftGameButtons[1].getFillColor() == Color::Red && _data->input.isRectangleClicked(_grill.at(i, j + 1), Mouse::Left, _data->window) && _grill.at(i, j).getOutlineColor() == Color::White && ((_noJoueur == 1 && _grill.at(i, j + 1).getOutlineColor() == Color::Red) || (_noJoueur == 2 && _grill.at(i, j + 1).getOutlineColor() == Color::Blue) || _grill.at(i, j + 1).getOutlineColor() == Color::Transparent))
		{
			if (_soundActive) {
				_soundDees.play();
			}
			while (_planeteJeu.at(i, j + 1)._planetes->_nombreArmee > 0 && _planeteJeu.at(i, j)._planetes->_nombreArmee > 1)
			{

				_attaque.tirer(3);
				_defense.tirer(3);

				if (_attaque.getResultat() > _defense.getResultat())
				{
					_planeteJeu.at(i, j + 1).supprimeArmee(1);
				}
				else
				{
					_planeteJeu.at(i, j).supprimeArmee(1);
				}
			}
			if (_planeteJeu.at(i, j + 1)._planetes->_nombreArmee == 0)
			{
				if (_soundActive) {
					_soundExplosion.play();
				}
				_planeteJeu.at(i, j + 1)._planetes->_nombreArmee = _planeteJeu.at(i, j)._planetes->_nombreArmee - 1;
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 1;
				if (_noJoueur == 1)
				{
					_grill.at(i, j).setOutlineColor(Color::Blue);
					_grill.at(i, j + 1).setOutlineColor(Color::Blue);
				}
				else
				{
					_grill.at(i, j).setOutlineColor(Color::Red);
					_grill.at(i, j + 1).setOutlineColor(Color::Red);
				}
			}

			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i, j + 1).setArmeeText();

			_nbAction--;
			_textAction->updateStats(_nbAction);
			if (_noJoueur == 1)
			{
				_leftGameButtons[1].setFillColor(Color::Blue);
			}
			else
			{
				_leftGameButtons[1].setFillColor(Color{ 152,59,59 });
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i, j + 1)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j + 1)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j + 1)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
		else if (j != 0 && _leftGameButtons[1].getFillColor() == Color::Red && _data->input.isRectangleClicked(_grill.at(i, j - 1), Mouse::Left, _data->window) && _grill.at(i, j).getOutlineColor() == Color::White && ((_noJoueur == 1 && _grill.at(i, j - 1).getOutlineColor() == Color::Red) || (_noJoueur == 2 && _grill.at(i, j - 1).getOutlineColor() == Color::Blue) || _grill.at(i, j - 1).getOutlineColor() == Color::Transparent))
		{
			if (_soundActive) {
				_soundDees.play();
			}
			while (_planeteJeu.at(i, j - 1)._planetes->_nombreArmee > 0 && _planeteJeu.at(i, j)._planetes->_nombreArmee > 1)
			{
				_attaque.tirer(3);
				_defense.tirer(3);

				if (_attaque.getResultat() > _defense.getResultat())
				{
					_planeteJeu.at(i, j - 1).supprimeArmee(1);
				}
				else
				{
					_planeteJeu.at(i, j).supprimeArmee(1);
				}
			}
			if (_planeteJeu.at(i, j - 1)._planetes->_nombreArmee == 0)
			{
				if (_soundActive) {
					_soundExplosion.play();
				}
				_planeteJeu.at(i, j - 1)._planetes->_nombreArmee = _planeteJeu.at(i, j)._planetes->_nombreArmee - 1;
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 1;
				if (_noJoueur == 1)
				{
					_grill.at(i, j).setOutlineColor(Color::Blue);
					_grill.at(i, j - 1).setOutlineColor(Color::Blue);
				}
				else
				{
					_grill.at(i, j).setOutlineColor(Color::Red);
					_grill.at(i, j - 1).setOutlineColor(Color::Red);
				}
			}

			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i, j - 1).setArmeeText();

			_nbAction--;
			_textAction->updateStats(_nbAction);
			if (_noJoueur == 1)
			{
				_leftGameButtons[1].setFillColor(Color::Blue);
			}
			else
			{
				_leftGameButtons[1].setFillColor(Color{ 152,59,59 });
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i , j- 1)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j - 1)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j - 1)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
	}
}

void gameState::deplaceTroupes(int i, int j)
{
	if (_data->input.isRectangleClicked(_grill.at(i, j), Mouse::Left, _data->window) 
		&& _leftGameButtons[0].getFillColor() == Color::Red 
		&& ((_noJoueur == 1 && _grill.at(i, j).getOutlineColor() == Color::Blue) || (_noJoueur == 2 && _grill.at(i, j).getOutlineColor() == Color::Red)))        //si la case selectionner appartient au joueur actif
	{
		_grill.at(i, j).setOutlineColor(Color::White);
	}
	else if (!(_leftGameButtons[1].getFillColor() == Color::Red) 
		&& _data->input.isRectangleClicked(_grill.at(i, j), Mouse::Left, _data->window) 
		&& _grill.at(i, j).getOutlineColor() == Color::White)								//retablie les couleurs
	{
		if (_noJoueur == 1)
		{
			_grill.at(i, j).setOutlineColor(Color::Blue);

		}
		else
		{
			_grill.at(i, j).setOutlineColor(Color::Red);
		}
	}

	if (_planeteJeu.at(i, j)._planetes->_nombreArmee >= 2)
	{
		if (i != 4 && (_leftGameButtons[0].getFillColor() == Color::Red) 
			&& _data->input.isRectangleClicked(_grill.at(i + 1, j), Mouse::Left, _data->window) 
			&& _grill.at(i, j).getOutlineColor() == Color::White 
			&& ((_noJoueur == 1 && _grill.at(i + 1, j).getOutlineColor() == Color::Blue) || (_noJoueur == 2 && _grill.at(i + 1, j).getOutlineColor() == Color::Red)) 
			&& _grill.at(i + 1, j).getOutlineColor() != Color::Transparent)    //s'assure qu'on deplace les unités sur une case qui nous appartient
		{
			_planeteJeu.at(i, j)._planetes->_nombreArmee -= 1;
			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i + 1, j)._planetes->_nombreArmee += 1;
			_planeteJeu.at(i + 1, j).setArmeeText();
			if (_noJoueur == 1)
			{
				_grill.at(i, j).setOutlineColor(Color::Blue);
				_grill.at(i + 1, j).setOutlineColor(Color::Blue);
				if (_noJoueur==1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			else
			{
				_grill.at(i, j).setOutlineColor(Color::Red);
				_grill.at(i + 1, j).setOutlineColor(Color::Red);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			if (_planeteJeu.at(i, j)._planetes->_nombreArmee == 1)
			{
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i+1, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i + 1, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i + 1, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
		else if (i != 0 && (_leftGameButtons[0].getFillColor() == Color::Red) && _data->input.isRectangleClicked(_grill.at(i - 1, j), Mouse::Left, _data->window) && _grill.at(i, j).getOutlineColor() == Color::White && ((_noJoueur == 1 && _grill.at(i - 1, j).getOutlineColor() == Color::Blue) || (_noJoueur == 2 && _grill.at(i - 1, j).getOutlineColor() == Color::Red)) && _grill.at(i - 1, j).getOutlineColor() != Color::Transparent)
		{
			_planeteJeu.at(i, j)._planetes->_nombreArmee -= 1;
			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i - 1, j)._planetes->_nombreArmee += 1;
			_planeteJeu.at(i - 1, j).setArmeeText();
			if (_noJoueur == 1)
			{
				_grill.at(i, j).setOutlineColor(Color::Blue);
				_grill.at(i - 1, j).setOutlineColor(Color::Blue);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			else
			{
				_grill.at(i, j).setOutlineColor(Color::Red);
				_grill.at(i - 1, j).setOutlineColor(Color::Red);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}

			}
			if (_planeteJeu.at(i, j)._planetes->_nombreArmee == 1)
			{
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i-1, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i - 1, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i - 1, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
		else if (j != 4 && (_leftGameButtons[0].getFillColor() == Color::Red) && _data->input.isRectangleClicked(_grill.at(i, j + 1), Mouse::Left, _data->window) && _grill.at(i, j).getOutlineColor() == Color::White && ((_noJoueur == 1 && _grill.at(i, j + 1).getOutlineColor() == Color::Blue) || (_noJoueur == 2 && _grill.at(i, j + 1).getOutlineColor() == Color::Red)) && _grill.at(i, j + 1).getOutlineColor() != Color::Transparent)
		{
			_planeteJeu.at(i, j)._planetes->_nombreArmee -= 1;
			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i, j + 1)._planetes->_nombreArmee += 1;
			_planeteJeu.at(i, j + 1).setArmeeText();
			if (_noJoueur == 1)
			{
				_grill.at(i, j).setOutlineColor(Color::Blue);
				_grill.at(i, j + 1).setOutlineColor(Color::Blue);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			else
			{
				_grill.at(i, j).setOutlineColor(Color::Red);
				_grill.at(i, j + 1).setOutlineColor(Color::Red);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}

			if (_planeteJeu.at(i, j)._planetes->_nombreArmee == 1)
			{
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i, j + 1)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j + 1)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j + 1)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
		else if (j != 0 && (_leftGameButtons[0].getFillColor() == Color::Red) && _data->input.isRectangleClicked(_grill.at(i, j - 1), Mouse::Left, _data->window) && _grill.at(i, j).getOutlineColor() == Color::White && ((_noJoueur == 1 && _grill.at(i, j - 1).getOutlineColor() == Color::Blue) || (_noJoueur == 2 && _grill.at(i, j - 1).getOutlineColor() == Color::Red)) && _grill.at(i, j - 1).getOutlineColor() != Color::Transparent)
		{
			_planeteJeu.at(i, j)._planetes->_nombreArmee -= 1;
			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i, j - 1)._planetes->_nombreArmee += 1;
			_planeteJeu.at(i, j - 1).setArmeeText();
			if (_noJoueur == 1)
			{
				_grill.at(i, j).setOutlineColor(Color::Blue);
				_grill.at(i, j - 1).setOutlineColor(Color::Blue);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			else
			{
				_grill.at(i, j).setOutlineColor(Color::Red);
				_grill.at(i, j - 1).setOutlineColor(Color::Red);
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			if (_planeteJeu.at(i, j)._planetes->_nombreArmee == 1)
			{
				if (_noJoueur == 1)
				{
					_leftGameButtons[0].setFillColor(Color::Blue);
				}
				else
				{
					_leftGameButtons[0].setFillColor(Color{ 152,59,59 });
				}
			}
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i, j - 1)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j - 1)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j - 1)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
		}
	}
}

void gameState::placeTroupe(int i, int j)
{
	if (_nbTroupe != 0                  //s'il y a au moins 1 troupe à placer
		&& _data->input.isRectangleClicked(_grill.at(i, j), Mouse::Left, _data->window)					//si la case est cliqué
		&& _leftGameButtons[2].getFillColor() == Color::Red												//si le bouton de placement de troupe est selectionné								
		&& ((_noJoueur == 1 && _grill.at(i, j).getOutlineColor() == Color::Blue) 
			|| (_noJoueur == 2 && _grill.at(i, j).getOutlineColor() == Color::Red)))					//si la case appartient au joueur actif		
	{
		_planeteJeu.at(i, j).ajoutArmee(1);
		_planeteJeu.at(i, j).setArmeeText();
		_nbTroupe--;
		_textTroupe->updateStats(_nbTroupe);

		if (_grill.at(i, j).getOutlineColor() == Color::Blue)
		{
			_leader->updateString("Joueur 1");
		}
		else
		{
			_leader->updateString("Joueur 2");
		}
		_nomPlanete->updateString(_planeteJeu.at(i, j).getNom());
		_typePlanete->updateString(_planeteJeu.at(i, j)._planetes->_typePlanete);
		_soldat->updateStats(_planeteJeu.at(i, j).getNbArmee());
		_croissance->updateStats(_planeteJeu.at(i, j)._planetes->_nbArmeeTour);
		_descriptionPlanete->updateString(_planeteJeu.at(i, j).getDef());
		_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
	}
}

void gameState::selectChangeTroopPlaceButton()
{
	if (_noJoueur==1)
	{
		if (_leftGameButtons[0].getFillColor() == Color::Red)
		{
			_leftGameButtons[0].setFillColor(Color::Blue);
		}
		else
		{
			_leftGameButtons[0].setFillColor(Color::Red);
		}
		_leftGameButtons[1].setFillColor(Color::Blue);
		if (_leftGameButtons[2].getFillColor() == Color::Red)
		{
			_leftGameButtons[2].setFillColor(Color::Blue);

			_leader->updateString("");
			_nomPlanete->updateString("");
			_typePlanete->updateString("");
			_soldat->updateStats(0);
			_croissance->updateStats(0);
			_descriptionPlanete->updateString("");

		}
	}
	else
	{
		if (_leftGameButtons[0].getFillColor() == Color::Red)
		{
			_leftGameButtons[0].setFillColor(Color{ 152, 59, 59 });
		}
		else
		{
			_leftGameButtons[0].setFillColor(Color::Red);
		}
		_leftGameButtons[1].setFillColor(Color{ 152, 59, 59 });
		if (_leftGameButtons[2].getFillColor() == Color::Red)
		{
			_leftGameButtons[2].setFillColor(Color{ 152, 59, 59 });

			_leader->updateString("");
			_nomPlanete->updateString("");
			_typePlanete->updateString("");
			_soldat->updateStats(0);
			_croissance->updateStats(0);
			_descriptionPlanete->updateString("");

		}
	}
	
}

void gameState::selectPutNewTroopsButton()
{	
	if (_noJoueur==1)
	{
		if (_leftGameButtons[2].getFillColor() == Color::Red)
		{
			_leftGameButtons[2].setFillColor(Color::Blue);

			_leader->updateString("");
			_nomPlanete->updateString("");
			_typePlanete->updateString("");
			_soldat->updateStats(0);
			_croissance->updateStats(0);
			_descriptionPlanete->updateString("");
		}
		else
		{
			_leftGameButtons[2].setFillColor(Color::Red);
		}
		_leftGameButtons[0].setFillColor(Color::Blue);
		_leftGameButtons[1].setFillColor(Color::Blue);
	}
	else
	{
		if (_leftGameButtons[2].getFillColor() == Color::Red)
		{
			_leftGameButtons[2].setFillColor(Color{ 152, 59, 59 });

			_leader->updateString("");
			_nomPlanete->updateString("");
			_typePlanete->updateString("");
			_soldat->updateStats(0);
			_croissance->updateStats(0);
			_descriptionPlanete->updateString("");
		}
		else
		{
			_leftGameButtons[2].setFillColor(Color::Red);
		}
		_leftGameButtons[0].setFillColor(Color{ 152, 59, 59 });
		_leftGameButtons[1].setFillColor(Color{ 152, 59, 59 });
	}
	
}

void gameState::selectAttackButton()
{
	if (_noJoueur==1)
	{
		if (_leftGameButtons[1].getFillColor() == Color::Red)
		{
			_leftGameButtons[1].setFillColor(Color::Blue);
		}
		else
		{
			_leftGameButtons[1].setFillColor(Color::Red);
		}
		_leftGameButtons[0].setFillColor(Color::Blue);
		if (_leftGameButtons[2].getFillColor() == Color::Red)
		{
			_leftGameButtons[2].setFillColor(Color::Blue);
			_leader->updateString("");
			_nomPlanete->updateString("");
			_typePlanete->updateString("");
			_soldat->updateStats(0);
			_croissance->updateStats(0);
			_descriptionPlanete->updateString("");
			
		}
	}
	else
	{
		if (_leftGameButtons[1].getFillColor() == Color::Red)
		{
			_leftGameButtons[1].setFillColor(Color{ 152, 59, 59 });
		}
		else
		{
			_leftGameButtons[1].setFillColor(Color::Red);
		}
		_leftGameButtons[0].setFillColor(Color{ 152, 59, 59 });
		if (_leftGameButtons[2].getFillColor() == Color::Red)
		{
			_leftGameButtons[2].setFillColor(Color{ 152, 59, 59 });
			_leader->updateString("");
			_nomPlanete->updateString("");
			_typePlanete->updateString("");
			_soldat->updateStats(0);
			_croissance->updateStats(0);
			_descriptionPlanete->updateString("");
		}
	}
}

void gameState::initNewTurn()
{
	if (_noJoueur == 1)
	{
		_noJoueur = 2;
		_nbAction = 2;
		_nbTroupe = 0;
		_textAction->updateStats(_nbAction);
		_leftGameButtons[0].setFillColor(Color::Blue);
		_leftGameButtons[1].setFillColor(Color::Blue);
		_leftGameButtons[2].setFillColor(Color::Blue);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{

				if (_grill.at(i, j).getOutlineColor() == Color::White)
				{
					_grill.at(i, j).setOutlineColor(Color::Blue);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_grill.at(i, j).getOutlineColor() == Color::Red)
				{
					_nbTroupe += _planeteJeu.at(i, j)._planetes->_nbArmeeTour;
				}
			}
		}
	}
	else
	{
		_noJoueur = 1;
		_nbAction = 2;
		_nbTroupe = 0;
		_textAction->updateStats(_nbAction);
		_leftGameButtons[0].setFillColor(Color::Blue);
		_leftGameButtons[1].setFillColor(Color::Blue);
		_leftGameButtons[2].setFillColor(Color::Blue);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_grill.at(i, j).getOutlineColor() == Color::White)
				{
					_grill.at(i, j).setOutlineColor(Color::Red);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_grill.at(i, j).getOutlineColor() == Color::Blue)
				{
					_nbTroupe += _planeteJeu.at(i, j)._planetes->_nbArmeeTour;
				}
			}
		}
	}

	_textJoueur->updateStats(_noJoueur);
	_textTroupe->updateStats(_nbTroupe);
}

void gameState::endTheGame()
{
	string gagnant = "";

	int compteur = 0;

	if (_noJoueur == 1)
	{
		gagnant = "Joueur 2";


		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_grill.at(i, j).getOutlineColor() == Color::Red)
				{
					compteur += _planeteJeu.at(i, j).getNbArmee();
				}
			}
		}

	}
	else
	{
		gagnant = "Joueur 1";

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_grill.at(i, j).getOutlineColor() == Color::Blue)
				{
					compteur += _planeteJeu.at(i, j).getNbArmee();
				}
			}
		}
	}
	_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
	_data->machine.addState(stateRef(new gameOverState(_data, _soundActive, _gameTime, gagnant, compteur)), true);
	_soundHopeLounge.stop();
}

void gameState::returnToMenu()
{
	_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
	_data->machine.addState(stateRef(new mainMenuState(_data, _soundActive)), true);
	_soundHopeLounge.stop();
}

//gère le délai, après 3 secondes, on veut afficher la prochaine fenêtre
void gameState::update(float dt)
{	
	int compteurRouge = 0;
	int compteurBleu = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_grill.at(i, j).getOutlineColor() == Color::Blue|| (_noJoueur==1 && _grill.at(i, j).getOutlineColor() == Color::White))
			{
				compteurBleu += _planeteJeu.at(i, j).getNbArmee();
			}
			if (_grill.at(i, j).getOutlineColor() == Color::Red || (_noJoueur == 2 && _grill.at(i, j).getOutlineColor() == Color::White))
			{
				compteurRouge += _planeteJeu.at(i, j).getNbArmee();
			}
		}
	}

	if (compteurBleu == 0 || compteurRouge == 0)
	{
		string gagnant = "";
		_data->window.create(VideoMode(1600, 900), "Risk Spatial", Style::Close | Style::Titlebar);
		if (compteurBleu==0)
		{
			gagnant = "Joueur 2";
			_data->machine.addState(stateRef(new gameOverState(_data, _soundActive, _gameTime, gagnant, compteurRouge)), true);
		}
		else
		{
			gagnant = "Joueur 1";
			_data->machine.addState(stateRef(new gameOverState(_data, _soundActive, _gameTime, gagnant, compteurBleu)), true);
		}
		
		_soundHopeLounge.stop();
	}
}

void gameState::draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_description);
	_data->window.draw(_descriptionTitle);
	_data->window.draw(_endTurnButton);
	_data->window.draw(_endTurnText);
	for (int i = 0; i < _topMenuButtons.size(); i++)
	{
		_data->window.draw(_topMenuButtons[i]);
	}
	for (int i = 0; i < _topMenuTexts.size(); i++)
	{
		_data->window.draw(_topMenuTexts[i]);
	}
	for (int i = 0; i < _leftInfoButtons.size(); i++)
	{
		_data->window.draw(_leftInfoButtons[i]);
	}
	for (int i = 0; i < _leftInfoTexts.size(); i++)
	{
		_data->window.draw(_leftInfoTexts[i]);
	}
	for (int i = 0; i < _leftGameButtons.size(); i++)
	{
		_data->window.draw(_leftGameButtons[i]);
	}
	for (int i = 0; i < _leftGameTexts.size(); i++)
	{
		_data->window.draw(_leftGameTexts[i]);
	}
	for (int i = 0; i < _rightInfoButtons.size(); i++)
	{
		_data->window.draw(_rightInfoButtons[i]);
	}
	for (int i = 0; i < _rightInfoTexts.size(); i++)
	{
		_data->window.draw(_rightInfoTexts[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_data->window.draw(_grill.at(i,j));
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_data->window.draw(_planeteJeu.at(i, j)._planetes->_forme);
			_data->window.draw(_planeteJeu.at(i, j)._planetes->_nombreArmeeText);
		}
	}
	
	_leader->draw();
	_nomPlanete->draw();
	_typePlanete->draw();
	_soldat->draw();
	_croissance->draw();
	_descriptionPlanete->draw();

	_textJoueur->draw();
	_textAction->draw();
	_textTroupe->draw();
	_data->window.display();
}


void gameState::initPlanets(int& random)
{
	_planeteJeu.resize(NOMBRE_LIGNE_JEU, NOMBRE_COLONNE_JEU);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0 && j == 0)                      //si c'est la case en haut à gauche
			{
				_planeteJeu.at(i, j).init();

				it = _nomliste.begin();
				it++;

				_planeteJeu.at(i, j)._planetes->_nom = *it;
				cout << _planeteJeu.at(i, j)._planetes->_nom << " : ";

				it = _descPlanete.begin();
				it++;
				_planeteJeu.at(i, j)._planetes->_def = *it;
				cout << _planeteJeu.at(i, j)._planetes->_def << endl;

				_planeteJeu.at(i, j)._planetes->_forme.setFillColor(COULEUR_DE_COMMENCEMENT);
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 8;
				_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 3;
				_planeteJeu.at(i, j)._planetes->_typePlanete = "Temperée";

			}
			else if (i == 4 && j == 0)				//si c'est la case en bas à gauche
			{
				_planeteJeu.at(i, j).init();

				it = _nomliste.begin();
				it++;
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_nom = *it;
				cout << _planeteJeu.at(i, j)._planetes->_nom << " : ";

				it = _descPlanete.begin();
				it++;
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_def = *it;
				cout << _planeteJeu.at(i, j)._planetes->_def << endl;

				_planeteJeu.at(i, j)._planetes->_forme.setFillColor(COULEUR_DE_COMMENCEMENT);
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 3;
				_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 3;
				_planeteJeu.at(i, j).setArmeeText();
				_planeteJeu.at(i, j)._planetes->_typePlanete = "Temperée";
			}
			else if (i == 0 && j == 4)				//si c'est la case en haut à droite
			{
				_planeteJeu.at(i, j).init();

				it = _nomliste.begin();
				it++;
				it++;
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_nom = *it;
				cout << _planeteJeu.at(i, j)._planetes->_nom << " : ";

				it = _descPlanete.begin();
				it++;
				it++;
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_def = *it;
				cout << _planeteJeu.at(i, j)._planetes->_def << endl;

				_planeteJeu.at(i, j)._planetes->_forme.setFillColor(COULEUR_DE_COMMENCEMENT);
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 3;
				_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 3;
				_planeteJeu.at(i, j).setArmeeText();
				_planeteJeu.at(i, j)._planetes->_typePlanete = "Temperée";

			}
			else if (i == 4 && j == 4)				//si c'est la case en bas à droite
			{
				_planeteJeu.at(i, j).init();

				it = _nomliste.begin();
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_nom = *it;
				cout << _planeteJeu.at(i, j)._planetes->_nom << " : ";

				it = _descPlanete.begin();
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_def = *it;
				cout << _planeteJeu.at(i, j)._planetes->_def << endl;

				_planeteJeu.at(i, j)._planetes->_forme.setFillColor(COULEUR_DE_COMMENCEMENT);
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 8;
				_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 3;
				_planeteJeu.at(i, j).setArmeeText();
				_planeteJeu.at(i, j)._planetes->_typePlanete = "Temperée";
			}
			else if (i == 2 && j == 2)				//si la case est au milieu
			{
				_planeteJeu.at(i, j).init();

				it = _nomliste.begin();

				_planeteJeu.at(i, j)._planetes->_nom = *it;
				cout << _planeteJeu.at(i, j)._planetes->_nom << " : ";

				it = _descPlanete.begin();

				_planeteJeu.at(i, j)._planetes->_def = *it;
				cout << _planeteJeu.at(i, j)._planetes->_def << endl;

				_planeteJeu.at(i, j)._planetes->_forme.setFillColor(COULEUR_PLANETE_PARADISIAQUE);
				_planeteJeu.at(i, j)._planetes->_nombreArmee = 10;
				_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 6;
				_planeteJeu.at(i, j).setArmeeText();
				_planeteJeu.at(i, j)._planetes->_typePlanete = "Paradisiaque";
			}
			else									//si c'est une case de planète normale
			{
				_planeteJeu.at(i, j).init();

				it = _nomliste.begin();
				it++;
				it++;
				it++;
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_nom = *it;
				_nomliste.erase(it);
				cout << _planeteJeu.at(i, j)._planetes->_nom << " : ";

				it = _descPlanete.begin();
				it++;
				it++;
				it++;
				it++;
				it++;

				_planeteJeu.at(i, j)._planetes->_def = *it;
				_descPlanete.erase(it);
				cout << _planeteJeu.at(i, j)._planetes->_def << endl;

				random = rand() % 2 + 1;
				_planeteJeu.at(i, j)._planetes->_forme.setFillColor(_planeteJeu.at(i, j).getColor(random));

				if (random == 1)
				{
					_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 2;
					_planeteJeu.at(i, j)._planetes->_nombreArmee = 2;
					_planeteJeu.at(i, j)._planetes->_typePlanete = "Habitable";
				}
				else
				{
					_planeteJeu.at(i, j)._planetes->_nbArmeeTour = 1;
					_planeteJeu.at(i, j)._planetes->_nombreArmee = 0;
					_planeteJeu.at(i, j)._planetes->_typePlanete = "Hostile";
				}
				_planeteJeu.at(i, j).setArmeeText();

			}

			_planeteJeu.at(i, j).setArmeeText();
			_planeteJeu.at(i, j)._planetes->_forme.setOrigin(Vector2f(_planeteJeu.at(i, j)._planetes->_forme.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_forme.getGlobalBounds().height / 2));
			_planeteJeu.at(i, j)._planetes->_forme.setPosition(Vector2f(_grill.at(i, j).getPosition().x + (_grill.at(i, j).getGlobalBounds().width / 2), _grill.at(i, j).getPosition().y + (_grill.at(i, j).getGlobalBounds().height / 2)));
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setFont(_data->assets.getFont("Risk font"));
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setFillColor(Color::Black);
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setCharacterSize(20);
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setOrigin(_planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().width / 2, _planeteJeu.at(i, j)._planetes->_nombreArmeeText.getGlobalBounds().height / 2);
			_planeteJeu.at(i, j)._planetes->_nombreArmeeText.setPosition(_grill.at(i, j).getPosition().x + (_grill.at(i, j).getGlobalBounds().width / 2), _grill.at(i, j).getPosition().y + (_grill.at(i, j).getGlobalBounds().height / 2)-6);
		}
	}
}

void gameState::initGameButton(sf::RectangleShape& rectangle, sf::Text& text)
{
	for (int i = 0; i < 3; i++)
	{
		_leftGameButtons.push_back(rectangle);
	}

	for (int i = 0; i < _leftGameButtons.size(); i++)
	{
		_leftGameButtons[i].setSize(Vector2f(250, 60));
		_leftGameButtons[i].setPosition(0, 600 + 90 * i);
		_leftGameButtons[i].setFillColor(Color::Blue);
		_leftGameButtons[i].setOutlineThickness(2);
		_leftGameButtons[i].setOutlineColor(Color::White);
	}
	for (int i = 0; i < 3; i++)
	{
		_leftGameTexts.push_back(text);
	}
	_leftGameTexts[0].setString("DEPLACER\nTROUPES ");
	_leftGameTexts[1].setString("PRENDRE\nTERRITOIRE");
	_leftGameTexts[2].setString("PLACER TROUPES");
	for (int i = 0; i < _leftGameTexts.size(); i++)
	{
		_leftGameTexts[i].setFont(_data->assets.getFont("Risk font"));
		_leftGameTexts[i].setFillColor(Color::White);
		_leftGameTexts[i].setCharacterSize(20);
		_leftGameTexts[i].setOrigin(_leftGameTexts[i].getGlobalBounds().width / 2, _leftGameTexts[i].getGlobalBounds().height / 2);
		_leftGameTexts[i].setPosition(_leftGameButtons[i].getPosition().x + (_leftGameButtons[i].getGlobalBounds().width / 2), _leftGameButtons[i].getPosition().y + 20);
	}
}

void gameState::initRightInfo(sf::RectangleShape& rectangle, sf::Text& text)
{

	for (int i = 0; i < 5; i++)
	{
		_rightInfoButtons.push_back(rectangle);
	}

	for (int i = 0; i < _rightInfoButtons.size(); i++)
	{
		_rightInfoButtons[i].setSize(Vector2f(250, 60));
		_rightInfoButtons[i].setPosition(1350, 120 + 90 * i);
		_rightInfoButtons[i].setFillColor(Color::Blue);
		_rightInfoButtons[i].setOutlineThickness(2);
		_rightInfoButtons[i].setOutlineColor(Color::White);
	}

	for (int i = 0; i < 5; i++)
	{
		_rightInfoTexts.push_back(text);
	}
	_rightInfoTexts[0].setString("LEADER :");
	_rightInfoTexts[1].setString("NOM :");
	_rightInfoTexts[2].setString("TYPE :");
	_rightInfoTexts[4].setString("CROISSANCE :");
	_rightInfoTexts[3].setString("UNITES :");

	for (int i = 0; i < _rightInfoTexts.size(); i++)
	{
		_rightInfoTexts[i].setFont(_data->assets.getFont("Risk font"));
		_rightInfoTexts[i].setFillColor(Color::White);
		_rightInfoTexts[i].setCharacterSize(20);
		_rightInfoTexts[i].setOrigin(_rightInfoTexts[i].getGlobalBounds().width / 2, _rightInfoTexts[i].getGlobalBounds().height / 2);
		_rightInfoTexts[i].setPosition(_rightInfoButtons[i].getPosition().x + (_rightInfoButtons[i].getGlobalBounds().width / 2), _rightInfoButtons[i].getPosition().y + 17);
	}
	_leader = new hud(_data);
	_leader->setPosition(_rightInfoTexts[0].getPosition().x - 35, _rightInfoTexts[0].getPosition().y + 15);

	_nomPlanete = new hud(_data);
	_nomPlanete->setPosition(_rightInfoTexts[1].getPosition().x - 35, _rightInfoTexts[1].getPosition().y + 15);

	_typePlanete = new hud(_data);
	_typePlanete->setPosition(_rightInfoTexts[2].getPosition().x - 45, _rightInfoTexts[2].getPosition().y + 15);

	_soldat = new hud(_data);
	_soldat->setPosition(_rightInfoTexts[3].getPosition().x + _rightInfoTexts[3].getGlobalBounds().width / 2 + 6, _rightInfoTexts[3].getPosition().y - 6);

	_croissance = new hud(_data);
	_croissance->setPosition(_rightInfoTexts[4].getPosition().x + _rightInfoTexts[4].getGlobalBounds().width / 2 + 6, _rightInfoTexts[4].getPosition().y - 6);
}

void gameState::initPlayerInfo(sf::RectangleShape& rectangle, sf::Text& text)
{
	for (int i = 0; i < 3; i++)
	{
		_leftInfoButtons.push_back(rectangle);
	}

	for (int i = 0; i < _leftInfoButtons.size(); i++)
	{
		_leftInfoButtons[i].setSize(Vector2f(250, 60));
		_leftInfoButtons[i].setPosition(0, 120 + 90 * i);
		_leftInfoButtons[i].setFillColor(Color::Blue);
		_leftInfoButtons[i].setOutlineThickness(2);
		_leftInfoButtons[i].setOutlineColor(Color::White);
	}
	for (int i = 0; i < 3; i++)
	{
		_leftInfoTexts.push_back(text);
	}
	_leftInfoTexts[0].setString("JOUEUR : ");
	_leftInfoTexts[1].setString("ACTIONS : ");
	_leftInfoTexts[2].setString("TROUPES : ");
	for (int i = 0; i < _topMenuTexts.size(); i++)
	{
		_leftInfoTexts[i].setFont(_data->assets.getFont("Risk font"));
		_leftInfoTexts[i].setFillColor(Color::White);
		_leftInfoTexts[i].setCharacterSize(20);
		_leftInfoTexts[i].setOrigin(_leftInfoTexts[i].getGlobalBounds().width / 2, _leftInfoTexts[i].getGlobalBounds().height / 2);
		_leftInfoTexts[i].setPosition(_leftInfoButtons[i].getPosition().x + (_leftInfoButtons[i].getGlobalBounds().width / 2), _leftInfoButtons[i].getPosition().y + 17);
	}

	_textJoueur = new hud(_data);
	_textJoueur->updateStats(_noJoueur);
	_textJoueur->setPosition(_leftInfoTexts[0].getPosition().x + _leftInfoTexts[0].getGlobalBounds().width / 2, _leftInfoTexts[0].getPosition().y - 6);

	_textAction = new hud(_data);
	_textAction->updateStats(_nbAction);
	_textAction->setPosition(_leftInfoTexts[1].getPosition().x + _leftInfoTexts[1].getGlobalBounds().width / 2, _leftInfoTexts[1].getPosition().y - 6);

	_textTroupe = new hud(_data);
	_textTroupe->updateStats(_nbTroupe);
	_textTroupe->setPosition(_leftInfoTexts[2].getPosition().x + _leftInfoTexts[2].getGlobalBounds().width / 2, _leftInfoTexts[2].getPosition().y - 6);
}

void gameState::initTopMenu(sf::RectangleShape& rectangle, sf::Text& text)
{
	for (int i = 0; i < 3; i++)
	{
		_topMenuButtons.push_back(rectangle);
	}

	for (int i = 0; i < _topMenuButtons.size(); i++)
	{
		_topMenuButtons[i].setSize(Vector2f(300, 60));
		_topMenuButtons[i].setPosition(330 + 320 * i, 20);
		_topMenuButtons[i].setFillColor(Color::Blue);
		_topMenuButtons[i].setOutlineThickness(2);
		_topMenuButtons[i].setOutlineColor(Color::White);
	}
	for (int i = 0; i < 3; i++)
	{
		_topMenuTexts.push_back(text);
	}
	_topMenuTexts[0].setString("MENU");
	_topMenuTexts[1].setString("ABANDONNER");
	_topMenuTexts[2].setString("QUITTER");
	for (int i = 0; i < _topMenuTexts.size(); i++)
	{
		_topMenuTexts[i].setFont(_data->assets.getFont("Risk font"));
		_topMenuTexts[i].setFillColor(Color::White);
		_topMenuTexts[i].setCharacterSize(30);
		_topMenuTexts[i].setOrigin(_topMenuTexts[i].getGlobalBounds().width / 2, _topMenuTexts[i].getGlobalBounds().height / 2);
		_topMenuTexts[i].setPosition(_topMenuButtons[i].getPosition().x + (_topMenuButtons[i].getGlobalBounds().width / 2), _topMenuButtons[i].getPosition().y + 17);
	}
}

void gameState::initGrill()
{
	_grill.resize(5, 5);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_grill.at(i, j).setSize(Vector2f(80, 80));
			_grill.at(i, j).setPosition(Vector2f(590 + (i * 80), 250 + (j * 80)));
			_grill.at(i, j).setFillColor(Color::Transparent);
			_grill.at(i, j).setOutlineThickness(-4);

			if (i == 0 && j == 0)
			{
				_grill.at(i, j).setOutlineColor(Color::Blue);
			}
			else if (i == 4 && j == 4)
			{
				_grill.at(i, j).setOutlineColor(Color::Red);
			}
			else
			{
				_grill.at(i, j).setOutlineColor(Color::Transparent);
			}
		}
	}
}

void gameState::initEndTurnButton()
{
	_endTurnButton.setSize(Vector2f(300, 60));
	_endTurnButton.setPosition(Vector2f(650, 840));
	_endTurnButton.setFillColor(Color::Blue);
	_endTurnButton.setOutlineThickness(2);
	_endTurnButton.setOutlineColor(Color::White);


	_endTurnText.setString("FIN DE TOUR");
	_endTurnText.setFont(_data->assets.getFont("Risk font"));
	_endTurnText.setFillColor(Color::White);
	_endTurnText.setCharacterSize(30);
	_endTurnText.setOrigin(_endTurnText.getGlobalBounds().width / 2, _endTurnText.getGlobalBounds().height / 2);
	_endTurnText.setPosition(_endTurnButton.getPosition().x + (_endTurnButton.getGlobalBounds().width / 2), _endTurnButton.getPosition().y + 20);
}

void gameState::initDescription()
{
	_description.setSize(Vector2f(250, 220));
	_description.setPosition(Vector2f(1350, 680));
	_description.setFillColor(Color::Blue);
	_description.setOutlineThickness(2);
	_description.setOutlineColor(Color::White);

	_descriptionTitle.setString("DESCRIPTION");
	_descriptionTitle.setFont(_data->assets.getFont("Risk font"));
	_descriptionTitle.setFillColor(Color::White);
	_descriptionTitle.setCharacterSize(20);
	_descriptionTitle.setOrigin(_descriptionTitle.getGlobalBounds().width / 2, _descriptionTitle.getGlobalBounds().height / 2);
	_descriptionTitle.setPosition(_description.getPosition().x + (_description.getGlobalBounds().width / 2), _description.getPosition().y);

	_descriptionPlanete = new hud(_data);
	_descriptionPlanete->setPosition(_description.getPosition().x, _description.getPosition().y + 15);
}

void gameState::initBackground()
{
	_data->assets.loadTexture("background", GAME_BACKGROUND_FILE_PATH);
	_background.setTexture(_data->assets.getTexture("background"));

	_background.setScale(1.5625, 1.5625);
}

void gameState::initSound()
{
	if (!_soundHopeLoungeBuffer.loadFromFile(SOUND_HOPE_LOUNGE_FILEPATH)) {
		cout << "erreur loading sound effect" << endl;
	}
	if (!_soundDeesBuffer.loadFromFile(SOUND_DEES_FILEPATH)) {
		cout << "erreur loading sound effect" << endl;
	}
	if (!_soundExplosionBuffer.loadFromFile(SOUND_EXPLOSION_FILEPATH)) {
		cout << "erreur loading sound effect" << endl;
	}
	if (_soundActive) {

		_soundHopeLounge.setLoop(true);
		_soundHopeLounge.setVolume(50);
		_soundHopeLounge.play();

	}

	_soundDees.setBuffer(_soundDeesBuffer);
	_soundExplosion.setBuffer(_soundExplosionBuffer);
	_soundHopeLounge.setBuffer(_soundHopeLoungeBuffer);

	if (_soundActive)
	{
		_soundHopeLounge.play();
	}
}

void gameState::initPlanetNameList()
{
	it = _nomliste.begin();
	it = _nomliste.insert(it, "Paradise");
	it = _nomliste.insert(it, "Alpha");
	it = _nomliste.insert(it, "Beta");
	it = _nomliste.insert(it, "Gamma");
	it = _nomliste.insert(it, "Delta");
	it = _nomliste.insert(it, "Epsilon");
	it = _nomliste.insert(it, "Zeta");
	it = _nomliste.insert(it, "Eta");
	it = _nomliste.insert(it, "Pheta");
	it = _nomliste.insert(it, "Iota");
	it = _nomliste.insert(it, "Kappa");
	it = _nomliste.insert(it, "Lambda");
	it = _nomliste.insert(it, "Mu");
	it = _nomliste.insert(it, "Nu");
	it = _nomliste.insert(it, "Ksi");
	it = _nomliste.insert(it, "Omicron");
	it = _nomliste.insert(it, "Pi");
	it = _nomliste.insert(it, "Rho");
	it = _nomliste.insert(it, "Sigma");
	it = _nomliste.insert(it, "Tau");
	it = _nomliste.insert(it, "Upsilon");
	it = _nomliste.insert(it, "Phi");
	it = _nomliste.insert(it, "Ki");
	it = _nomliste.insert(it, "Psy");
	it = _nomliste.insert(it, "Omega");
}

void gameState::initDescList()
{
	it = _descPlanete.begin();
	it = _descPlanete.insert(it, "Cette planete est \n remplie de\n ressource\net de vie");
	it = _descPlanete.insert(it, "Planete d'origine\ndes Bleuesiens");
	it = _descPlanete.insert(it, "Planete d'origine\ndes Rougois");
	it = _descPlanete.insert(it, "Planete avec une\ntempérature \nparfaite\noubliee de tous");
	it = _descPlanete.insert(it, "Planete avec une\ntempérature \nparfaite\noubliee de tous");
	it = _descPlanete.insert(it, "Planete glaciaire");
	it = _descPlanete.insert(it, "Planete volcanique");
	it = _descPlanete.insert(it, "Planete desertique");
	it = _descPlanete.insert(it, "Planete forestiere");
	it = _descPlanete.insert(it, "Planete pleine de\nmouches");
	it = _descPlanete.insert(it, "Personnellement,\nje n'y ai\njamais ete");
	it = _descPlanete.insert(it, "Planete avec de \nvieille ruine");
	it = _descPlanete.insert(it, "Planete de beton");
	it = _descPlanete.insert(it, "Planete de marais");
	it = _descPlanete.insert(it, "Planete avec des\n rivieres\n de lave");
	it = _descPlanete.insert(it, "Planete \nmontagneuse");
	it = _descPlanete.insert(it, "Planete oceanique");
	it = _descPlanete.insert(it, "Planete fongique");
	it = _descPlanete.insert(it, "Planete medicinale");
	it = _descPlanete.insert(it, "Planete gazeuse");
	it = _descPlanete.insert(it, "Planete forestiere");
	it = _descPlanete.insert(it, "Planete \nmontagneuse");
	it = _descPlanete.insert(it, "Planete desertique");
	it = _descPlanete.insert(it, "Planete de marais");
	it = _descPlanete.insert(it, "Planete de marais");
}