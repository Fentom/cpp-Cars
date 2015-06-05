#include "Iterateur.h"

#include <stdlib.h>
#include <cstring>
#include <sstream>

using namespace std;

template <class type>
Iterateur<type>::Iterateur(ListeBase<type>& l):_pPrec(NULL),_list(l),_pCur(l.pTete) 
{

};

template<class type>
void Iterateur<type>::reset() 
{
	_pPrec = NULL;
	_pCur = _list.pTete;
}

template<class type>
bool Iterateur<type>::end() 
{
	return _pCur == NULL;
}

template<class type>
type Iterateur<type>::remove() 
{
	Cellule<type> * toRemove = _pCur;
	type ret;

	if(_pCur != NULL)
	{
		ret = _pCur->valeur;

		if(_pPrec == NULL)
			_list.pTete = _pCur->suivant;
		else
			_pPrec->suivant = _pCur->suivant;

		_pCur = _pCur->suivant;

		delete toRemove;
	}

	return ret;
}

template<class type>
bool Iterateur<type>::operator++()
{
	if(_pCur)
	{
		_pPrec = _pCur;
		_pCur = _pCur->suivant;
		return true;
	}
	else
		return false;
}

template <class type>
bool Iterateur<type>::operator++(int)  // post-incrementation
{
  return operator++(); 
}

template class Iterateur<int>;

#include "Option.h"
template class Iterateur<Option>;

#include "Personne.h"
template class Iterateur<Personne>;

#include "Employe.h"
template class Iterateur<Employe>;

#include "Client.h"
template class Iterateur<Client>;

#include "Modele.h"
template class Iterateur<Modele>;

#include "Contrat.h"
template class Iterateur<Contrat>;
