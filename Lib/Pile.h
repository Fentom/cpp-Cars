#ifndef PILE_H
#define PILE_H

#include "ListeBase.h"
#include <iostream>

using namespace std;

template<class type>
class Pile : public ListeBase<type>
{
	private:
	public:
		void insere(const type & val);
		type retire();
};

#endif

