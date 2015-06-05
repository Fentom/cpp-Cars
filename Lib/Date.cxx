#include "Date.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using  namespace std;

int Date::Comparaison(const Date & D)
{
	if(this->getAnnee() > D.getAnnee())
		return 1;
	if(this->getAnnee() < D.getAnnee())
		return -1;
	if(this->getMois() > D.getMois())
		return 1;
	if(this->getMois() < D.getMois())
		return -1;
	if(this->getJour() > D.getJour())
		return 1;
	if(this->getJour() < D.getJour())
		return -1;
	
	return 0;
}
Date::Date()
{
	_day = 1;
	_month = 1;
	_year = 2000;
}
Date::Date(const int jour, const int mois, const int annee)
{
	if(!CheckDate(jour, mois, annee))
		throw InvalidDateException("Date invalide");

	setJour(jour);
	setMois(mois);
	setAnnee(annee);
}
Date::Date(const Date & obj)
{
	setJour(obj.getJour());
	setMois(obj.getMois());
	setAnnee(obj.getAnnee());
}
Date::~Date()
{

}

const int Date::getJour() const
{
	return _day;
}
const int Date::getMois() const
{
	return _month;
}
const int Date::getAnnee() const
{
	return _year;
}
void Date::setJour(const int j)
{
	_day = j;
}
void Date::setMois(const int m)
{
	_month = m;
}
void Date::setAnnee(const int a)
{
	_year = a;
}
void Date::Affiche() const
{
	cout << "Voici la date : " << endl;
	cout <<  getJour() << "/" << getMois() << "/" << getAnnee() << endl;
}
const char * Date::toString() const
{
	ostringstream s;

	s << getJour() << "/" << getMois() << "/" << getAnnee() << endl;

	return s.str().c_str();
}
bool Date::CheckDate(const int jour, const int mois, const int annee)
{
	int jourDsMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(Bissextile(annee))
		jourDsMois[1]++;

	if(annee < 2000)
		return false;

	if(mois > 12 || mois < 1)
		return false;

	if(jour < 1 || jour > jourDsMois[mois - 1])
		return false;

	return true;
}
bool Date::Bissextile(const int annee)
{
	if(annee % 4 == 0 && annee % 100 != 0 || annee % 400 == 0)
		return true;
	else
		return false;
} 

void Date::Save(std::ofstream &f)
{
    f.write((char*) &_day, sizeof(int));
    f.write((char*) &_month, sizeof(int));
    f.write((char*) &_year, sizeof(int));
}
void Date::Load(std::ifstream &f)
{
	f.read((char*) &_day, sizeof(int));
	f.read((char*) &_month, sizeof(int));
	f.read((char*) &_year, sizeof(int));
}

Date & Date::operator=(const Date & D)
{
	setJour(D.getJour());
	setMois(D.getMois());
	setAnnee(D.getAnnee());
}
int Date::operator<(const Date & D)
{
	return Comparaison(D) == -1;
}
int Date::operator>(const Date & D)
{
	return Comparaison(D) == 1;
}
int Date::operator==(const Date & D)
{
	return Comparaison(D) == 0;
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Date & D)
	{
		flux << D.toString();

		return flux;
	}
	istream & operator>> (istream & flux, Date & D)
	{
		int day, month, year;

		cout << "Jour : ";
		flux >> day;

		cout << "Mois : ";
		flux >> month;

		cout << "Annee : ";
		flux >> year;

		D = Date(day, month, year);

		flux.clear();
		flux.ignore();

		return flux;
	}

//
