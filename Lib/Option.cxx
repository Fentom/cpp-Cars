#include "Option.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using  namespace std;

Option::Option()
{
	_intitule = NULL;

	setCode("0000");
	setIntitule("Default");
	setPrix(0);
}
Option::Option(const char * code, const char * intitule, const float prix)
{
	_intitule = NULL;
	
	setCode(code);
	setIntitule(intitule);
	setPrix(prix);
}
Option::Option(const Option & obj)
{
	// cout << endl << "Copie d'une autre option" << endl;
	_intitule = NULL;

	setCode(obj.getCode());
	setIntitule(obj.getIntitule());
	setPrix(obj.getPrix());
}
Option::~Option()
{
	if (_intitule != NULL)
		delete [] _intitule;
}

void Option::setCode(const char * code)
{
	strcpy(_code, code);
}

void Option::setIntitule(const char * intitule)
{
	if(_intitule != NULL)
		delete [] _intitule;

	_intitule = new char[strlen(intitule)+1];
	strcpy(_intitule, intitule);
}

void Option::setPrix(const float price)
{
	_price = price;
}

const char * Option::getCode() const
{
	return _code;
}
const char * Option::getIntitule() const
{
	return _intitule;
}
const float Option::getPrix() const
{
	return _price;
}

void Option::Affiche() const
{
	cout << "Code : " << getCode() << endl;
	cout << "Intitule : " << getIntitule() << endl;
	cout << "Prix : " << getPrix() << endl;
}

const char * Option::toString() const
{
	ostringstream s;

	s << "OPTION:" << getCode() << "#" << getIntitule() << "#" << getPrix(); 

	return s.str().c_str();
}

Option Option::operator--() // pré-décrémentation
{
	setPrix(getPrix()-50);

	return *this;
}
Option Option::operator--(int) // post-décrémentation
{
	Option opt(*this);
	--(*this);

	return opt;
}

Option & Option::operator=(const Option & O)
{
	// cout << endl << "Copie d'une autre option" << endl;
	_intitule = NULL;

	setCode(O.getCode());
	setIntitule(O.getIntitule());
	setPrix(O.getPrix());
}

void Option::Save(std::ofstream &f)
{
	char buff[100];
	int n;

	n = strlen(_code);
	f.write((char*) &n, sizeof(int));
	f.write(_code, n);

	n = strlen(_intitule);
	f.write((char*) &n, sizeof(int));
	f.write(_intitule, n);

    f.write((char*) &_price, sizeof(float));
}
void Option::Load(std::ifstream &f)
{
	char buff[100];
	int n;

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setCode(buff);

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setIntitule(buff);

    f.read((char*) &_price, sizeof(float));
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Option & O)
	{
		flux << O.toString();

		return flux;
	}
	istream & operator>> (istream & flux, Option & O)
	{
		cout << "Code : ";
		flux >> O._code;
		cout << "Intitule : ";
		flux >> O._intitule;
		cout << "Prix : ";
		flux >> O._price;

		flux.clear();
		flux.ignore();
	}

//
