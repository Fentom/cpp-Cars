#ifndef CONTRAT_H
#define CONTRAT_H

#include "Date.h"
#include "Voiture.h"
#include "InvalidRistourneException.h"

#include <iostream>

using namespace std;

class Contrat
{
	friend ostream & operator<< (ostream & flux, const Contrat & C);

	private:
		int _number;
		int _sellerNumber;
		int _customerNumber;
		Date _date;
		Voiture * _pcar;
		float _ristourne;

		int Comparaison(const Contrat & C);
	public:
		Contrat();
		Contrat(int n, int nv, int nc, Date d, Voiture & v, float r);
		~Contrat();

		void setNumero(const int n);
		void setNumeroV(const int n);
		void setNumeroC(const int n);
		void setDate(const Date & D);
		void setVoiture(const Voiture & V);
		void setRistourne(const float rist);

		int getNumero() const;
		int getNumeroV() const;
		int getNumeroC() const;
		Date getDate() const;
		Voiture & getVoiture() const;
		float getRistourne() const;

		void Affiche() const;
		const char * toString() const;

        Contrat & operator=(const Contrat & C);

		int operator<(const Contrat & C);
		int operator>(const Contrat & C);
		int operator==(const Contrat & C);

		void Save(std::ofstream &f);
        void Load(std::ifstream &f);
};


#endif // CONTRAT_H
