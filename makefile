.SILENT:

LIB=$(HOME)/LaboC++/DOSSIER/Lib

EXEC=Concession
OBJ=$(LIB)/Personne.o $(LIB)/Employe.o $(LIB)/InvalidFonctionException.o $(LIB)/InvalidPasswordException.o $(LIB)/Date.o $(LIB)/InvalidDateException.o $(LIB)/ListeBase.o $(LIB)/ListeTriee.o $(LIB)/Liste.o $(LIB)/FichierUtilisateur.o $(LIB)/Iterateur.o $(LIB)/Option.o $(LIB)/FichierClient.o $(LIB)/Client.o $(LIB)/Modele.o $(LIB)/Voiture.o $(LIB)/Contrat.o $(LIB)/FichierContrat.o $(LIB)/InvalidRistourneException.o

CC=g++ -I$(LIB)

all: $(EXEC)

Concession:	main.cxx $(OBJ)
		echo Creation de Concession executable
		$(CC) -o Concession main.cxx $(OBJ)

$(LIB)/Employe.o:	$(LIB)/Employe.h $(LIB)/Employe.cxx $(LIB)/Personne.o $(LIB)/InvalidFonctionException.o $(LIB)/InvalidPasswordException.o
				echo Creation de Employe.o
				$(CC) -c $(LIB)/Employe.cxx -o $(LIB)/Employe.o

$(LIB)/Personne.o:	$(LIB)/Personne.h $(LIB)/Personne.cxx
				echo Creation de Personne.o
				$(CC) -c $(LIB)/Personne.cxx -o $(LIB)/Personne.o

$(LIB)/Client.o:	$(LIB)/Client.h $(LIB)/Client.cxx $(LIB)/Personne.o
				echo Creation de Client.o
				$(CC) -c $(LIB)/Client.cxx -o $(LIB)/Client.o

$(LIB)/Date.o:	$(LIB)/Date.h $(LIB)/Date.cxx $(LIB)/InvalidDateException.o
				echo Creation de Date.o
				$(CC) -c $(LIB)/Date.cxx -o $(LIB)/Date.o

$(LIB)/InvalidDateException.o:	$(LIB)/InvalidDateException.h $(LIB)/InvalidDateException.cxx
				echo Creation de InvalidDateException.o
				$(CC) -c $(LIB)/InvalidDateException.cxx -o $(LIB)/InvalidDateException.o

$(LIB)/InvalidFonctionException.o:	$(LIB)/InvalidFonctionException.h $(LIB)/InvalidFonctionException.cxx
				echo Creation de InvalidFonctionException.o
				$(CC) -c $(LIB)/InvalidFonctionException.cxx -o $(LIB)/InvalidFonctionException.o

$(LIB)/InvalidPasswordException.o:	$(LIB)/InvalidPasswordException.h $(LIB)/InvalidPasswordException.cxx
				echo Creation de InvalidPasswordException.o
				$(CC) -c $(LIB)/InvalidPasswordException.cxx -o $(LIB)/InvalidPasswordException.o

$(LIB)/InvalidRistourneException.o:	$(LIB)/InvalidRistourneException.h $(LIB)/InvalidRistourneException.cxx
				echo Creation de InvalidRistourneException.o
				$(CC) -c $(LIB)/InvalidRistourneException.cxx -o $(LIB)/InvalidRistourneException.o

$(LIB)/Contrat.o:	$(LIB)/Contrat.h $(LIB)/Contrat.cxx $(LIB)/Date.o $(LIB)/Voiture.o $(LIB)/InvalidRistourneException.o
				echo Creation de Contrat.o
				$(CC) -c $(LIB)/Contrat.cxx -o $(LIB)/Contrat.o

$(LIB)/ListeTriee.o:	$(LIB)/ListeTriee.h $(LIB)/ListeTriee.cxx $(LIB)/ListeBase.o
				echo Creation de ListeTriee.o
				$(CC) -c $(LIB)/ListeTriee.cxx -o $(LIB)/ListeTriee.o

$(LIB)/Liste.o:	$(LIB)/Liste.h $(LIB)/Liste.cxx $(LIB)/ListeBase.o
				echo Creation de Liste.o
				$(CC) -c $(LIB)/Liste.cxx	-o $(LIB)/Liste.o			

$(LIB)/ListeBase.o:	$(LIB)/ListeBase.h $(LIB)/ListeBase.cxx $(LIB)/Option.o $(LIB)/Personne.o $(LIB)/Employe.o $(LIB)/Client.o $(LIB)/Modele.o $(LIB)/Contrat.o
				echo Creation de ListeBase.o
				$(CC) -c $(LIB)/ListeBase.cxx -o $(LIB)/ListeBase.o

$(LIB)/FichierUtilisateur.o:	$(LIB)/FichierUtilisateur.h $(LIB)/FichierUtilisateur.cxx $(LIB)/Iterateur.o $(LIB)/Employe.o $(LIB)/ListeTriee.o
				echo Creation de FichierUtilisateur.o
				$(CC) -c $(LIB)/FichierUtilisateur.cxx -o $(LIB)/FichierUtilisateur.o

$(LIB)/FichierClient.o:	$(LIB)/FichierClient.h $(LIB)/FichierClient.cxx $(LIB)/Iterateur.o $(LIB)/Client.o $(LIB)/ListeTriee.o
				echo Creation de FichierClient.o
				$(CC) -c $(LIB)/FichierClient.cxx -o $(LIB)/FichierClient.o

$(LIB)/FichierContrat.o:	$(LIB)/FichierContrat.h $(LIB)/FichierContrat.cxx $(LIB)/Iterateur.o $(LIB)/Contrat.o $(LIB)/ListeTriee.o
				echo Creation de FichierContrat.o
				$(CC) -c $(LIB)/FichierContrat.cxx -o $(LIB)/FichierContrat.o

$(LIB)/Iterateur.o:	$(LIB)/Iterateur.h $(LIB)/Iterateur.cxx $(LIB)/ListeBase.o
				echo Creation de Iterateur.o
				$(CC) -c $(LIB)/Iterateur.cxx -o $(LIB)/Iterateur.o

$(LIB)/Option.o:	$(LIB)/Option.h $(LIB)/Option.cxx
				echo Creation de Option.o
				$(CC) -c $(LIB)/Option.cxx -o $(LIB)/Option.o

$(LIB)/Modele.o:	$(LIB)/Modele.h $(LIB)/Modele.cxx
				echo Creation de Modele.o
				$(CC) -c $(LIB)/Modele.cxx -o $(LIB)/Modele.o

$(LIB)/Voiture.o:	$(LIB)/Voiture.h $(LIB)/Voiture.cxx
				echo Creation de Voiture.o
				$(CC) -c $(LIB)/Voiture.cxx -o $(LIB)/Voiture.o

