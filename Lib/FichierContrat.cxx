#include "FichierContrat.h"
#include "ListeTriee.h"
#include "Contrat.h"
#include "Iterateur.h"

#include <string.h>
#include <iostream>

using namespace std;

FichierContrat::FichierContrat()
{
    setNomFichier("Contrats.dat");

    fstream f(getNomFichier(), ios::in | ios::out | ios::binary);
    if (!f.is_open())
    {
        setNombreEnregistrement(0);
        f.open(getNomFichier(), ios::out | ios::app | ios::binary);
        f.write((char*) &_iNbreEnreg, sizeof(int));
    }

    f.close();
}

FichierContrat::FichierContrat(const char* nF)
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

FichierContrat::~FichierContrat()
{

}

const char* FichierContrat::getNomFichier() const
{
    return _nomFichier;
}

int FichierContrat::getNombreEnregistrement() const
{
    return _iNbreEnreg;
}

void FichierContrat::setNomFichier(const char* nF)
{
    if (strlen(nF) < 50)
        strcpy(_nomFichier, nF);
}

void FichierContrat::setNombreEnregistrement(int nE)
{
    _iNbreEnreg = nE;
}

/*******************************************/
void FichierContrat::Add(Contrat & ctr)
{
    ofstream f(getNomFichier(), ios::in | ios::out | ios::binary);

    if (f.is_open())
    {
        _iNbreEnreg = recupNombreEnregistrement(getNomFichier());

        f.seekp(0, ios::beg);
        f.write((char*) &_iNbreEnreg, sizeof(int));
        f.seekp(0, ios::end);
        ctr.Save(f);
        f.close();
    }
    else
        cout << "Le fichier " << getNomFichier() << " n'a pas pu s'ouvrir correctement en ecriture !" << endl;
}

void FichierContrat::Load(ListeTriee<Contrat> &lContrat)
{
    ifstream f(getNomFichier(), ios::in | ios::binary);

    if (f.is_open())
    {
        Contrat ctr;
        int i = 0;

        f.read((char*) &_iNbreEnreg, sizeof(int));

        while (i < getNombreEnregistrement())
        {
            ctr.Load(f);
            lContrat.insere(ctr);
            i++;
        }
    }
    f.close();
}   

void FichierContrat::Save(ListeTriee<Contrat> & lContrat)
{
    ofstream f(getNomFichier(), ios::out | ios::binary | ios::trunc);
    Contrat ctr;

    if (f.is_open())
    {
        Iterateur<Contrat> it(lContrat);

        _iNbreEnreg = lContrat.getNombreElements();

        f.seekp(0, ios::beg);
        f.write((char*) &_iNbreEnreg, sizeof(int));

        for(it.reset() ; !it.end() ; it++)
        {
            cout << "Sauvegarde contrat in file" << endl;
            ctr = (Contrat) it;
            ctr.Save(f);
        }

        f.close();
    }
    else
        cout << "Le fichier " << getNomFichier() << " n'a pas pu s'ouvrir correctement en ecriture !" << endl;
}

void FichierContrat::list()
{
    ifstream f(getNomFichier(), ios::in | ios::binary);

    f.read((char*) &_iNbreEnreg, sizeof(int));

    int i = 0;
    Contrat ctr;

    while (i < getNombreEnregistrement())
    {
        ctr.Load(f);
        ctr.Affiche();
        i++;
    }

    f.close();
}

int FichierContrat::recupNombreEnregistrement(const char* nF)
{
    ifstream fichierR(nF, ios::binary);

    fichierR.seekg(0, ios::beg);
    fichierR.read((char*) &_iNbreEnreg, sizeof(int));
    _iNbreEnreg++;
    fichierR.close();

    return _iNbreEnreg;
}
