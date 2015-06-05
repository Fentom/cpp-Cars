#include "Employe.h"
#include "Client.h"
#include "Modele.h"
#include "Option.h"
#include "Voiture.h"
#include "Contrat.h"
#include "Date.h"

#include "ListeTriee.h"
#include "Liste.h"
#include "Iterateur.h"

#include "FichierUtilisateur.h"
#include "FichierClient.h"
#include "FichierContrat.h"

#include <iostream>
#include <string>
#include <cstdlib>


#define ADMINISTRATIF 10
#define VENDEUR 20
#define QUITTER 99999


using namespace std;

void LoadOpt();
void LoadMdl();

void Pause();
int Menu(int Fct);

Employe Connexion();

void User_ChangePassword(Employe & user);
void User_Listing();
void User_Info();
void User_Add();
void User_InitPassword();

void Client_Add();
void Client_Remove();
void Client_Listing();

void Car_ListingModele();
void Car_ListingOption();
Voiture Car_NewCar();
Voiture Car_Load();
void Car_Display();
void Car_AddOption();
void Car_RemoveOption();
void Car_OptionDiscount();
void Car_Save();

void Contrat_Sumpup();
void Contrat_Add(Employe & user);
bool Contrat_Listing(Employe & user);
void Contrat_Display(Employe & user);
void Contrat_Modify(Employe & user);

ListeTriee<Employe> ListEmp;
Iterateur<Employe> itListEmp(ListEmp);

ListeTriee<Client> ListClient;
Iterateur<Client> itListClient(ListClient);

ListeTriee<Modele> ListModele;
Iterateur<Modele> itListModele(ListModele);

Liste<Option> ListOption;
Iterateur<Option> itListOption(ListOption);

ListeTriee<Contrat> ListContrat;
Iterateur<Contrat> itListContrat(ListContrat);

Voiture ProjetEnCours;

int main()
{
	Employe user;

	// On tente d'ouvrir le fichier Utilisateurs pour voir s'il existe
	fstream fc("Utilisateurs.dat", ios::in | ios::out |ios::binary);

	if(!fc.is_open())
	{	
		// Il n'existe pas, on va le bidonner
		FichierUtilisateur fUtilisateur("Utilisateurs.dat");
		fUtilisateur.Add(user); // Simple bidonnage avec le user admin-admin
	}

	fc.close();

	// Oouverture des fichiers User & clients
	FichierUtilisateur fUser("Utilisateurs.dat");
	FichierClient fClient("Clients.dat");
	FichierContrat fContrat("Contrats.dat");

	// On charge en mémoire les user & les clients & les contrats
	cout << "Chargement fichier user" << endl;
	fUser.Load(ListEmp);
	cout << "Chargement fichier client" << endl;
	fClient.Load(ListClient);
	cout << "Chargement fichier contrat" << endl;
	fContrat.Load(ListContrat);

	// On charge en mémoire les options & les modeles des voitures
	LoadMdl();
	LoadOpt();

	cout << "Chargement fini" << endl << endl << endl;
	// On recupère le user connecté
	user = Connexion();

	int fct;

	if(strcmp(user.getFonction(), "Administratif") == 0)
		fct = ADMINISTRATIF;
	else
		fct = VENDEUR;

	int choix;

	do
	{
		choix = Menu(fct);

		switch (choix)
		{
			case 0:
				User_ChangePassword(user);
			break;
			case 1:
				if (fct == ADMINISTRATIF)
				{
					User_Listing();
					Pause();
				}
				else
					Client_Add();
			break;
			case 2:
				if (fct == ADMINISTRATIF)
					User_Info();
				else
					Client_Remove();
			break;
			case 3:
				if (fct == ADMINISTRATIF)
					User_Add();
				else
				{
					Client_Listing();
					Pause();
				}
			break;
			case 4:
				if (fct == ADMINISTRATIF)
					User_InitPassword();
				else
				{
					Car_ListingModele();
					Pause();
				}
			break;
			case 5:
				if(fct == ADMINISTRATIF)
				{
					Contrat_Listing(user);
					Pause();
				}
				else
				{
					Car_ListingOption();
					Pause();
				}
			break;
			case 6:
				if(fct == ADMINISTRATIF)
					Contrat_Display(user);
				else
					ProjetEnCours = Car_NewCar();
			break;
			case 7:
				if(fct == ADMINISTRATIF)
					Contrat_Sumpup();
				else
					ProjetEnCours = Car_Load();
			break;
			case 8:
				if (fct == VENDEUR)
				{
					Car_Display();
					Pause();
				}
			break;
			case 9:
				if (fct == VENDEUR)
					Car_AddOption();
			break;
			case 10:
				if (fct == VENDEUR)
					Car_RemoveOption();
			break;
			case 11:
				if (fct == VENDEUR)
					Car_OptionDiscount();
			break;
			case 12:
				if (fct == VENDEUR)
					Car_Save();
			break;
			case 13:
				if(fct == VENDEUR)
					Contrat_Add(user);
			break;
			case 14:
				if(fct == VENDEUR)
				{
					Contrat_Listing(user);
					Pause();
				}
			break;
			case 15:
				if(fct == VENDEUR)
					Contrat_Display(user);
			break;
			case 16:
				if(fct == VENDEUR)
					Contrat_Modify(user);
			break;
		}

	} while (choix != QUITTER);


	fUser.Save(ListEmp);
	fClient.Save(ListClient);
	fContrat.Save(ListContrat);

	cout << "Sauvegarde effectuee." << endl;

	exit(0);
}

void LoadOpt() 
{
	char buff[100], code[50], intitule[70], temp[20];
	float prix;

	ifstream f("Options.csv", ios::in);

	if(f.is_open())
	{
		f.getline(buff, 100, '\n');

		while(f.peek() != EOF)
		{
			f.getline(code, 50, ';');
			f.getline(intitule, 70, ';');
			f.getline(temp, 20, '\n');
			prix = atof(temp);

			ListOption.insere(Option(code,intitule,prix));
		}
	}
	else
		cout << "Le fichier Options.csv ne s'est pas ouvert correctement" << endl;

	f.close();
}

void LoadMdl() 
{
	char nom[100], buff[100];
	int puissance;
	bool diesel;
	float prix;
	char temp[20];

	ifstream f("Modeles.csv", ios::in);

	if(f.is_open())
	{
		f.getline(buff,100,'\n');

		while(f.peek() != EOF)
		{
			f.getline(nom, 100, ';');
			f.getline(temp, 20, ';');
			puissance = atoi(temp);
			f.getline(temp, 20, ';');
			diesel = atoi(temp);
			f.getline(temp, 20, '\n');
			prix = atof(temp);

			ListModele.insere(Modele(nom, puissance, diesel, prix));
		}
	}
	else
		cout << "Le fichier Modele.csv ne s'est pas ouvert correctement" << endl;

	f.close();
}

Employe Connexion()
{
	int connected = 0;

	Employe user;

	cout << "***********************************" << endl;
	cout << "********** Bienvenue !!! **********" << endl;
	cout << "***********************************" << endl;

	char pwdbuff[80], loginbuff[80];
	int found = 0;
	int passwordinit = 1;

	while(connected == 0)
	{
		cout << "Login : ";
	    cin.getline(loginbuff, 80, '\n');

	    for (itListEmp.reset() ; !itListEmp.end() && found == 0 ; itListEmp++)
	    {
	    	user = (Employe) itListEmp;
	    	if(strcmp(user.getLogin(), loginbuff) == 0)
	    	{
	    		found = 1;

	    		if(strcmp(user.getMotDePasse(), "nopassword1" ) == 0)
	    			passwordinit = 0;
	    	}
	    }

	    if(found == 1)
	    {
	    	if(passwordinit == 0)
		    {
				User_ChangePassword(user);
				connected = 1;
		    }
		    else
		    {
				cout << "Mot de passe : ";
				cin.getline(pwdbuff, 80, '\n');

		    	if(strcmp(pwdbuff, user.getMotDePasse()) == 0)
		    		connected = 1;
			    else
			    	cout << "Il y a une erreur dans le mot de passe !" << endl;
		    }
	    }
	    else
	    	cout << "Le login n'a pa ete trouve." << endl;


	    if (connected == 1)
	    	cout << "Vous etes bien connecte !" << endl;
	}

	return user;
}

void Pause()
{
	cout << endl << "Appuyez sur entrer pour continuer...";
	cin.get();
}


int Menu(int Fct)
{
	char choice[3];

	system("clear");

	if(Fct == ADMINISTRATIF)
	{
		cout << "******************************************************" << endl;
		cout << "********** Menu Administratif ************************" << endl;
		cout << "******************************************************" << endl;
		cout << "0. Changer de mot de passe" << endl;
		cout << "Gestion des utilisateurs *****************************" << endl;
		cout << "1. Afficher la liste des utilisateurs" << endl;
		cout << "2. Afficher les infos d’un utilisateur" << endl;
		cout << "3. Créer un nouvel utilisateur" << endl;
		cout << "4. Réinitialiser le mot de passe d’un utilisateur" << endl;
		cout << "Gestion des contrats *********************************" << endl;
		cout << "5. Afficher tous les contrats" << endl;
		cout << "6. Afficher les détails d’un contrat" << endl;
		cout << "7. Afficher les contrats et le chiffre d’affaire d’un vendeur" << endl;
		cout << "Q. Quitter l’application" << endl;
	}
	else
	{
		cout << "******************************************** " << endl;
		cout << "********** Menu Vendeur ******************** " << endl;
		cout << "******************************************** " << endl;
		cout << "0. Changer de mot de passe " << endl;
		cout << "Gérer les clients ************************** " << endl;
		cout << "1. Ajouter un nouveau client " << endl;
		cout << "2. Supprimer un client " << endl;
		cout << "3. Afficher la liste des clients " << endl;
		cout << "Gérer les projets de voiture *************** " << endl;
		cout << "4. Afficher la liste des modèles " << endl;
		cout << "5. Afficher la liste des options " << endl;
		cout << "6. Nouvelle Voiture " << endl;
		cout << "7. Charger une voiture " << endl;
		cout << "8. Afficher la voiture en cours " << endl;
		cout << "9. Ajouter une option à la voiture en cours " << endl;
		cout << "10. Retirer une option à la voiture en cours " << endl;
		cout << "11. Appliquer une ristourne à une option de la voiture en cours " << endl;
		cout << "12. Enregistrer la voiture en cours " << endl;
		cout << "Gérer les contrats de vente **************** " << endl;
		cout << "13. Nouveau contrat " << endl;
		cout << "14. Afficher tous mes contrats " << endl;
		cout << "15. Afficher un contrat et le prix de vente définitif " << endl;
		cout << "16. Modifier un contrat " << endl;
		cout << "Q. Quitter l’application " << endl;
	}

	cout << endl << endl << "Votre choix : ";
	cin.getline(choice, 3, '\n');
	cout << endl;

	if(choice[0] == '\n')
		return 99;
	else
	{
		if(isalpha(choice[0]))
			return QUITTER;
		else
			return atoi(choice);
	}
}

void User_ChangePassword(Employe & user)
{
	int found = 0;
	Employe tmpEmp;

	itListEmp.reset();

	while (!itListEmp.end() && found == 0)
	{
		if (strcmp((&itListEmp).getLogin(), user.getLogin()) == 0)
			found = 1;
		else
			itListEmp++;
	}


	if (found == 1)
	{
		char pwd[80], pwdconfirmed[80];
		int good = 0;

		cout << "Votre mot de passe doit contenir au moins une lettre et un chiffre. (min: 8 caracteres)" << endl;

		while (good == 0)
		{
			try
			{
				cout << endl << "Entrez votre nouveau mot de passe : ";
				cin.getline(pwd, 80, '\n');

				tmpEmp.setMotDePasse(pwd);

				cout << "Retaper votre nouveau mot de passe : ";
				cin.getline(pwdconfirmed, 80, '\n');

				if (strcmp(pwdconfirmed, pwd) == 0)
				{
					(&itListEmp).setMotDePasse(pwd);
					good = 1;

					cout << "Votre mot de passe a bien ete modifie." << endl;
				}
				else
					cout << "Les deux mot de passe ne sont pas identiques !!" << endl;
			}
			catch (InvalidPasswordException Ex)
			{
				cout << "Mot de passe invalide. (RAISON : ";
				if (Ex.getNombre() < 8)
					cout << "trop court!)" << endl;
				else
					cout << "il ne contient pas au moins une lettre et un chiffre)" << endl;
			}
		}
	}
}

void User_Listing()
{
	cout << "Listin emp" << endl;
	if(ListEmp.getNombreElements() == 0)
		cout << "La liste des employes est vide" << endl;
	else
	{
		cout << "Voici la liste des employes : " << endl << endl;
	    for (itListEmp.reset() ; !itListEmp.end() ; itListEmp++)
	    {
	    	cout << (&itListEmp).toString() << endl;
	    }
	}
}

void User_Info()
{
	int found = 0;
	char buff[80];

	User_Listing();

	cout << endl << "Entrez le nom de l'employe a afficher : ";
	cin.getline(buff, 80, '\n');

	for(itListEmp.reset() ; !itListEmp.end() && found == 0 ; itListEmp++)
	{
		if (strcmp((&itListEmp).getNom(), buff) == 0)
		{
			(&itListEmp).Affiche();
			found = 1;
		}
	}

	if (found == 0)
		cout << "Nom inconnu." << endl;

	Pause();
}

void User_Add()
{
	int sameNumber = 0, sameLogin = 0;


	try
	{
		Employe empToAdd;

		cout << "Entrez les informations de l'employe a ajouter : " << endl << endl;
		cin >> empToAdd;

		cout << endl << "Voici l'utilisateur entre" << endl;
		empToAdd.Affiche();

		for(itListEmp.reset() ; !itListEmp.end() && (sameNumber == 0 && sameLogin == 0) ; itListEmp++)
		{
			if ((&itListEmp).getNumero() == empToAdd.getNumero())
			{
				sameNumber = 1;
				cout << "Le numero d'employe est deja utilise." << endl;
			}

			if (strcmp((&itListEmp).getLogin(), empToAdd.getLogin()) == 0)
			{
				sameLogin = 1;
				cout << "Le login n'est pas disponible." << endl;
			}
		}

		if (sameLogin == 0 && sameNumber == 0)
		{
			ListEmp.insere(empToAdd);
		}
	}
	catch(InvalidFonctionException Ex)
	{
		cout << Ex.getMessage() << endl;
	}

	Pause();
}

void User_InitPassword()
{
	char buff[80];
	int found = 0;

	User_Listing();

	cout << endl << "Entrez le login a reinitialiser : ";
	cin.getline(buff, 80, '\n');

	itListEmp.reset();

	while (!itListEmp.end() && found == 0)
	{
		if (strcmp((&itListEmp).getLogin(), buff) == 0)
			found = 1;
		else
			itListEmp++;
	}

	if (found == 1)
	{
		(&itListEmp).ResetMotDePasse();
		cout << "Le mot de passe a bien ete reinitialise." << endl;
	}
	else
		cout << "Login inconnu." << endl;

	Pause();
}

void Client_Add()
{
	int sameNumber = 0;
	Client cltToAdd;


	cout << "Entrez les informations du client a ajouter : " << endl << endl;
	cin >> cltToAdd;

	// cout << endl << "Voici le client entre" << endl;
	// cltToAdd.Affiche();

	for(itListClient.reset() ; !itListClient.end() && sameNumber == 0 ; itListClient++)
	{
		if ((&itListClient).getNumero() == cltToAdd.getNumero())
		{
			sameNumber = 1;
			cout << "Le numero de client est deja utilise." << endl;
		}
	}

	if (sameNumber == 0)
	{
		ListClient.insere(cltToAdd);
	}

	Pause();
}

void Client_Remove()
{

	if(ListClient.getNombreElements() == 0)
		cout << "La liste des clients est vide" << endl;
	else
	{
		int number, found = 0;

		Client_Listing();

		cout << endl << "Entrez le numero du client a supprimer : ";
		cin >> number;

		cin.ignore();

		itListClient.reset();

		while(!itListClient.end() && found == 0)
		{
			if((&itListClient).getNumero() == number)
				found = 1;
			else
				itListClient++;
		}

		if(found == 1)
		{
			int contratfound = 0;

			for(itListContrat.reset() ; !itListContrat.end() && contratfound == 0 ; itListContrat++)
			{
				if ((&itListContrat).getNumeroC() == number)
					contratfound = 1;
			}
			if(contratfound == 0)
			{
				itListClient.remove();
				cout << "Le client a bien ete supprime." << endl;
			}
			else
				cout << "Le client a conclus un contrat, vous ne pouvez pas le supprimer!" << endl;
		}
		else
			cout << "Numero inconnu." << endl;
	}

	Pause();
}

void Client_Listing()
{
	if(ListClient.getNombreElements() == 0)
		cout << "La liste des clients est vide" << endl;
	else
	{
		cout << "Voici la liste des clients : " << endl << endl;
	    for (itListClient.reset() ; !itListClient.end() ; itListClient++)
	    {
	    	cout << (&itListClient).toString() << endl;
	    }
	}
}

void Car_ListingModele()
{
	int count = 1;

	if(ListModele.getNombreElements() == 0)
		cout << "La liste des modeles est vide" << endl;
	else
	{
		cout << "Voici la liste des modeles : " << endl << endl;
	    for (itListModele.reset() ; !itListModele.end() ; itListModele++)
	    {
	    	cout << count << ". " << (&itListModele).toString() << endl;
	    	count++;
	    }
	}
}


void Car_ListingOption()
{
	if(ListOption.getNombreElements() == 0)
		cout << "La liste des options est vide" << endl;
	else
	{
		cout << "Voici la liste des options : " << endl << endl;
	    for (itListOption.reset() ; !itListOption.end() ; itListOption++)
	    {
	    	cout << (&itListOption).toString() << endl;
	    }
	}
}

Voiture Car_NewCar()
{
	Voiture v;
	int number, i = 1;

	char buff[80];

	cout << "Entrez le nom du projet : ";
	cin.getline(buff, 80, '\n');

	v.setNom(buff);

	Car_ListingModele();
	cout << endl << "Numero du modele choisi : ";
	cin >> number;

	cin.ignore();

	if (number < 1 || number > 24)
		cout << "Modele inconnu." << endl;
	else
	{
		itListModele.reset();
		while (!itListModele.end() && i < number)
		{
			itListModele++;
			i++;
		}

		v.setModele((&itListModele));

		cout << "Projet cree avec succes." << endl;

		Pause();

		return v;
	}

	Pause();
}

Voiture Car_Load()
{
	Voiture v;
	char buff[80];

	cout << "Entrez le nom du projet a charger : ";
	cin.getline(buff, 80, '\n');

	strcat(buff, ".car");
	v.Load(buff);

	if (strcmp(v.getNom(), "DEFAULT") != 0)
		cout << "Voiture charge avec succes." << endl;

	Pause();

	return v;
}

void Car_Display()
{
	if (strcmp(ProjetEnCours.getNom(), "DEFAULT") == 0)
		cout << "Vous n'avez pas de voiture en cours." << endl;
	else
		ProjetEnCours.Affiche();
}

void Car_AddOption()
{
	if (strcmp(ProjetEnCours.getNom(), "DEFAULT") == 0)
		cout << "Vous n'avez pas de voiture en cours." << endl;
	else
	{
		Car_ListingOption();

		char buff[80];
		int found = 0;

		cout << endl << "Entrez le code de l'option a ajouter : ";
		cin.getline(buff, 80, '\n');

		itListOption.reset();
		while(!itListOption.end() && found == 0) 
		{
		    if (strcmp((&itListOption).getCode(), buff) == 0)
		    	found = 1;
		    else
		    	itListOption++;
		}

		if (found == 1)
		{
			ProjetEnCours.AjouteOption((Option)itListOption);
			cout << "L'option a ete ajoutee avec succes." << endl;
		}
		else
			cout << "Option inconnue." << endl;

	}

	Pause();
}

void Car_RemoveOption()
{
	if (strcmp(ProjetEnCours.getNom(), "DEFAULT") == 0)
		cout << "Vous n'avez pas de voiture en cours." << endl;
	else
	{
		if(&(ProjetEnCours.getOption(0)) == NULL)
			cout << "Vous n'avez pas d'option dans votre voiture actuelle." << endl;
		else
		{
			Car_Display();

			char buff[80];
			int found = 0;

			cout << endl << "Entrez le code de l'option a retirer : ";
			cin.getline(buff, 80, '\n');

			ProjetEnCours.RetireOption(buff);
		}
	}

	Pause();
}

void Car_OptionDiscount()
{
	if (strcmp(ProjetEnCours.getNom(), "DEFAULT") == 0)
		cout << "Vous n'avez pas de voiture en cours." << endl;
	else
	{
		if(&(ProjetEnCours.getOption(0)) == NULL)
			cout << "Vous n'avez pas d'option dans votre voiture actuelle." << endl;
		else
		{
			Car_Display();

			char buff[80];
			int found = 0;

			cout << endl << "Entrez le code de l'option a reduire : ";
			cin.getline(buff, 80, '\n');

			for (int i = 0 ; i < 10 && found == 0 ; ++i)
			{
				if (&(ProjetEnCours.getOption(i)) != NULL)
				{
					if (strcmp(ProjetEnCours.getOption(i).getCode(), buff) == 0)
					{
						found = 1;

						if(ProjetEnCours.getOption(i).getPrix() == 50)
							cout << "L'option est deja pas tres chere!!" << endl;
						else
						{
							--(ProjetEnCours.getOption(i));
							cout << "Ristourne appliquee avec succes." << endl;
						}
					}
				}
			}

			if(found == 0)
				cout << "Option inconnue" << endl;
		}
 	}

	Pause();
}

void Car_Save()
{
	if (strcmp(ProjetEnCours.getNom(), "DEFAULT") == 0)
		cout << "Vous n'avez pas de voiture en cours." << endl;
	else
	{
		ProjetEnCours.Save();
		cout << "Projet sauvegarde avec succes" << endl;
	}

	Pause();
}

void Contrat_Sumpup()
{
	char buff[30];
	int numVendeur, found = 0, not_a_seller = 0;

	User_Listing();

	cout << endl << "Entrez le nom du vendeur : ";
	cin.getline(buff, 80, '\n');

	itListEmp.reset();
	while(!itListEmp.end() && found == 0)
	{
		if (strcmp((&itListEmp).getNom(), buff) == 0)
		{
			found = 1;

			if (strcmp((&itListEmp).getFonction(), "Administratif") == 0)
				not_a_seller = 1;
		}
		else
			itListEmp++;
	}
	if(found == 1 && not_a_seller == 0)
	{
		numVendeur = (&itListEmp).getNumero();

		Employe tmpEmp;
		tmpEmp = (Employe)itListEmp;

		if(Contrat_Listing(tmpEmp))
		{
			float benef = 0;

			for(itListContrat.reset() ; !itListContrat.end() ; itListContrat++)
			{
				if ((&itListContrat).getNumeroV() == numVendeur)
					benef = benef + ((&itListContrat).getVoiture().getPrix() - (&itListContrat).getRistourne());
			}

			cout << endl << "Chiffre d'affaire: " << benef << " eur" << endl;
		}
	}
	else
		if (not_a_seller == 1)
			cout << "Cet employe n'est pas un vendeur." << endl;
		else
			cout << "Nom inconnu." << endl;

	Pause();
}

void Contrat_Add(Employe & user)
{
	int numberC, ristourne, found = 0;

	Client_Listing();

	cout << endl << "Entrez le numero du client : ";
	cin >> numberC;

	cin.ignore();


	itListClient.reset();

	while(!itListClient.end() && found == 0)
	{
		if((&itListClient).getNumero() == numberC)
			found = 1;
		else
			itListClient++;
	}

	if(found == 1)
	{
		try
		{
			Date tmpDate;

			cout << "Entrez la date du contrat : " << endl;
			cin >> tmpDate;

			Voiture tmpV;
			char buff[80];

			cout << endl << "Entrez le nom du projet : ";
			cin.getline(buff, 80, '\n');

			strcat(buff, ".car");

			tmpV.Load(buff);

			if (strcmp(tmpV.getNom(), "DEFAULT") != 0)
			{
				cout << "Voiture charge avec succes." << endl;

				cout << "Entrez une ristourne : ";
				cin >> ristourne;

				Contrat tmpC(ListContrat.getNombreElements()+1, user.getNumero(), numberC, tmpDate, tmpV, ristourne);
				ListContrat.insere(tmpC);
			}
		}
		catch(InvalidDateException Ex)
		{
			cout << Ex.getMessage();
		}
		catch(InvalidRistourneException Ex)
		{
			cout << Ex.getMessage();
		}
	}
	else
		cout << "Numero inconnu." << endl;

	Pause();
}

bool Contrat_Listing(Employe & user)
{
	int numclient = 0, found = 0;

	if(ListContrat.getNombreElements() == 0)
		cout << "La liste des contrats est vide" << endl;
	else
	{
		for (itListContrat.reset() ; !itListContrat.end() ; itListContrat++)
		{
			if(strcmp(user.getFonction(), "Vendeur") == 0)
			{
				if((&itListContrat).getNumeroV() == user.getNumero())
					found = 1;
			}
			else
				found = 1;
		}
		if (found == 1)	
		{
			cout << "Voici la liste des contrats" << endl << endl;

		    for (itListContrat.reset() ; !itListContrat.end() ; itListContrat++)
		    {
		    	if(strcmp(user.getFonction(), "Vendeur") == 0)
		    	{
			    	if((&itListContrat).getNumeroV() == user.getNumero())
			    	{
			    		numclient = (&itListContrat).getNumeroC();
			    		itListClient.reset();

			    		while((&itListClient).getNumero() != numclient)
			    			itListClient++;

			    		cout << (&itListContrat).getNumero() << " :Num. Contrat | Client : " << (&itListClient).getNom() << " " << (&itListClient).getPrenom() << " | Prix final: " << (&itListContrat).getVoiture().getPrix() - (&itListContrat).getRistourne() << endl;
			    	}
		    	}
		    	else
		    	{
					numclient = (&itListContrat).getNumeroC();
		    		itListClient.reset();

		    		while((&itListClient).getNumero() != numclient)
		    			itListClient++;

		    		cout << (&itListContrat).getNumero() << " :Num. Contrat | Client : " << (&itListClient).getNom() << " " << (&itListClient).getPrenom() << " | Prix final: " << (&itListContrat).getVoiture().getPrix() - (&itListContrat).getRistourne() << endl;
		    	}
		    }

		    return true;
		}
		else
		{
			cout << "Aucun contrat actuellement conlu." << endl;
			return false;
		}
	}

	return false;
}

void Contrat_Display(Employe & user)
{
	if(Contrat_Listing(user))
	{
		int number, found = 0;

		cout << endl << "Entrez le numero du contrat a afficher : ";
		cin >> number;

		cin.ignore();

		for (itListContrat.reset() ; !itListContrat.end() && found == 0; itListContrat++)
		{
			if ((&itListContrat).getNumero() == number)
			{
				if(strcmp(user.getFonction(), "Vendeur") == 0)
				{
					if ((&itListContrat).getNumeroV() == user.getNumero())
					{
						found = 1;
						(&itListContrat).Affiche();
					}
					else
					{
						found = 1;
						cout << "Vous ne pouvez pas afficher ce contrat!" << endl;
					}
				}
				else
				{
					found = 1;
					(&itListContrat).Affiche();	
				}
			}
		}

		if (found == 0)
			cout << "Numero inconnu." << endl;
	}

	Pause();
}
void Contrat_Modify(Employe & user)
{
	if(Contrat_Listing(user))
	{
		int number, found = 0;

		cout << endl << "Entrez le numero du contrat a modifier : ";
		cin >> number;

		cin.ignore();

		for (itListContrat.reset() ; !itListContrat.end() && found == 0; itListContrat++)
		{
			if ((&itListContrat).getNumero() == number)
			{
				found = 1;

				if ((&itListContrat).getNumeroV() == user.getNumero())
				{
					int choix = 0;
					(&itListContrat).Affiche();

					cout << "Que souhaitez vous modifier?" << endl << endl;
					cout << "1. La ristourne" << endl;
					cout << "2. Le modele" << endl;
					do
					{
						cout << "Votre choix: ";
						cin >> choix;
					} while (choix < 1 || choix > 2);

					cin.ignore();

					if(choix == 1)
					{
						try
						{
							float rist;
							cout << endl << "Entrez une nouvelle ristourne: ";
							cin >> rist;

							cin.ignore();

							(&itListContrat).setRistourne(rist);
							cout << "Le contrat a bien ete modifie." << endl;
						}
						catch(InvalidRistourneException Ex)
						{
							cout << Ex.getMessage();
						}
					}
					else
					{
						char buff[80];
						Voiture tmpV;

						cout << "Entrez le nom du projet a charger : ";
						cin.getline(buff, 80, '\n');
						strcat(buff, ".car");

						tmpV.Load(buff);

						if (strcmp(tmpV.getNom(), "DEFAULT") != 0)
						{
							(&itListContrat).setVoiture(tmpV);
							cout << "Le contrat a bien ete modifie." << endl;
						}					
					}
				}
				else
				{
					found = 1;
					cout << "Vous ne pouvez pas modifier ce contrat." << endl;
				}
			}
		}

		if (found == 0)
			cout << "Numero inconnu." << endl;

	}

	Pause();
}
