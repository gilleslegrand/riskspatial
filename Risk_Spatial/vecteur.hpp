/****************************************************************************************
Auteur: Étienne Germain
Laboratoire: laboratoire 2
Nom du fichier: vecteur.hpp
Date: 2021-09-03
But: Object vecteur. Ce .hpp permet de faire une copie de l'objet vector pour un apprentissage sur la gestion de mémoire dynamique.
*****************************************************************************************/

#pragma once																	//Permet de ne pas instancier 
//une librairie qui a déjà été instanciée.
#include<iostream>																//Permet d'utiliser les cin et cout
#include<cassert>																//Permet d'utiliser les assert
#include<ostream>																//Permet d'utiliser ostream et istream
using namespace std;															//Permet d'utiliser la façon standard

template<class TYPE>															//Le mot TYPE sera utilisé pour remplacer 
																				//un int et généraliser
class vecteur
{
private:
	TYPE* _tab;																//pointeur sur le vecteur d'entier
	int _dim;																//dimension du vecteur
public:
	vecteur();																//constructeur sans paramètre... 
																			//Attention un pointeur ne peut rester non initialisé
	vecteur(int dim);														//construit le vecteur à la dimension de dim
	~vecteur();																//destructeur essentiel avec l'allocation dynamique.
																			//Attention, un pointeur ne peut conserver 
																			//l'adresse d'un espace mémoire désalouée.

	vecteur(const vecteur<TYPE>& vecObjet);									//Constructeur de copie

	void print(ostream& exit)const;											//Permet d'afficher les vecteurs

	void push_back(TYPE nb);												//Permet d'ajouter une valeur à la fin d'un vecteur
	void resize(int nb);													//Permet de modifier la grandeur du vecteur.

	int size();																//Permet de retourné la taille

	void clear();															//Permet d'effacer les nombres 
																			//en mémoire ainsi que le pointeur.

	TYPE& at(int nb);														//Permet de retourner le nombre à l'indice nombre
	TYPE& operator[](int nb);												//Permet de retourner le nombre à l'indice nombre

	const vecteur<TYPE>& operator=(const vecteur<TYPE>& vecteurObject);		//Permet d'affecter un vecteur à un autre
	const bool operator==(const vecteur<TYPE>& vecteurObjet);				//Permet de comparer si deux vecteur sont pareils
	vecteur<TYPE> operator+(const vecteur<TYPE>& vecteurObject)const;		//Permet d'additionner des vecteurs ensemble
	const vecteur<TYPE>& operator+=(const vecteur<TYPE>& vecteurObject);	//Permet d'incrémenter un vecteur dans un autre

	const vecteur<TYPE>& swap(vecteur<TYPE>& vecteurObject);				//Permet d'interchanger des vecteurs

	template<class T>
	friend void swap(vecteur<T>& vecteur1, vecteur<T>& vecteur2);			//Permet d'interchanger les vecteurs

	void reverse();															//Permet de changer les valeurs de place 
																			//dans un seul vecteur
	void reverseRecursive(int i = 0);										//Permet de changer les valeurs de place 
																			//dans un seul vecteur

};
template<class TYPE>
ostream& operator<<(ostream& exit, const vecteur<TYPE>& vecObjet);				//Permet d'afficher les vecteurs



//Le cpp

template<class TYPE>
vecteur<TYPE>::vecteur() {
	_tab = nullptr;
	_dim = 0;
}

template<class TYPE>
vecteur<TYPE>::vecteur(int dim) {
	assert(dim >= 0);
	if (dim == 0) {
		_tab = nullptr;
		_dim = 0;
	}
	else {
		_tab = new TYPE[dim];
		_dim = dim;
	}
}

template<class TYPE>
vecteur<TYPE>::~vecteur() {
	clear();
}

template<class TYPE>
vecteur<TYPE>::vecteur(const vecteur<TYPE>& vecObjet) {
	if (vecObjet._dim == 0) {
		_tab = nullptr;
		_dim = 0;
	}
	else {
		_tab = new TYPE[vecObjet._dim];
		_dim = vecObjet._dim;
		for (int i = 0; i < _dim; i++)
		{
			*(_tab + i) = *(vecObjet._tab + i);
		}
	}
}

template<class TYPE>
void vecteur<TYPE>::print(ostream& exit)const {
	for (int i = 0; i < _dim; i++)
	{
		exit << *(_tab + i) << " ";
	}
}

template<class TYPE>
ostream& operator<<(ostream& exit, const vecteur<TYPE>& vecObjet) {
	vecObjet.print(exit);

	return exit;
}

template<class TYPE>
void vecteur<TYPE>::push_back(TYPE nb) {
	TYPE* newTab = new TYPE[1 + _dim];
	for (int i = 0; i < _dim; i++)
	{
		*(newTab + i) = *(_tab + i);
	}
	*(newTab + _dim) = nb;
	delete[]_tab;
	_tab = newTab;
	_dim++;
}

template<class TYPE>
int vecteur<TYPE>::size() {
	return _dim;
}

template<class TYPE>
void vecteur<TYPE>::resize(int nb) {
	assert(nb >= 0);

	if (nb == _dim) {
		return;
	}
	else {

		TYPE* newTab = new TYPE[nb];

		for (int i = 0; (i < _dim) && (i < nb); i++)
		{
			*(newTab + i) = *(_tab + i);
		}

		delete[]_tab;
		_tab = newTab;
		_dim = nb;
	}

}

template<class TYPE>
void vecteur<TYPE>::clear() {
	delete[]_tab;
	_tab = nullptr;
	_dim = 0;
}

template<class TYPE>
TYPE& vecteur<TYPE>::at(int nb) {
	assert(nb >= 0 && nb < (_dim));
	return *(_tab + nb);
}

template<class TYPE>
TYPE& vecteur<TYPE>::operator[](int nb) {
	return at(nb);
}

template<class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator=(const vecteur<TYPE>& vecteurObject) {
	if (this != &vecteurObject) {
		this->clear();

		_dim = vecteurObject._dim;


		if (_dim > 0) {
			_tab = new TYPE[_dim];
			for (int i = 0; i < _dim; i++)
			{
				*(_tab + i) = *(vecteurObject._tab + i);
			}
		}
	}

	return *this;

}

template<class TYPE>
const bool vecteur<TYPE>::operator==(const vecteur<TYPE>& vecteurObjet) {
	if (this->_dim == vecteurObjet._dim) {
		for (int i = 0; i < _dim; i++)
		{
			if (this->_tab[i] != vecteurObjet._tab[i]) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

template<class TYPE>
vecteur<TYPE> vecteur<TYPE>::operator+(const vecteur<TYPE>& vecteurObject)const {
	int dim = _dim + vecteurObject._dim;
	vecteur<TYPE> vec(dim);

	for (int i = 0; i < dim; i++)
	{
		if (i < _dim) {
			*(vec._tab + i) = *(_tab + i);
		}
		else {
			*(vec._tab + i) = *(vecteurObject._tab + (i - _dim));
		}
	}
	return vec;
}

template<class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator+=(const vecteur<TYPE>& vecteurObject) {
	*this = operator+(vecteurObject);
	return *this;
}

template<class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::swap(vecteur<TYPE>& vecteurObject) {
	int dim = _dim;
	TYPE* tab = _tab;

	_dim = vecteurObject._dim;
	_tab = vecteurObject._tab;

	vecteurObject._dim = dim;
	vecteurObject._tab = tab;

	return *this;
}

template<class TYPE>
void swap(vecteur<TYPE>& vecteur1, vecteur<TYPE>& vecteur2) {
	vecteur1.swap(vecteur2);
}

template<class TYPE>
void vecteur<TYPE>::reverse() {
	int dim = _dim / 2;
	TYPE temp;

	for (int i = 0; i < dim; i++)
	{
		temp = *(_tab + i);
		*(_tab + i) = *(_tab + (_dim - 1) - i);
		*(_tab + (_dim - 1) - i) = temp;
	}
}

template<class TYPE>
void vecteur<TYPE>::reverseRecursive(int i) {
	assert(i >= 0);
	if (i < _dim / 2) {

		TYPE temp;

		temp = *(_tab + i);
		*(_tab + i) = *(_tab + (_dim - 1) - i);
		*(_tab + (_dim - 1) - i) = temp;

		reverseRecursive(i + 1);
	}
}





