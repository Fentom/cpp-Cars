#ifndef FICHIERCLIENT_H
#define FICHIERCLIENT_H

#include "ListeTriee.h"
#include "Client.h"

#include <fstream>
using namespace std;

class FichierClient
{
    private:
        char _nomFichier[50];
        int _iNbreEnreg;
    public:
        FichierClient();
        FichierClient(const char* nF);
        ~FichierClient();

        const char* getNomFichier() const;
        int getNombreEnregistrement() const;

        void setNomFichier(const char* nF);
        void setNombreEnregistrement(int nE);

        int recupNombreEnregistrement(const char* nF);
        void Add(Client & emp);
        void Load(ListeTriee<Client> & lClient);
        void Save(ListeTriee<Client> & lClient);
        void list();
};

#endif // FICHIERCLIENT_H
