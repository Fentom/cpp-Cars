#include "ListeTriee.h"
#include <iostream>

using namespace std;

template<class type>
void ListeTriee<type>::insere(const type & val)
{
	cout << "In inserer liste" << endl;
	Cellule<type> *pParc = this->pTete;
	Cellule<type> *pPrec = NULL;
	Cellule<type> *pTemp = NULL;

	if(pParc == NULL)
	{
		this->pTete = new Cellule<type>;
		this->pTete->valeur = type(val);
		this->pTete->suivant = NULL;
	}
	else
	{
		while (pParc != NULL && pParc->valeur < val)
		{
			pPrec = pParc;
			pParc = pParc->suivant;
		}

		if (pPrec == NULL) // AJout en début de liste
		{
			pTemp = this->pTete;
			this->pTete = new Cellule<type>;
			this->pTete->valeur = type(val);
			this->pTete->suivant = pTemp;
		}
		else
		{
			pPrec->suivant = new Cellule<type>;
			pPrec->suivant->valeur = type(val);
			pPrec->suivant->suivant = pParc;
		}
	}
}

template class ListeTriee<int>;

#include "Personne.h"
template class ListeTriee<Personne>;

#include "Employe.h"
template class ListeTriee<Employe>;

#include "Client.h"
template class ListeTriee<Client>;

#include "Modele.h"
template class ListeTriee<Modele>;

#include "Contrat.h"
template class ListeTriee<Contrat>;
