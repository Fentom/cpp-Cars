#include "ListeBase.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

template<class type>
ListeBase<type>::ListeBase()
{
	pTete = NULL;
}


// template<class type>
// ListeBase<type>::ListeBase(const ListeBase & lis)
// {
// 	if(lis.vide())
// 		return;

// 	Cellule<type> *pCopy = lis.pTete;
// 	Cellule<type> *pTemp;

// 	pTete = new Cellule<type>;
// 	pTete->valeur = type(lis.pTete->valeur);
// 	pTete->suivant = NULL;

// 	pTemp = pTete;

// 	while(pCopy = pCopy->suivant)
// 	{
// 		pTemp->suivant = new Cellule<type>;
// 		pTemp->suivant->valeur = type(pCopy->valeur);
// 		pTemp = pTemp->suivant;
// 	}

// 	pTemp->suivant = NULL;
// }

template<class type>
ListeBase<type>::~ListeBase()
{
	Cellule<type> *pCur, *pPrec;

	pCur = pTete;

	while(pCur != NULL)
	{
		pPrec = pCur;
		pCur = pCur->suivant;

		delete pPrec;
	}

}

template<class type>
const bool ListeBase<type>::vide() const
{
	if(pTete == NULL)
		return 1;
	else
		return -1;
}

template<class type>
const int ListeBase<type>::getNombreElements() const
{
	Cellule<type> *pCur;
	int i = 0;

	pCur = pTete;

	while(pCur != NULL)
	{
		i++;
		pCur = pCur->suivant;
	}

	return i;
}

template<class type>
void ListeBase<type>::Affiche() const
{
	Cellule<type> *pCur;
	int i = 0;

	pCur = pTete;
	if (pCur == NULL)
		cout << "La liste est vide." << endl;
	else
	{
		while(pCur != NULL)
		{
			cout << "indice [" << i << "] = " << pCur->valeur << endl;
			pCur = pCur->suivant;
			i++;
		}
	}
}

template class Cellule<int>;
template class ListeBase<int>;

#include "Option.h"
template class Cellule<Option>;
template class ListeBase<Option>;

#include "Personne.h"
template class Cellule<Personne>;
template class ListeBase<Personne>;

#include "Employe.h"
template class Cellule<Employe>;
template class ListeBase<Employe>;

#include "Client.h"
template class Cellule<Client>;
template class ListeBase<Client>;

#include "Modele.h"
template class Cellule<Modele>;
template class ListeBase<Modele>;

#include "Contrat.h"
template class Cellule<Contrat>;
template class ListeBase<Contrat>;
