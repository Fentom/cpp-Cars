#ifndef DATE_H
#define DATE_H

#include <iostream>
#include "InvalidDateException.h"

using namespace std;

class Date
{
	friend ostream & operator<< (ostream & flux, const Date & D);
	friend istream & operator>> (istream & flux, Date & D);

	private:
		int _day;
		int _month;
		int _year;

		int Comparaison(const Date & D);
	public:
		Date();
		Date(const int jour, const int mois, const int annee);
		Date(const Date & obj);
		~Date();

		const int getJour() const;
		const int getMois() const;
		const int getAnnee() const;

		void setJour(const int j);
		void setMois(const int m);
		void setAnnee(const int a);

		void Affiche() const;
		const char * toString() const;
		bool CheckDate(const int jour, const int mois, const int annee);
		bool Bissextile(const int annee);

		void Save(std::ofstream &f);
        void Load(std::ifstream &f);

        Date & operator=(const Date & D);

		int operator<(const Date & D);
		int operator>(const Date & D);
		int operator==(const Date & D);
};

#endif // DATE_H
