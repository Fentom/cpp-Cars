#ifndef VOITURE_H
#define VOITURE_H

#include "Modele.h"
#include "Option.h"
#include <iostream>

using namespace std;

class Voiture
{
	friend Voiture operator+(const Voiture & V, const Option & O);
	friend Voiture operator-(const Voiture & V, const Option & O);
	friend Voiture operator-(const Voiture & V, const char * code);

	friend ostream & operator<< (ostream & flux, const Voiture & V);
	friend istream & operator>> (istream & flux, Voiture & V);

	private:
		char * _name;
		Modele _modele;
		Option * options[10];

		int Comparaison(const Voiture & V);
	public:
		Voiture();
		Voiture(const char * name, const Modele & obj);
		Voiture(const Voiture & obj);
		virtual ~Voiture();

		void setNom(const char * name);
		void setModele(const Modele & obj);

		const char * getNom() const;
		const Modele & getModele() const;

		Option & getOption(int ind) const; // for own uses
		const float getPrix() const;

		void Affiche() const;
		const char * toString() const;
		void AjouteOption(const Option & opt);
		void RetireOption(const char * code);

		void Save();
        void Load(const char* nomFichier);

		Voiture & operator=(const Voiture & V);

		int operator<(const Voiture & V);
		int operator>(const Voiture & V);
		int operator==(const Voiture & V);
};


#endif // VOITURE_H
