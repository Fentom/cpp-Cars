#include "Liste.h"
#include <iostream>

using namespace std;

template<class type>
void Liste<type>::insere(const type & val)
{
	Cellule<type> *pCur = this->pTete;

	if(pCur == NULL)
	{
		this->pTete = new Cellule<type>;
		this->pTete->valeur = type(val);
	}
	else
	{
		while(pCur->suivant != NULL)
		{
			pCur = pCur->suivant;
		}

		pCur->suivant = new Cellule<type>;
		pCur->suivant->valeur = type(val);
	}
}

#include "Option.h"
template class Liste<int>;
template class Liste<Option>;

