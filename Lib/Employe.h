#ifndef EMPLOYE_H
#define EMPLOYE_H

#include "Personne.h"
#include "InvalidFonctionException.h"
#include "InvalidPasswordException.h"

#include <iostream>

using namespace std;

class Employe : public Personne
{
	friend ostream & operator<< (ostream & flux, const Employe & E);
	friend istream & operator>> (istream & flux, Employe & E);

	private:
		int _number;
		char * _login;
		char * _password;
		char * _function;

		const int CheckPassword(const char * pwd) const;
		int Comparaison(const Employe & E);
	public:
		static char ADMINISTRATIF[];
		static char VENDEUR[];

		Employe();
		Employe(const char * nom, const char * prenom, const int nombre, const char * login, const char * fct);
		Employe(const Employe & E);
		~Employe();

		void setNumero(const int nombre);
		void setLogin(const char * login);
		void setMotDePasse(const char * mdp);
		void setFonction(const char * fct);

		const int getNumero() const;
		const char * getLogin() const;
		const char * getMotDePasse() const;
		const char * getFonction() const;

		void Affiche() const;
		void ResetMotDePasse();
		const char * toString() const;

		Employe & operator=(const Employe & E);

		int operator<(const Employe & E);
		int operator>(const Employe & E);
		int operator==(const Employe & E);

		void Save(std::ofstream &f);
        void Load(std::ifstream &f);
};

#endif // EMPLOYE_H
