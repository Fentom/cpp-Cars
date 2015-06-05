#include "Contrat.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;

int Contrat::Comparaison(const Contrat & C)
{
	if(getDate() < C.getDate())
		return -1;
	if(getDate() > C.getDate())
		return 1;

	return 0;
}

Contrat::Contrat()
{
	_pcar = NULL;

	setNumero(999);
	setNumeroV(999);
	setNumeroC(999);
	setDate(Date(1,1,2000));
	setRistourne(0);
}
Contrat::Contrat(int n, int nv, int nc, Date d, Voiture & v, float r)
{
	_pcar = NULL;

	setNumero(n);
	setNumeroV(nv);
	setNumeroC(nc);
	setDate(d);
	setVoiture(v);
	setRistourne(r);
}
Contrat::~Contrat()
{
	if (_pcar != NULL)
		delete _pcar;
}

void Contrat::setNumero(const int n)
{
	_number = n;
}
void Contrat::setNumeroV(const int n)
{
	_sellerNumber = n;
}
void Contrat::setNumeroC(const int n)
{
	_customerNumber = n;
}
void Contrat::setDate(const Date & D)
{
	_date = D;
}
void Contrat::setVoiture(const Voiture & V)
{
	if (_pcar != NULL)
		delete _pcar;

	_pcar = new Voiture(V);
}
void Contrat::setRistourne(const float rist)
{
	if(_pcar != NULL)
	{
		if(rist >= getVoiture().getPrix())
			throw InvalidRistourneException("La ristourne est trop importante");
	}

	_ristourne = rist;
}

int Contrat::getNumero() const
{
	return _number;
}
int Contrat::getNumeroV() const
{
	return _sellerNumber;
}
int Contrat::getNumeroC() const
{
	return _customerNumber;
}
Date Contrat::getDate() const
{
	return _date;
}
Voiture & Contrat::getVoiture() const
{
	return *_pcar;
}
float Contrat::getRistourne() const
{
	return _ristourne;
}
void Contrat::Affiche() const
{
	cout << endl << "############# CONTRAT #############" << endl;	
	cout << "Num. Contrat: " << getNumero() << " - Num. Vendeur: " << getNumeroV() << " - Num. Client: " << getNumeroC() << " - Date: " << getDate().toString() << endl;
	getVoiture().Affiche();
	cout << endl << "Prix de la voiture: " << getVoiture().getPrix() << " eur" << endl;
	cout << "Ristourne de: -" << getRistourne() << " eur" << endl;
	cout << "_________________________" << endl;
	cout << "Prix final: " << getVoiture().getPrix() - getRistourne() << endl;
}
const char * Contrat::toString() const
{
	ostringstream s;

	s << getNumero() << " :Num Contrat" << " | Num Client: " << getNumeroC() << " - Prix final: " << getVoiture().getPrix() - getRistourne();

	return s.str().c_str();
}

Contrat & Contrat::operator=(const Contrat & C)
{
	_pcar = NULL;

	setNumero(C.getNumero());
	setNumeroV(C.getNumeroV());
	setNumeroC(C.getNumeroC());
	setDate(C.getDate());
	setVoiture(C.getVoiture());
	setRistourne(C.getRistourne());
}
int Contrat::operator<(const Contrat & C)
{
	return Comparaison(C) == -1;
}
int Contrat::operator>(const Contrat & C)
{
	return Comparaison(C) == 1;
}
int Contrat::operator==(const Contrat & C)
{
	return Comparaison(C) == 0;
}

void Contrat::Save(std::ofstream &f)
{
	int n;

    f.write((char*) &_number, sizeof(int));
    f.write((char*) &_sellerNumber, sizeof(int));
    f.write((char*) &_customerNumber, sizeof(int));

    _date.Save(f);

	n = strlen(getVoiture().getNom());
	f.write((char*) &n, sizeof(int));
	f.write(getVoiture().getNom(), n);

	f.write((char*) &_ristourne, sizeof(int));
}
     
void Contrat::Load(std::ifstream &f)
{
	Voiture tmpV;
	char Buff[100];
	int n;

	f.read((char*) &_number, sizeof(int));
	f.read((char*) &_sellerNumber, sizeof(int));
	f.read((char*) &_customerNumber, sizeof(int));

	_date.Load(f);

	f.read((char*)&n, sizeof(int));
    f.read(Buff, n);
    Buff[n] = '\0';
    strcat(Buff, ".car");

    tmpV.Load(Buff);
    _pcar = new Voiture(tmpV);

	f.read((char*) &_ristourne, sizeof(float));
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Contrat & C)
	{
		flux << C.toString();

		return flux;
	}

//
