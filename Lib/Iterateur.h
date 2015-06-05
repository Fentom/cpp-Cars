#ifndef ITERATEUR_H
#define ITERATEUR_H

#include <iostream>
#include "ListeBase.h"

using namespace std;

template<class type>
class Iterateur
{
	private:
		ListeBase<type> &_list;
		Cellule<type> *_pCur;
		Cellule<type> *_pPrec;
	public:
		Iterateur(ListeBase<type> & l);

		void reset();
		bool end();
		type remove();

		bool operator++();
		bool operator++ (int);
		operator type() const { return _pCur->valeur; }
		type& operator&(void) { return _pCur->valeur; }
};

#endif // ITERATEUR_H
