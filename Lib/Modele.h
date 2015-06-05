#ifndef MODELE_H
#define MODELE_H

#include <iostream>

using namespace std;

class Modele
{
	friend ostream & operator<< (ostream & flux, const Modele & M);
	friend istream & operator>> (istream & flux, Modele & M);

	private:
		char * _name;
		int _power;
		bool _ifdiesel;
		float _price;

		int Comparaison(const Modele & M);
	public:
		Modele();
		Modele(const char * name, const int power, const bool ifdiesel, const float price);
		Modele(const Modele & obj);
		virtual ~Modele();

		void setNom(const char * name);
		void setPuissance(const int power);
		void setDiesel(const bool ifdiesel);
		void setPrixDeBase(const float price);

		const char * getNom() const;
		const int getPuissance() const;
		const bool isDiesel() const;
		const float getPrixDeBase() const;

		void Affiche() const;
		const char * toString() const;

		Modele & operator=(const Modele & M);

		int operator<(const Modele & M);
		int operator>(const Modele & M);
		int operator==(const Modele & M);

		void Save(std::ofstream &f);
        void Load(std::ifstream &f);
};

#endif
