/*
* =============================================
* Auteur: Gilles Sinotte
* Laboratoire: Projet finale
* Nom du fichier: liste.hpp
* Date: 2021-12-18
* But: Liste explicite.
* =============================================
*/

#pragma once

#include <assert.h>
template <typename TYPE> class liste;

//CLASSE CELLULE
template <typename TYPE>
class cellule
{
	friend class liste<TYPE>;	//la seule classe ayant accès à la  représentation de la cellule

	TYPE _element;			//Contenu de la cellule
	cellule <TYPE>* _next;		//Pointeur vers la cellule suivante 
	cellule <TYPE>* _prev;	//Pointeur vers la cellule precedente

	cellule(const TYPE& e, cellule<TYPE>* n = nullptr, cellule<TYPE>* p = nullptr)
	{
		_element = e;
		_next = n;
		_prev = p;
	}
};


//CLASSE LISTE
template <typename TYPE>
class liste
{
private:
	cellule <TYPE>* _first;			//Adresse du premier élément 

	liste(const liste<TYPE>& l);		//Copieur désactivé
public:
	//CLASSE Iterator
	class Iterator
	{
		friend class liste<TYPE>;
	private:
		cellule<TYPE>* _current;		//adresse de la cellule
		const liste<TYPE>* _list;		//adresse de la liste
	public:
		Iterator();					//constructeurs
		~Iterator();				//destructeur

		const Iterator& operator=(const Iterator& I);//pour j=i

		bool operator==(const Iterator& I)const; //pour if(j==i)
		bool operator!=(const Iterator& I)const; //pour if(j!=i)

		Iterator operator++(int);			//i++
		const Iterator& operator++();		//++i

		Iterator operator--(int);			//i--
		const Iterator& operator--();		//--i

		TYPE& operator*();				//accès à un élément
		const TYPE& operator*()const;		//idem, en mode const

	};
	//construct
	liste(void);
	//destruct
	~liste(void);

	void clear();							//supprime la liste
	bool empty()const;						//verifie si la liste est vide

	Iterator begin()const;			//return premier
	Iterator end()const;				//return nullptr

	Iterator insert(Iterator I, const TYPE& e);				//insert un élément a cette endroit
	Iterator erase(Iterator I);								//efface un élément a cette endroit
	Iterator erase(Iterator first, Iterator last);			//efface d'un element a un autre

	TYPE& operator[](Iterator I);							//recupere l'element a l'iterateur donné
	const TYPE& operator[](Iterator I)const;

	//et à partir de l’itérateur reçu pour la version 2
	//la méthode  retourne un Iterator sur l’element trouvé
	//s’il est innexistant, l’Iterator est à la fin 
	Iterator operator()(const TYPE&)const;					//place l'iterateur vers un element
	Iterator operator()(const TYPE&, Iterator)const;

	const liste<TYPE>& operator=(const liste<TYPE>& l);		//donne les données d'une liste vers une autre
};

template<typename TYPE>
liste<TYPE>::Iterator::Iterator()
{
	_current = nullptr;
	_list = nullptr;

}

template<typename TYPE>
liste<TYPE>::Iterator::~Iterator()
{
	_current = nullptr;
	_list = nullptr;

}

template<typename TYPE>
const typename liste<TYPE>::Iterator& liste<TYPE>::Iterator::operator=(const typename liste<TYPE>::Iterator& I)
{
	_current = I._current;
	_list = I._list;

	return *this;
}

template<typename TYPE>
bool liste<TYPE>::Iterator::operator==(const typename liste<TYPE>::Iterator& it) const
{
	assert(_list == it._list);
	assert(_list != nullptr);

	return(_current == it._current);
}

template<typename TYPE>
bool liste<TYPE>::Iterator::operator!=(const typename liste<TYPE>::Iterator& it) const
{
	return !this->operator==(it);
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::Iterator::operator++(int)
{
	liste<TYPE>::Iterator it = *this;

	this->operator++();

	return it;
}

template<typename TYPE>
const typename liste<TYPE>::Iterator& liste<TYPE>::Iterator::operator++()
{
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(_list->_first != nullptr);

	if (_current == _list->_first->_prev)  //si current est à la fin previous de first c'est la fin
		_current = nullptr;					// pointe dans le vide attendant une valeur
	else
		_current = _current->_next;			//sinon, il point a l'iterateur suivant

	return *this;
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::Iterator::operator--(int)
{
	liste<TYPE>::Iterator it = *this;

	this->operator--();

	return it;
}

template<typename TYPE>
const typename liste<TYPE>::Iterator& liste<TYPE>::Iterator::operator--()
{
	assert(_list != nullptr);
	assert(_list->_first != nullptr);

	if (_current == nullptr)
		_current = _list->_first->_prev;   //si current est vide donc apres la fin avec end, il pointe vers le dernier iterateur avec un element
	else
		_current = _current->_prev;			//sinon il pointe vers l'iterateur precedent

	return *this;
}

template<typename TYPE>
TYPE& liste<TYPE>::Iterator::operator*()
{
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(_list->_first != nullptr);

	return _current->_element;
}

template<typename TYPE>
const TYPE& liste<TYPE>::Iterator::operator*()const
{
	return this->operator*();
}

template<typename TYPE>
inline liste<TYPE>::liste(void)
{
	_first = nullptr;
}

template<typename TYPE>
inline liste<TYPE>::~liste(void)
{
	this->clear();
}

template<typename TYPE>
inline void liste<TYPE>::clear()
{
	this->erase(this->begin(), this->end());
}

template<typename TYPE>
inline bool liste<TYPE>::empty() const
{
	return _first == nullptr;
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::begin() const
{
	liste<TYPE>::Iterator it;

	it._current = _first;
	it._list = this;

	return it;
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::end() const
{
	liste<TYPE>::Iterator it;

	it._current = nullptr;
	it._list = this;

	return it;
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::insert(typename liste<TYPE>::Iterator it, const TYPE& element)
{
	assert(this == it._list);

	if (!_first)    
		it._current = _first->_prev = _first = new cellule<TYPE>(element, nullptr, nullptr);

	else if (_first == it._current)  
		it._current = _first = _first->_prev = new cellule<TYPE>(element, _first, _first->_prev);

	else if (!it._current)      //si la l'iterateur est à end
		it._current = _first->_prev = _first->_prev->_next = new cellule<TYPE>(element, nullptr, _first->_prev);

	else
		it._current = it._current->_prev = it._current->_prev->_next = new cellule<TYPE>(element, it._current, it._current->_prev);

	it++;
	return it;
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::erase(typename liste<TYPE>::Iterator it)
{
	assert((this == it._list) && (it._current != nullptr) && (_first != nullptr));

	cellule<TYPE>* deleteCell = it._current;

	if (!_first->_next)
		_first = it._current = nullptr;

	else if (_first == it._current) {
		_first->_next->_prev = _first->_prev;
		_first = it._current = _first->_next;
	}
	else if (_first->_prev == it._current) {
		_first->_prev->_prev->_next = nullptr;
		_first->_prev = it._current = _first->_prev->_prev;
	}

	else {
		it._current->_next->_prev = it._current->_prev;
		it._current = it._current->_prev->_next = it._current->_next;
	}

	delete deleteCell;

	return it;

}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::erase(typename liste<TYPE>::Iterator it_first, typename liste<TYPE>::Iterator it_last)
{
	assert((this == it_first._list) && (it_first._list != nullptr));
	assert((this == it_last._list) && (it_last._list != nullptr));

	while ((it_first != it_last) && (it_first != this->end()))
		it_first = this->erase(it_first);

	return it_first;
}

template<typename TYPE>
inline TYPE& liste<TYPE>::operator[](typename liste<TYPE>::Iterator it)
{
	assert((this == it._list) && (it._list != nullptr));
	return *it;
}

template<typename TYPE>
inline const TYPE& liste<TYPE>::operator[](typename liste<TYPE>::Iterator it) const
{
	assert((this == it._list) && (it._list != nullptr));
	return *it;
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::operator()(const TYPE& element) const
{
	return this->operator()(element, this->begin());
}

template<typename TYPE>
typename liste<TYPE>::Iterator liste<TYPE>::operator()(const TYPE& element, typename liste<TYPE>::Iterator it) const
{
	assert(this == it._list);

	while ((it != this->end()) && (*it != element))
		it++;
	return it;
}

template<typename TYPE>
const typename liste<TYPE>& liste<TYPE>::operator=(const typename liste<TYPE>& l)
{
	Iterator it;
	it = l.begin();

	if (this == it._list)
	{
		return *this;
	}

	if (l.empty())
	{
		clear();
		return *this;
	}
	for (it = l.begin(); it != l.end(); it++)
	{
		if (!_first)
			it._current = _first->_prev = _first = new cellule<TYPE>(*it, nullptr, nullptr);

		else if (_first == it._current)
			it._current = _first = _first->_prev = new cellule<TYPE>(*it, _first, _first->_prev);

		else if (!it._current)
			it._current = _first->_prev = _first->_prev->_next = new cellule<TYPE>(*it, nullptr, _first->_prev);

		else
			it._current = it._current->_prev = it._current->_prev->_next = new cellule<TYPE>(*it, it._current, it._current->_prev);
	}

	return *this;
}




