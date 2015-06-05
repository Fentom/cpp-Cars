#ifndef FICHIERUTILISATEUR_H
#define FICHIERUTILISATEUR_H

#include "ListeTriee.h"
#include "Employe.h"

#include <fstream>
using namespace std;

class FichierUtilisateur
{
    private:
        char _nomFichier[50];
        int _iNbreEnreg;
    public:
        FichierUtilisateur();
        FichierUtilisateur(const char* nF);
        ~FichierUtilisateur();

        const char* getNomFichier() const;
        int getNombreEnregistrement() const;

        void setNomFichier(const char* nF);
        void setNombreEnregistrement(int nE);

        int recupNombreEnregistrement(const char* nF);
        void Add(Employe & emp);
        void Load(ListeTriee<Employe> & lEmploye);
        void Save(ListeTriee<Employe> & lEmploye);
        void list();
};

#endif // FICHIERUTILISATEUR_H
