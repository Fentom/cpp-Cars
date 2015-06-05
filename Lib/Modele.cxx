#include "Modele.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>


using namespace std;

Modele::Modele()
{
	// cout << endl << "Appel du constructeur par defaut de modele" << endl;
	_name = NULL;

	setNom("Modele par defaut");
	setPuissance(0);
	setDiesel(false);
	setPrixDeBase(0);
}

Modele::Modele(const char * name, const int power, const bool ifdiesel, const float price)
{
	// cout << endl << "Appel du constructeur complet de modele" << endl;
	_name = NULL;
	
	setNom(name);
	setPuissance(power);
	setDiesel(ifdiesel);
	setPrixDeBase(price);
}

Modele::Modele(const Modele & obj)
{
	// cout << endl << "Copie d'un autre modele" << endl;
	_name = NULL;

	setNom(obj.getNom());
	setPuissance(obj.getPuissance());
	setDiesel(obj.isDiesel());
	setPrixDeBase(obj.getPrixDeBase());
}

Modele::~Modele()
{
	// cout << endl << "Appel du destructeur de Modele" << endl;
	delete [] _name;
}

int Modele::Comparaison(const Modele & M)
{
	if(_price < M._price )
		return -1;

	if(_price > M._price )
		return 1;

	if(_price == M._price )
		return 0;
}
void Modele::setNom(const char * name)
{
	if(_name != NULL)
		delete [] _name;

	_name = new char[strlen(name)+1];
	strcpy(_name, name);
}
void Modele::setPuissance(const int power)
{
	_power = power;
}
void Modele::setDiesel(const bool ifdiesel)
{
	_ifdiesel = ifdiesel;
}
void Modele::setPrixDeBase(const float price)
{
	_price = price;
}

const char * Modele::getNom() const
{
	return _name;
}
const int Modele::getPuissance() const
{
	return _power;
}
const bool Modele::isDiesel() const
{
	return _ifdiesel;
}
const float Modele::getPrixDeBase() const
{
	return _price;
}

void Modele::Affiche() const
{
	cout << endl << "Nom : " << getNom() << endl;
	cout << "Puissance : " << getPuissance() << endl;
	cout << "Carburant : ";
	if (isDiesel())
		cout << "Diesel";
	else
		cout << "Essence";
	cout << endl;
	cout << "Prix : " << getPrixDeBase() << endl;
}

const char * Modele::toString() const
{
	ostringstream s;

	s << getNom() << " | Puissance " << getPuissance() << " | Carburant : ";
	if (isDiesel())
		s << "Diesel";
	else
		s << "Essence";
	s << " | " << getPrixDeBase() << " eur";

	return s.str().c_str();
}

Modele & Modele::operator=(const Modele & E)
{
	_name = NULL;

	setNom(E.getNom());
	setPuissance(E.getPuissance());
	setDiesel(E.isDiesel());
	setPrixDeBase(E.getPrixDeBase());
}

int Modele::operator<(const Modele & M)
{
	return Comparaison(M) == -1;
}
int Modele::operator>(const Modele & M)
{
	return Comparaison(M) == 1;
}
int Modele::operator==(const Modele & M)
{
	return Comparaison(M) == 0;
}

void Modele::Save(std::ofstream &f)
{
	char buff[100];
	int n;

	n = strlen(_name);
	f.write((char*) &n, sizeof(int));
	f.write(_name, n);

    f.write((char*) &_power, sizeof(int));
    f.write((char*) &_ifdiesel, sizeof(bool));
    f.write((char*) &_price, sizeof(float));
}
void Modele::Load(std::ifstream &f)
{
	char buff[100];
	int n;

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setNom(buff);

    f.read((char*) &_power, sizeof(int));
    f.read((char*) &_ifdiesel, sizeof(bool));
    f.read((char*) &_price, sizeof(float));
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Modele & M)
	{
		flux << M.toString();

		return flux;
	}

	istream & operator>> (istream & flux, Modele & M)
	{
		cout << "Nom : ";
		flux >> M._name;
		cout << "Puissance : ";
		flux >> M._power;
		cout << "Diesel? (1 ou 0) : ";
		flux >> M._ifdiesel;
		cout << "Prix : ";
		flux >> M._price;

		flux.clear();
		flux.ignore();

		return flux;
	}

//
