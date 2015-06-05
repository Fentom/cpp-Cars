#include "Client.h"


#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;

Client::Client()
{
	_lastname = NULL;
	_firstname = NULL;
	_adresse = NULL;

	setNom("PasdeNom");
	setPrenom("PasdePrenom");
	setNumero(0);
	setAdresse("Pasd'adresse");
}

Client::Client(const char * nom, const char * prenom, const int nombre, const char * ad)
{
	_lastname = NULL;
	_firstname = NULL;
	_adresse = NULL;

	setNom(nom);
	setPrenom(prenom);
	setNumero(nombre);
	setAdresse(ad);
}

Client::Client(const Client & C)
{
	_lastname = NULL;
	_firstname = NULL;
	_adresse = NULL;

	setNom(C.getNom());
	setPrenom(C.getPrenom());
	setNumero(C.getNumero());
	setAdresse(C.getAdresse());
}

Client::~Client()
{
	delete _lastname;
	delete _firstname;
	delete _adresse;
}


void Client::setNumero(const int nombre)
{
	_number = nombre;
}

void Client::setAdresse(const char * ad)
{
	if(_adresse != NULL)
		delete [] _adresse;

	_adresse = new char[strlen(ad)+1];
	strcpy(_adresse, ad);
}


const int Client::getNumero() const
{
	return _number;
}

const char * Client::getAdresse() const
{
	return _adresse;
}


void Client::Affiche() const
{
	cout << endl;
	cout << "Nom : " << getNom() << endl;
	cout << "Prenom : " << getPrenom() << endl;
	cout << "Numero : " << getNumero() << endl;
	cout << "Adresse : " << getAdresse() << endl;
}

const char * Client::toString() const
{
	ostringstream s;

	s << "CLIENT:" << getNumero() << "# Nom: " << getNom() << " - Prenom: " << getPrenom();

	return s.str().c_str();
}

void Client::Save(std::ofstream &f)
{
	char buff[100];
	int n;

	f.write((char*) &_number, sizeof(int));

	n = strlen(_lastname);
	f.write((char*) &n, sizeof(int));
	f.write(_lastname, n);

	n = strlen(_firstname);
	f.write((char*) &n, sizeof(int));
	f.write(_firstname, n);

	n = strlen(_adresse);
	f.write((char*) &n, sizeof(int));
	f.write(_adresse, n);

}

void Client::Load(std::ifstream &f)
{
	char buff[100];
	int n;

    f.read((char*) &_number, sizeof(int));

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setNom(buff);

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setPrenom(buff);

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setAdresse(buff);
}

Client & Client::operator=(const Client & C)
{
	_lastname = NULL;
	_firstname = NULL;
	_adresse = NULL;

	setNom(C.getNom());
	setPrenom(C.getPrenom());
	setNumero(C.getNumero());
	setAdresse(C.getAdresse());
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Client & C)
	{
		flux << C.toString();

		return flux;
	}
	istream & operator>> (istream & flux, Client & C)
	{
		cout << "Nom : ";
		flux >> C._lastname;
		cout << "Prenom : ";
		flux >> C._firstname;
		cout << "Numero : ";
		flux >> C._number;
		cout << "Adresse : ";
		flux >> C._adresse;

		flux.clear();
		flux.ignore();

		return flux;
	}
	
//
