#ifndef LISTE_BASE_H
#define LISTE_BASE_H

#include <iostream>

using namespace std;

template<class E> struct Cellule
{
	E valeur;
	Cellule<E> * suivant;

	Cellule()
	{
		suivant = NULL;
	}
};

template <class type> class Iterateur;

template<class type>
class ListeBase
{
	protected:
		Cellule<type> * pTete;
	public:
		ListeBase();
		// ListeBase(const ListeBase & lis);
		~ListeBase();

		const bool vide() const;
		const int getNombreElements() const;
		void Affiche() const;

		virtual void insere(const type & val) = 0;

		friend class Iterateur<type>;
};


 
#endif
