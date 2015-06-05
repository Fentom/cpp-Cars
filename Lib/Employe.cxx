#include "Employe.h"


#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;

char Employe::ADMINISTRATIF[] = "Administratif";
char Employe::VENDEUR[] = "Vendeur";

Employe::Employe()
{
	_lastname = NULL;
	_firstname = NULL;
	_login = NULL;
	_password = NULL;
	_function = NULL;

	setNom("Admin");
	setPrenom("Admin");
	setNumero(0);
	setLogin("admin");
	setMotDePasse("admin");
	setFonction(Employe::ADMINISTRATIF);
}
Employe::Employe(const char * nom, const char * prenom, const int nombre, const char * login, const char * fct)
{
	_lastname = NULL;
	_firstname = NULL;
	_login = NULL;
	_password = NULL;
	_function = NULL;

	setNom(nom);
	setPrenom(prenom);
	setNumero(nombre);
	setLogin(login);
	setFonction(fct);
}
Employe::Employe(const Employe & E)
{
	_lastname = NULL;
	_firstname = NULL;
	_login = NULL;
	_password = NULL;
	_function = NULL;

	setNom(E.getNom());
	setPrenom(E.getPrenom());
	setNumero(E.getNumero());
	setLogin(E.getLogin());
	setMotDePasse(E.getMotDePasse());
	setFonction(E.getFonction());
}
Employe::~Employe()
{
	if (_lastname != NULL)
		delete _lastname;
	if (_firstname != NULL)
		delete _firstname;
	if (_login != NULL)
		delete _login;
	if (_password != NULL)
		delete _password;
	if (_function != NULL)
		delete _function;
}

const int Employe::CheckPassword(const char * pwd) const
{
	cout << "In password pwd;" << pwd << endl;

	if (strcmp (_login, "admin") == 0 && strcmp(pwd, "admin") == 0 )
	{
		
	}
	else
	{
		int lenght = 0;
		bool gotNumber = false, gotLetter = false, tmp = false;

		lenght = strlen(pwd);

		if(lenght < 8)
			return -1;

		for (int i = 0 ; i < lenght + 1 ; i++)
		{
			tmp = isdigit(pwd[i]);

			if (tmp == true)
				gotNumber = true;
			else
			{
				tmp = isalpha(pwd[i]);

				if(tmp == true)
					gotLetter = true;
			}
		}

		if(gotLetter == true && gotNumber == true)
			return 1;
		else
			return -1;
	}
}

int Employe::Comparaison(const Employe & E)
{
	if(_number < E._number )
		return -1;

	if(_number > E._number )
		return 1;

	if(_number == E._number )
		return 0;
}

void Employe::setNumero(const int nombre)
{
	_number = nombre;
}
void Employe::setLogin(const char * login)
{
	if(_login != NULL)
		delete [] _login;

	_login = new char[strlen(login)+1];
	strcpy(_login, login);
}
void Employe::setMotDePasse(const char * mdp)
{
	if (mdp != NULL)
	{
		if (CheckPassword(mdp) != -1)
		{
			if(_password != NULL)
				delete [] _password;

			_password = new char[strlen(mdp)+1];
			strcpy(_password, mdp);
		}
		else
		{
			throw InvalidPasswordException(strlen(mdp));
		}
	}
	else
		ResetMotDePasse();		
}
void Employe::setFonction(const char * fct)
{
	if (strcmp(fct, Employe::ADMINISTRATIF) == 0 || strcmp(fct, Employe::VENDEUR) == 0 )
	{
		if(_function != NULL)
			delete [] _function;

		_function = new char[strlen(fct)+1];
		strcpy(_function, fct);
	}
	else
		throw InvalidFonctionException("ERREUR: Fonction invalide");
}

const int Employe::getNumero() const
{
	return _number;
}
const char * Employe::getLogin() const
{
	return _login;
}
const char * Employe::getMotDePasse() const
{
	return _password;
}
const char * Employe::getFonction() const
{
	return _function;
}

void Employe::Affiche() const
{
	cout << endl;
	cout << "Nom : " << getNom() << endl;
	cout << "Prenom : " << getPrenom() << endl;
	cout << "Numero : " << getNumero() << endl;
	cout << "Login : " << getLogin() << endl;
	cout << "Mot de passe : ";
	if(getMotDePasse() == NULL || (strcmp(getMotDePasse(), "nopassword1" ) == 0) )
		cout << "pas initialise" << endl;
	else
		cout << getMotDePasse() << endl;
	cout << "Fonction : " << getFonction() << endl;
}

void Employe::ResetMotDePasse()
{
	cout << "In reset" << endl;
	if(_password != NULL)
	{
		cout << "In reset, in if" << endl;
		delete [] _password;
		_password = NULL;
	}
}

const char * Employe::toString() const
{
	locale loc;
	ostringstream s;

	s << getFonction() << ":" << getNumero() << "# "  << "Nom: " << getNom() << " | Login: " << getLogin();

	return s.str().c_str();
}

Employe & Employe::operator=(const Employe & E)
{
	_lastname = NULL;
	_firstname = NULL;
	_login = NULL;
	_password = NULL;
	_function = NULL;

	setNom(E.getNom());
	setPrenom(E.getPrenom());
	setNumero(E.getNumero());
	setLogin(E.getLogin());
	setMotDePasse(E.getMotDePasse());
	setFonction(E.getFonction());
}

int Employe::operator<(const Employe & E)
{
	return Comparaison(E) == -1;
}
int Employe::operator>(const Employe & E)
{
	return Comparaison(E) == 1;
}
int Employe::operator==(const Employe & E)
{
	return Comparaison(E) == 0;
}

void Employe::Save(std::ofstream &f)
{
	char buff[100];
	int n;

	f.write((char*) &_number, sizeof(int));

	n = strlen(_lastname) + 1;
	f.write((char*) &n, sizeof(int));
	f.write(_lastname, n);

	n = strlen(_firstname) + 1;
	f.write((char*) &n, sizeof(int));
	f.write(_firstname, n);

	n = strlen(_login) + 1;
	f.write((char*) &n, sizeof(int));
	f.write(_login, n);

	if (_password != NULL)
	{
		n = strlen(_password) + 1;
		f.write((char*) &n, sizeof(int));
		f.write(_password, n);
	}
	else
	{
		n = strlen("nopassword1") + 1;
		f.write((char*) &n, sizeof(int));
		f.write("nopassword1", n);
	}

	n = strlen(_function) + 1;
	f.write((char*) &n, sizeof(int));
	f.write(_function, n);
}

void Employe::Load(std::ifstream &f)
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
    setLogin(buff);

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setMotDePasse(buff);

    f.read((char*)&n, sizeof(int));
    f.read(buff, n);
    buff[n] = '\0';
    setFonction(buff);
}

// FONCTION LIBRE (donc amie) -- HORS de la classe

	ostream & operator<< (ostream & flux, const Employe & E)
	{
		flux << E.toString();

		return flux;
	}
	istream & operator>> (istream & flux, Employe & E)
	{
		char temp[30];

		cout << "Nom : ";
		flux >> E._lastname;
		cout << "Prenom : ";
		flux >> E._firstname;
		cout << "Numero : ";
		flux >> E._number;
		cout << "Login : ";
		flux >> E._login;
		cout << "Fonction : ";
		flux >> temp;
		E.setMotDePasse("nopassword1");
		E.setFonction(temp);

		flux.clear();
		flux.ignore();

		return flux;
	}
//
