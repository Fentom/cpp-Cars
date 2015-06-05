#ifndef CLIENT_H
#define CLIENT_H

#include "Personne.h"

#include <iostream>

using namespace std;

class Client : public Personne
{
	friend ostream & operator<< (ostream & flux, const Client & C);
	friend istream & operator>> (istream & flux, Client & C);

	private:
		int _number;
		char * _adresse;
	public:
		Client();
		Client(const char * nom, const char * prenom, const int nombre, const char * ad);
		Client(const Client & C);
		~Client();

		void setNumero(const int nombre);
		void setAdresse(const char * ad);

		const int getNumero() const;
		const char * getAdresse() const;

		void Affiche() const;
		const char * toString() const;

		void Save(std::ofstream &f);
        void Load(std::ifstream &f);

		Client & operator=(const Client & C);
};

#endif // CLIENT_H
