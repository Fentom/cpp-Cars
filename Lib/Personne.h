#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>

using namespace std;

class Personne
{
	friend ostream & operator<< (ostream & flux, const Personne & P);
	friend istream & operator>> (istream & flux, Personne & P);

	private:
	protected:
		char * _lastname;
		char * _firstname;
		int Comparaison(const Personne & P);
	public:
		Personne();
		Personne(const char * nom, const char * prenom);
		Personne(const Personne & P);
		virtual ~Personne();

		void setNom(const char * nom);
		void setPrenom(const char * prenom);

		const char * getNom() const;
		const char * getPrenom() const;

		void Affiche() const;
		virtual const char * toString() const;

		int operator<(const Personne & P);
		int operator>(const Personne & P);
		int operator==(const Personne & P);
		Personne & operator=(const Personne & P);
};


#endif // PERSONNE_H
