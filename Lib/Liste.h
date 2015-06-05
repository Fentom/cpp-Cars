#ifndef LISTE_H
#define LISTE_H

#include "ListeBase.h"
#include <iostream>

using namespace std;

template<class type>
class Liste : public ListeBase<type>
{
	private:
	public:
		void insere(const type & val);
};

#endif

