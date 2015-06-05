#include "Personne.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;


int Personne::Comparaison(const Personne & P)
{
	if(strcmp(this->_lastname, P._lastname) < 0)
		return -1;
	else
	{
		if(strcmp(this->_lastname, P._lastname) > 0)
			return 1;
		else
		{
			if(strcmp(this->_firstname, P._firstname) < 0)
				return -1;
			else
			{
				if(strcmp(this->_firstname, P._firstname) > 0)
					return 1;
				else
					return 0;
			}
		}
	}
}

Personne::Personne()
{
	_lastname = NULL;
	_firstname = NULL;

	setNom("PasdeNom");
	setPrenom("PasdePrenom");
}
Personne::Personne(const char * nom, const char * prenom)
{
	_lastname = NULL;
	_firstname = NULL;

	setNom(nom);
	setPrenom(prenom);
}
Personne::Personne(const Personne & P)
{
	_lastname = NULL;
	_firstname = NULL;

	setNom(P.getNom());
	setPrenom(P.getPrenom());
}
Personne::~Personne()
{
	delete _lastname;
	delete _firstname;
}

void Personne::setNom(const char * nom)
{
	if(_lastname != NULL)
		delete [] _lastname;

	_lastname = new char[strlen(nom)+1];
	strcpy(_lastname, nom);
}
void Personne::setPrenom(const char * prenom)
{
	if(_firstname != NULL)
		delete [] _firstname;

	_firstname = new char[strlen(prenom)+1];
	strcpy(_firstname, prenom);
}

const char * Personne::getNom() const
{
	return _lastname;
}
const char * Personne::getPrenom() const
{
	return _firstname;
}

void Personne::Affiche() const
{
	cout << endl;
	cout << "Nom : " << getNom() << endl;
	cout << "Prenom : " << getPrenom() << endl;
}
const char * Personne::toString() const
{
	ostringstream s;

	s << getNom() << "#" << getPrenom();

	return s.str().c_str();
}

Personne & Personne::operator=(const Personne & P)
{
	_lastname = NULL;
	_firstname = NULL;

	setNom(P.getNom());
	setPrenom(P.getPrenom());
}

int Personne::operator<(const Personne & P)
{
	return Comparaison(P) == -1;
}
int Personne::operator>(const Personne & P)
{
	return Comparaison(P) == 1;
}
int Personne::operator==(const Personne & P)
{
	return Comparaison(P) == 0;
}


// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Personne & P)
	{
		flux << P.toString();

		return flux;
	}
	istream & operator>> (istream & flux, Personne & P)
	{
		cout << "Nom : ";
		cin >> P._lastname;
		cout << "Prenom : ";
		cin >> P._firstname;

		flux.clear();
		flux.ignore();

		return flux;
	}

//
