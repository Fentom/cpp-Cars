#ifndef FICHIERCONTRAT_H
#define FICHIERCONTRAT_H

#include "ListeTriee.h"
#include "Contrat.h"

#include <fstream>
using namespace std;

class FichierContrat
{
    private:
        char _nomFichier[50];
        int _iNbreEnreg;
    public:
        FichierContrat();
        FichierContrat(const char* nF);
        ~FichierContrat();

        const char* getNomFichier() const;
        int getNombreEnregistrement() const;

        void setNomFichier(const char* nF);
        void setNombreEnregistrement(int nE);

        int recupNombreEnregistrement(const char* nF);
        void Add(Contrat & ctr);
        void Load(ListeTriee<Contrat> & lContrat);
        void Save(ListeTriee<Contrat> & lContrat);
        void list();
};

#endif // FICHIERCONTRAT_H
