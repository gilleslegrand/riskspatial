/*
* =============================================
* Auteur: Gilles Sinotte
* Laboratoire: Projet finale
* Nom du fichier: mapGilles.hpp
* Date: 2021-12-18
* But: Objet Map
* =============================================
*/
#pragma once
#include <assert.h>
#include <string.h>
#include <new>
#include <fstream>

using namespace std;

template<class TYPE>
class mappe
{

private:
	int _row;
	int _col;
	char* _nom;
	TYPE** _map;

public:
	//constructeurs
	mappe();
	mappe(const char* name, int line, int col);
	mappe(const char* name, int line, int col, TYPE** _map);

	//desctructeur
	~mappe();

	void clear();																		//efface la mappe
	void clearMap();																	
	void clearName();

	const char* getName()const;															//retourne le nom de la mappe
	int getLine()const;																	//retourne le nombre de ligne
	int getCol()const;																	//retourne le nombre de colonne

	void setName(const char* name);														//donne un nom
	void resize(int line, int col);														//donne la taille de la mappe

	TYPE& at(int posI, int posJ)const;													//retourne la donnee a la coordonnée donnée

	void print(ostream& out)const;														//affiche le contenu de la mappe

	void read(istream& entree);															//lit les donnés de la mappe

	void readFile(mappe<TYPE>& mapLue, const char* nomFichier);							//lit un fichier contenant une mappe
};

template<class TYPE>
ostream& operator<<(ostream& out, const mappe<TYPE>& m);
template<class TYPE>
ostream& operator>>(istream& in, const mappe<TYPE>& m);


template<class TYPE>
mappe<TYPE>::mappe()
{
	_row=0;
	_col=0;
	_nom=nullptr;
	_map=nullptr;
}

template<class TYPE>
mappe<TYPE>::mappe(const char* name, int line, int col)
{
	assert(line >= 0 && col >= 0);
	assert(name != "");

	_nom = new char[strlen(name)+1];

	_row = line;
	_col = col;
	_map = new TYPE * [line];

	for (int i = 0; i < line; i++)
	{
		*(_map + i) = new TYPE[col];
	}

	for (int i = 0; i < strlen(name)+1; i++)
	{
		*(_nom + i) = *(name + i);
	}
}

template<class TYPE>
inline mappe<TYPE>::mappe(const char* name, int line, int col, TYPE** _map)
{
	assert(line >= 0 && col >= 0);
	assert(name != "");

	_nom = new char[strlen(name) + 1];

	_row = line;
	_col = col;
	_map = new TYPE * [line];

	for (int i = 0; i < line; i++)
	{
		*(_map + i) = new TYPE[col];
	}

	for (int i = 0; i < strlen(name) + 1; i++)
	{
		*(_nom + i) = *(name + i);
	}
	for (int i = 0; i < _row; i++)
	{

	}
}

template<class TYPE>
mappe<TYPE>::~mappe()
{
	clear();
}

template<class TYPE>
void mappe<TYPE>::clear()
{
	delete[] _nom;
	for (int i = 0; i < _row; i++)
	{
		delete[] *(_map + i);
	}

	delete[] _map;
	_nom = nullptr;
	_map = nullptr;
	_row = 0;
	_col = 0;
}

template<class TYPE>
void mappe<TYPE>::clearMap()
{
	for (int i = 0; i < _row; i++)
	{
		delete[] * (_map + i);
	}
	delete[] _map;
	_map = nullptr;
	_row = 0;
	_col = 0;
}

template<class TYPE>
void mappe<TYPE>::clearName()
{ 
	delete[] _nom;
	_nom = nullptr;
}

template<class TYPE>
const char* mappe<TYPE>::getName()const
{
	assert(_nom != "" && _nom != NULL);
	return _nom;
}

template<class TYPE>
inline int mappe<TYPE>::getLine()const
{
	return _row;
}

template<class TYPE>
inline int mappe<TYPE>::getCol()const
{
	return _col;
}

template<class TYPE>
inline void mappe<TYPE>::setName(const char* name)
{
	assert(name != "");
	_nom = new char[strlen(name) + 1];
	for (int i = 0; i < strlen(name) + 1; i++)
	{
		*(_nom + i) = *(name + i);
	}
}

template<class TYPE>
inline void mappe<TYPE>::resize(int line, int col)
{
	assert(line >= 0 && col >= 0);

	if (line==0||col==0)
	{
		clearMap();
	}

	if (line==_row && col==_col)
	{
		return;
	}

	TYPE** tempMap = new TYPE*[line];
	for (int i = 0; i < line; i++)
	{
		*(tempMap+i) = new TYPE[col];
	}
	
	for (int i = 0; i < _row && i < line; i++)
	{
		for (int j = 0; j < _col && j < col; j++) 
		{
			*(*(tempMap + i) + j) = *(*(_map + i) + j);
		}
	}

	
	clearMap();
	_map = tempMap;
	for (int i = 0; i < line; i++)
	{
		*(_map + i) = *(tempMap + i);
	}
	_row = line;
	_col = col;

}

template<class TYPE>
inline TYPE& mappe<TYPE>::at(int posI, int posJ) const
{
	return *(*(_map + posI) + posJ);
}

template<class TYPE>
inline void mappe<TYPE>::print(ostream& out) const
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			out << " " <<  *(*(_map + i) + j) << " ";
		}
		out << endl;
	}
}

template<class TYPE>
void mappe<TYPE>::read(istream & entree)
{
	TYPE readVal;

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			if (entree >> readVal)
			{
				*(*(_map + i) + j) = readVal;
			}
			else
			{
				exit(EXIT_FAILURE);
			}
		}
	}
	
}



template<class TYPE>
inline ostream& operator<<(ostream& out, const mappe<TYPE>& m)
{
	m.print(out);
	return out;
}

template<class TYPE>
inline istream& operator>>(istream& in, mappe<TYPE>& m)
{
	m.read(in);
	return in;
}

template<class TYPE>
void mappe<TYPE>::readFile(mappe<TYPE>& mapLue, const char* nomFichier)
{
	
	ifstream fichier(nomFichier); //ouverture du ficher
	int nbLine, nbCol;
	if (fichier.is_open())
	{
		mapLue.setName(nomFichier);
		fichier >> nbLine >> nbCol;
		mapLue.resize(nbLine, nbCol);
		fichier >> mapLue; //lecture de la matrice
		fichier.close();
	}
	else
	{
		cout << "Fichier : " << nomFichier << " inexistant";
	}
}

/*
template<class TYPE>
mappe<TYPE>::map(const mappe<TYPE>& mapObj) {
	_row = mapObj._row;
	_col = mapObj._col;
	_map = nullptr;

	if (_row && _col)
	{
		_map = new TYPE * [_row];

		for (int i = 0; i < _row; i++)
		{
			*(_map + i) = new TYPE[_col];
		}
		for (int i = 0; i < _row; i++)
		{
			*(_map + i) = new TYPE[_col];
			for (int j = 0; j < _col; j++)
			{
				*(*(_map + i) + j) = *(*(mapObj._map + i) + j);
			}
			strcpy(_nom, mapObj._nom);
		}
	}

}*/