#include "Pile.h"
#include <iostream>

using namespace std;

template<class type>
void Pile<type>::insere(const type & val)
{
	Cellule<type> *toAdd = new Cellule<type>;

	toAdd->valeur = type(val);
	toAdd->suivant = this->pTete;

	this->pTete = toAdd;
}

template<class type>
type Pile<type>::retire()
{
	if (this->pTete == NULL)
		cout << "Il n'y a rien a depiler!" << endl;
	else
	{
		Cellule<type> *toRemove = this->pTete;
		type ret;

		this->pTete = this->pTete->suivant;
		ret = toRemove->valeur;
		delete toRemove;

		return ret;
	}
}

#include "Option.h"
template class Pile<int>;
template class Pile<Option>;

