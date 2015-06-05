#include "FichierUtilisateur.h"
#include "ListeTriee.h"
#include "Employe.h"
#include "Iterateur.h"

#include <string.h>
#include <iostream>

using namespace std;

FichierUtilisateur::FichierUtilisateur()
{
    setNomFichier("Utilisateurs.dat");

    fstream f(getNomFichier(), ios::in | ios::out | ios::binary);
    if (!f.is_open())
    {
        setNombreEnregistrement(0);
        f.open(getNomFichier(), ios::out | ios::app | ios::binary);
        f.write((char*) &_iNbreEnreg, sizeof(int));
    }

    f.close();
}

FichierUtilisateur::FichierUtilisateur(const char* nF)
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

FichierUtilisateur::~FichierUtilisateur()
{

}

const char* FichierUtilisateur::getNomFichier() const
{
    return _nomFichier;
}

int FichierUtilisateur::getNombreEnregistrement() const
{
    return _iNbreEnreg;
}

void FichierUtilisateur::setNomFichier(const char* nF)
{
    if (strlen(nF) < 50)
        strcpy(_nomFichier, nF);
}

void FichierUtilisateur::setNombreEnregistrement(int nE)
{
    _iNbreEnreg = nE;
}

/*******************************************/
void FichierUtilisateur::Add(Employe & emp)
{
    ofstream f(getNomFichier(), ios::in | ios::out | ios::binary);

    if (f.is_open())
    {
        _iNbreEnreg = recupNombreEnregistrement(getNomFichier());

        f.seekp(0, ios::beg);
        f.write((char*) &_iNbreEnreg, sizeof(int));
        f.seekp(0, ios::end);
        emp.Save(f);
        f.close();
    }
    else
        cout << "Le fichier " << getNomFichier() << " n'a pas pu s'ouvrir correctement en ecriture !" << endl;
}

void FichierUtilisateur::Load(ListeTriee<Employe> &lEmploye)
{
    ifstream f(getNomFichier(), ios::in | ios::binary);

    if (f.is_open())
    {
        Employe emp;
        int i = 0;

        f.read((char*) &_iNbreEnreg, sizeof(int));

        while (i < getNombreEnregistrement())
        {
            emp.Load(f);
            lEmploye.insere(emp);
            i++;
        }
    }
    f.close();
}

void FichierUtilisateur::Save(ListeTriee<Employe> & lEmploye)
{
    ofstream f(getNomFichier(), ios::out | ios::binary | ios::trunc);
    Employe user;

    if (f.is_open())
    {
        Iterateur<Employe> it(lEmploye);

        _iNbreEnreg = lEmploye.getNombreElements();

        f.seekp(0, ios::beg);
        f.write((char*) &_iNbreEnreg, sizeof(int));

        for(it.reset() ; !it.end() ; it++)
        {
            user = (Employe) it;
            user.Save(f);
        }

        f.close();
    }
    else
        cout << "Le fichier " << getNomFichier() << " n'a pas pu s'ouvrir correctement en ecriture !" << endl;
}

void FichierUtilisateur::list()
{
    ifstream f(getNomFichier(), ios::in | ios::binary);

    f.read((char*) &_iNbreEnreg, sizeof(int));

    int i = 0;
    Employe emp;

    while (i < getNombreEnregistrement())
    {
        emp.Load(f);
        emp.Affiche();
        i++;
    }

    f.close();
}

int FichierUtilisateur::recupNombreEnregistrement(const char* nF)
{
    ifstream fichierR(nF, ios::binary);

    fichierR.seekg(0, ios::beg);
    fichierR.read((char*) &_iNbreEnreg, sizeof(int));
    _iNbreEnreg++;
    fichierR.close();

    return _iNbreEnreg;
}
