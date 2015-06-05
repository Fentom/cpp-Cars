#ifndef LISTE_TRIEE_H
#define LISTE_TRIEE_H

#include "ListeBase.h"
#include <iostream>

using namespace std;

template<class type>
class ListeTriee : public ListeBase<type>
{
	private:
	public:
		void insere(const type & val);
};


#endif // LISTE_TRIEE_H
