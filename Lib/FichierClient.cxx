#include "FichierClient.h"
#include "ListeTriee.h"
#include "Client.h"
#include "Iterateur.h"

#include <string.h>
#include <iostream>

using namespace std;

FichierClient::FichierClient()
{
    setNomFichier("Clients.dat");

    fstream f(getNomFichier(), ios::in | ios::out | ios::binary);
    if (!f.is_open())
    {
        setNombreEnregistrement(0);
        f.open(getNomFichier(), ios::out | ios::app | ios::binary);
        f.write((char*) &_iNbreEnreg, sizeof(int));
    }

    f.close();
}

FichierClient::FichierClient(const char* nF)
{
    setNomFichier(nF);
    fstream f(nF, ios::in | ios::out | ios::binary);

    if (!f.is_open())
    {
        setNombreEnregistrement(0);
        f.open(nF, ios::out | ios::app | ios::binary);
        f.write((char*) &_iNbreEnreg, sizeof(int));
    }

    f.close();
}

FichierClient::~FichierClient()
{

}

const char* FichierClient::getNomFichier() const
{
    return _nomFichier;
}

int FichierClient::getNombreEnregistrement() const
{
    return _iNbreEnreg;
}

void FichierClient::setNomFichier(const char* nF)
{
    if (strlen(nF) < 50)
        strcpy(_nomFichier, nF);
}

void FichierClient::setNombreEnregistrement(int nE)
{
    _iNbreEnreg = nE;
}

/*******************************************/
void FichierClient::Add(Client & clt)
{
    ofstream f(getNomFichier(), ios::in | ios::out | ios::binary);

    if (f.is_open())
    {
        _iNbreEnreg = recupNombreEnregistrement(getNomFichier());

        f.seekp(0, ios::beg);
        f.write((char*) &_iNbreEnreg, sizeof(int));
        f.seekp(0, ios::end);
        clt.Save(f);
        f.close();
    }
    else
        cout << "Le fichier " << getNomFichier() << " n'a pas pu s'ouvrir correctement en ecriture !" << endl;
}

void FichierClient::Load(ListeTriee<Client> &lClient)
{
    ifstream f(getNomFichier(), ios::in | ios::binary);

    if (f.is_open())
    {
        Client clt;
        int i = 0;

        f.read((char*) &_iNbreEnreg, sizeof(int));

        while (i < getNombreEnregistrement())
        {
            clt.Load(f);
            lClient.insere(clt);
            i++;
        }
    }
    f.close();
}

void FichierClient::Save(ListeTriee<Client> & lClient)
{
    ofstream f(getNomFichier(), ios::out | ios::binary | ios::trunc);
    Client clt;

    if (f.is_open())
    {
        Iterateur<Client> it(lClient);

        _iNbreEnreg = lClient.getNombreElements();

        f.seekp(0, ios::beg);
        f.write((char*) &_iNbreEnreg, sizeof(int));

        for(it.reset() ; !it.end() ; it++)
        {
            clt = (Client) it;
            clt.Save(f);
        }

        f.close();
    }
    else
        cout << "Le fichier " << getNomFichier() << " n'a pas pu s'ouvrir correctement en ecriture !" << endl;
}

void FichierClient::list()
{
    ifstream f(getNomFichier(), ios::in | ios::binary);

    f.read((char*) &_iNbreEnreg, sizeof(int));

    int i = 0;
    Client clt;

    while (i < getNombreEnregistrement())
    {
        clt.Load(f);
        clt.Affiche();
        i++;
    }

    f.close();
}

int FichierClient::recupNombreEnregistrement(const char* nF)
{
    ifstream fichierR(nF, ios::binary);

    fichierR.seekg(0, ios::beg);
    fichierR.read((char*) &_iNbreEnreg, sizeof(int));
    _iNbreEnreg++;
    fichierR.close();

    return _iNbreEnreg;
}
