#include "Voiture.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>


using  namespace std;

int Voiture::Comparaison(const Voiture & V)
{
	if(getPrix() < V.getPrix() )
		return -1;

	if(getPrix() > V.getPrix() )
		return 1;

	if(getPrix() == V.getPrix() )
		return 0;
}

Voiture::Voiture()
{
	// cout << endl << "Appel du constructeur par defaut de voiture" << endl;

	_name = NULL;
	setNom("DEFAULT");
	setModele(Modele());

	for (int i = 0 ; i < 10 ; i++)
		options[i] = NULL;
}
Voiture::Voiture(const char * name, const Modele & obj)
{
	// cout << endl << "Appel du constructeur complet de voiture" << endl;

	_name = NULL;
	setNom(name);
	setModele(obj);

	for (int i = 0 ; i < 10 ; i++)
		options[i] = NULL;
}
Voiture::Voiture(const Voiture & obj)
{
	// cout << endl << "Appel du constructeur de copie de voiture" << endl;
	_name = NULL;

	setNom(obj.getNom());
	setModele(obj.getModele());

	for (int i = 0 ; i < 10 ; i++)
		options[i] = NULL;

	for (int i = 0 ; i < 10 ; i++)
	{
		if(obj.options[i] != NULL)
		{
			AjouteOption(obj.getOption(i));
		}
	}
}
Voiture::~Voiture()
{
	// cout << endl << "Appel du desructeur de voiture" << endl;

	if (_name != NULL)
		delete []_name;

	for(int i = 0 ; i < 10 ; i++)
	{
		if (options[i] != NULL)
			delete options[i];
	}
}

void Voiture::setNom(const char * name)
{
	if(_name != NULL)
		delete [] _name;

	_name = new char[strlen(name)+1];
	strcpy(_name, name);
}
void Voiture::setModele(const Modele & obj)
{
	_modele.setNom(obj.getNom());
	_modele.setPuissance(obj.getPuissance());
	_modele.setDiesel(obj.getPuissance());
	_modele.setPrixDeBase(obj.getPrixDeBase());
}

const char * Voiture::getNom() const
{
	return _name;
}
const Modele & Voiture::getModele() const
{
	return _modele;
}
Option & Voiture::getOption(int ind) const
{
	return *options[ind];
}
const float Voiture::getPrix() const 
{
	float prix = 0;

	prix = prix + getModele().getPrixDeBase();

	for (int i = 0 ; i < 10 ; i++)
	{
		if(options[i] != NULL)
			prix = prix + options[i]->getPrix();
	}

	return prix;
}
void Voiture::Affiche() const
{
	int i = 0;

	cout << endl << "Nom : " << getNom() << endl << endl;
	cout << "	Modele : ";
	getModele().Affiche();
	cout << endl;
	cout << "	Options : " << endl;

	int trouve = 0;

	for (i = 0 ; i < 10 ; i++)
	{
		if (options[i] != NULL)
		{
			trouve = 1;
			options[i]->Affiche();
			cout << endl;
		}
	}

	if (trouve == 0)
		cout << "Il n'y a pas d'options" << endl;
}

const char * Voiture::toString() const
{
	ostringstream s;

	s << "VOITURE:" << getNom() << "#" << getModele().getNom();

	return s.str().c_str();
}

void Voiture::AjouteOption(const Option & opt)
{
	for(int i = 0 ; i < 10 ; i++)
	{
		if(options[i] == NULL)
		{
			options[i] = new Option(opt);
			i = 10;
		}
	}
}

void Voiture::RetireOption(const char * code)
{
	int found = 0;

	for (int i = 0 ; i < 10 && found == 0 ; i++)
	{
		if(strcmp(options[i]->getCode(), code) == 0)
		{
			delete options[i];
			options[i] = NULL;
			found = 1;
		}
	}

	if (found == 1)
		cout << "Option retiree avec succes." << endl;
	else
		cout << "Option inconnue." << endl;
}


Voiture & Voiture::operator=(const Voiture & V)
{
	_name = NULL;

	setNom(V.getNom());
	setModele(V.getModele());

	for (int i = 0 ; i < 10 ; i++)
		options[i] = NULL;

	for (int i = 0 ; i < 10 ; i++)
	{
		if(V.options[i] != NULL)
		{
			AjouteOption(V.getOption(i));
		}
	}
}

int Voiture::operator<(const Voiture & V)
{
	return Comparaison(V) == -1;
}
int Voiture::operator>(const Voiture & V)
{
	return Comparaison(V) == 1;
}
int Voiture::operator==(const Voiture & V)
{
	return Comparaison(V) == 0;
}

void Voiture::Save()
{
	char NomFichier[100];
	char Buff[100];
	int n;

	strcpy(NomFichier, _name);
	strcat(NomFichier, ".car");

	ofstream fichier(NomFichier,ios::out);

	n = strlen(_name);
	fichier.write((char*) &n, sizeof(int));
	fichier.write(_name, n);

	_modele.Save(fichier);

	n = 0;

	for (int i = 0; i < 10; i++)
	{
		if (options[i] != NULL)
		{
			n++;
		}
	}

	fichier.write((char*) &n, sizeof(int)); // Pour connaitre le nbr d'option

	for (int i = 0; i < 10; i++)
	{
		if (options[i] != NULL)
		{
			options[i]->Save(fichier);
		}
	}

}
     
void Voiture::Load(const char* nomFichier)
{
	char buff[100];
	int n;
	Option opt;

	ifstream f(nomFichier,ios::in);

	if(f.is_open())
	{
		f.read((char*)&n, sizeof(int));
		f.read(buff, n);
		buff[n] = '\0';
		setNom(buff);

		_modele.Load(f);

		f.read((char*)&n, sizeof(int));

		for (int i = 0; i < 10; ++i)
		{
			delete options[i];
			options[i] = NULL;
		}

		for (int i = 0; i < n; ++i)
		{
			opt.Load(f);
			AjouteOption(opt);
		}
	}
	else
		cout << "Il n'y a pas de fichier avec ce nom. (NOM: " << nomFichier << ")" << endl;
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	Voiture operator+(const Voiture & V, const Option & O)
	{
		Voiture result = V;
		result.AjouteOption(O);

		return result;
	}

	Voiture operator-(const Voiture & V, const Option & O)
	{
		Voiture result = V;
		result.RetireOption(O.getCode());

		return result;
	}

	Voiture operator-(const Voiture & V, const char * code)
	{
		Voiture result = V;
		result.RetireOption(code);

		return result;
	}

	ostream & operator<< (ostream & flux, const Voiture & V)
	{
		flux << V.toString();

		return flux;
	}
	istream & operator>> (istream & flux, Voiture & V)
	{
		cout << "Nom : ";
		flux >> V._name;
		cout << "Modele : " << endl;
		flux >> V._modele;

		flux.clear();
		flux.ignore();

		return flux;
	}

//
