#include "fonctions.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <time.h>
using namespace std;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
Fonctions::Fonctions()/*Initialisation des tableaux Argent, Nom_du_livre[0] et Equipements*/
{
    int I;
    int J;
    Nom_du_livre[0] = {'*'};/*Initialisation de la première case du tableau Nom_du_livre qui servira pour les vérifications dans l'IHM*/
    for(I=0;I<4;I++)
    {
        Argent[I] = 0;/*Initialisation du tableau Argent pour qu'il soit a 0*/
    }
    for(I=0;I<11;I++)
    {
        for (J=0;J<11;J++)
        {
            Equipements[I][J] = 0;/*Initialisation du tableau Equipement a 0 pour des vérifications dans la création de la fiche perso*/
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Nom_livre()/*Saisie du nom du livre et création d'un répertoire du même nom avec les droits 0777(notation base 8)*/
{
    system("clear");
    cout<<"Quel est le nom du livre dont vous essayez de résoudre l’énigme ? : ";
    cin.getline(Nom_du_livre,50);/*Récupération du Nom du livre*/
    mkdir(Nom_du_livre,0777);/*Création du répertoire*/
    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Infos_personnages()/*Saisie du nom et d'informations sur un personnage dans un document*/
{
    system("clear");
    char Name[70] = "./";/*Permet de créer le fichier sous le nom de type <Nom du livre>-Repertoire-des-noms.odt*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-Repertoire-des-noms.odt");
    fstream fichier(Name, ios::out|ios::app);/*Création du fichier et écriture dans celui-ci*/

            if(fichier)
            {
                    cout<<"Quel est le nom du personnage ? : ";
                    cin.getline(Nom_Perso,50);/*Récupération du nom du personnage*/
                    fichier << Nom_Perso <<" :\n";/*Écriture du Nom dans le fichier*/
                    cout<<"Quelles informations avez-vous sur "<< Nom_Perso <<" : ";
                    cin.getline(Infos,200);/*Récupération des informations*/
                    fichier <<Infos<<"\n---------------------------------------------------------------------\n";/*Écriture des informations dans le fichier*/
                    fichier.close();/*Fermeture du fichier*/
            }
            else
                    cerr << "Impossible d'ouvrir le fichier !" << endl;

    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de selection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Indices_deductions()/*Saisie d'indices et déductions dans un document*/
{
    system("clear");
    char Texte[100];/*Tampon du texte*/
    char Sauvegarde_avant[100][100];/*Sauvegarde des lignes avant la ligne qui nous intéresse*/
    char Sauvegarde_apres[100][400];/*Sauvegarde des lignes après la ligne qui nous intéresse*/
    char Doc_complet[1000];/*Tampon du document complet*/
    int Total = 0;/*Contiens le nombre de caractères du document complet*/
    int Taille = 0;/*Contiens le nombre de caractères de chaque ligne*/
    int Tampon = 0;/*Tampon du nombre de caractères de chaque ligne individuelle*/
    int taille_avant = 0;/*contiens le nombre de lignes avant la ligne qui nous intéresse*/
    int taille_apres = 0;/*contiens le nombre de lignes après la ligne qui nous intéresse*/
    int nblignes = 0;/*contiens le nombre de lignes total du document*/
    int Choix;
    int I;
    int Page = 0;
    char Lettre = '\0';
    char Name[200] = "./";/*Permet d’écrire le calepin dont le nom est indiqué*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    fstream fichier;/*Ouverture du fichier*/
    cout<<"Ce que vous voulez noter c'est \n1 : Un indice\n2 : Une déduction \nMon choix : ";
    cin>>Choix;
    getchar();
    if(Choix==1)
    {
            if(fichier)
            {
                cout<<"Quelle est la lettre de l'indice ?\nC'est : ";
                cin>>Lettre;
                Numero = Comparaison(Lettre);
                getchar();
                cout<<"Que dit cet indice ?\nIl dit : ";
                cin.getline(Indices,1000);
                cout<<"À quelle page se trouve cet indice ?\nC'est à la page N° : ";
                cin>>Page;
                getchar();
                strcat (Name,"-calepin-indice.odt");
            }
            else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
      }

    if(Choix==2)
    {
            if(fichier)
            {
                cout<<"Quel est le numéro de la déduction ?\nC'est : ";
                cin>>Numero;
                Numero = Numero - 1;
                getchar();
                cout<<"Quelle est votre déduction ?"<<" : ";
                cin.getline(Indices,1000);/*Récupération de l'indice*/
                cout<<"À quelle page se trouve cet indice ?\nC'est à la page N° : ";
                cin>>Page;
                getchar();
                strcat (Name,"-calepin-deductions.odt");
            }
            else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
      }
    //-------------------------------------------------------------//
    fichier.open(Name,ios::in);//Ouverture du fichier en lecture (retour au début du fichier)
    while(fichier.getline(Doc_complet,1000))//Lecture entière du fichier pour savoir le nombre total de lignes et de caractères
    {
        Tampon = strlen(Doc_complet);//Calcul du nombre de caractères de la ligne
        Total = Total + Tampon;//Calcul du total de caractère
        nblignes++;//Ajout d'une ligne par cycle
    }
    fichier.close();//Fermeture du fichier
    //-------------------------------------------------------------//
    fichier.open(Name,ios::in);//Ouverture du fichier en lecture (retour au début du fichier)
    Tampon = 0;//Initialisation du Tampon à 0
    for(I=0;I<Numero;I++)//Calcule le nombre de ligne qui se trouvent avant la ligne "cible" et stock les lignes dans Sauvegarde_avant
    {
        fichier.getline(Texte,100);//Obtention d'une ligne dans Texte
        Tampon = strlen(Texte);//Calcul du nombre de caractères de la ligne
        Taille = Tampon + Taille + 1;//Calculer le nombre total de caractères avant la ligne "cible"
        strcpy(Sauvegarde_avant[I],Texte);//Permet de copier le contenu de Texte dans Sauvegarde_avant pour sauvegarder le texte avant la ligne "cible"
        taille_avant++;//Ajoute 1 au compteur de lignes
    }
    taille_apres = nblignes - taille_avant;//Calcul du nombre de ligne qu'il reste après la ligne "cible"
    fichier.seekg(Taille,ios::beg);//Place le curseur de lecture a l'emplacement de la ligne "cible"

    fichier.close();//fermeture du fichier
    //-------------------------------------------------------------//
    fichier.open(Name,ios::in);//Ouverture du fichier en lecture (retour au début du fichier)
    fichier.seekg(Taille,ios::beg);//Place le curseur de lecture a l'emplacement de la ligne "cible"
    for(I=0;I<taille_apres;I++)//Calcule le nombre de ligne qui se trouvent après la ligne "cible" et stock les lignes dans Sauvegarde_apres
    {
        fichier.getline(Texte,100);//Obtention d'une ligne dans Texte
        Tampon = strlen(Texte);//Calcul du nombre de caractères de la ligne
        Taille = Tampon + Taille + 1;//Calculer le nombre total de caractères après la ligne "cible"
        strcpy(Sauvegarde_apres[I],Texte);//Permet de copier le contenu de Texte dans Sauvegarde_apres pour sauvegarder le texte après la ligne "cible"
    }
    fichier.close();/*Fermeture du fichier*/
//----------------------Écriture---------------------------------//
    fichier.open(Name,ios::out);//ouverture du fichier en écriture
    for(I=0;I<taille_avant;I++)//Écriture des lignes avant la ligne "cible"
    {
        fichier<<Sauvegarde_avant[I]<<"\n";//Écriture de chaque ligne
    }
    if (Choix == 1)
    {
        fichier<<Lettre<<") "<<Indices<<" (Page N°"<<Page<<")";//Écriture de la ligne "cible"
    }
    if (Choix == 2)
    {
        fichier<<Numero+1<<") "<<Indices<<" (Page N°"<<Page<<")";//Écriture de la ligne "cible"
    }
    for(I=0;I<taille_apres;I++)//Écriture des lignes après la ligne "cible"
    {
        fichier<<Sauvegarde_apres[I]<<"\n";//Écriture de chaque ligne
    }
    fichier.close();
    cout<<"Sauvegarde terminer\n";
    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
int Fonctions::Comparaison(char Lettre)
{
    int resultat = 0;
    switch(Lettre)
    {
    case 'A':
        resultat = 0;
    case 'a':
        resultat = 0;
        break;
    case 'B':
        resultat = 1;
    case 'b':
        resultat = 1;
        break;
    case 'C':
        resultat = 2;
    case 'c':
        resultat = 2;
        break;
    case 'D'|'d':
        resultat = 3;
        break;
    case 'E':
        resultat = 4;
    case 'e':
        resultat = 4;
        break;
    case 'F':
        resultat = 5;
    case 'f':
        resultat = 5;
        break;
    case 'G':
        resultat = 6;
    case 'g':
        resultat = 6;
        break;
    case 'H':
        resultat = 7;
    case 'h':
        resultat = 7;
        break;
    case 'I':
        resultat = 8;
    case 'i':
        resultat = 8;
        break;
    case 'J':
        resultat = 9;
    case 'j':
        resultat = 9;
        break;
    case 'K':
        resultat = 10;
    case 'k':
        resultat = 10;
        break;
    case 'L':
        resultat = 11;
    case 'l':
        resultat = 11;
        break;
    case 'M':
        resultat = 12;
    case 'm':
        resultat = 12;
        break;
    case 'N':
        resultat = 13;
    case 'n':
        resultat = 13;
        break;
    case 'O':
        resultat = 14;
    case 'o':
        resultat = 14;
        break;
    case 'P':
        resultat = 15;
    case 'p':
        resultat = 15;
        break;
    case 'Q':
        resultat = 16;
    case 'q':
        resultat = 16;
        break;
    case 'R':
        resultat = 17;
    case 'r':
        resultat = 17;
        break;
    case 'S':
        resultat = 18;
    case 's':
        resultat = 18;
        break;
    case 'T':
        resultat = 19;
    case 't':
        resultat = 19;
        break;
    case 'U':
        resultat = 20;
    case 'u':
        resultat = 20;
        break;
    case 'V':
        resultat = 21;
    case 'v':
        resultat = 21;
        break;
    case 'W':
        resultat = 22;
    case 'w':
        resultat = 22;
        break;
    case 'X':
        resultat = 23;
    case 'x':
        resultat = 23;
        break;
    case 'Y':
        resultat = 24;
    case 'y':
        resultat = 24;
        break;
    case 'Z':
        resultat = 25;
    case 'z':
        resultat = 25;
        break;
    }
    return resultat;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Lancer_de_de()/*Simule un lancer de dé*/
{
    int Nbde,I;/*Nbde permet d'indiquer le nombre de dé et I permet les for*/
    int Somme = 0;/*Variable qui contera la somme des valeurs des dés*/
    int *val;/*Indiquera la valeur de chaque dé*/
    system("clear");/*Permet d'effacer l’écran*/
    srand(time(NULL));/*Permet de remettre l'horloge a zéro*/
    cout<<"Combien de dés voulez vous lancer ? : ";
    cin>>Nbde;
    getchar();
    val = new int[Nbde];/*Permet de gérer le nombre de dé qui sont lancer*/
    for (I=0;I<Nbde;I++)
    {
        val[I] = rand() % 6+1;/*Enregistre les valeurs dans le tableau*/
        Somme = Somme + val[I];/*S'incrémente à chaque passage*/
    }
    if (Nbde==1)
    {
            cout<<"Pressez la touche entrer pour lancer le dé\n";/*Affiche le mot dé au singulier s’il y en a qu'un*/

    }
    else
    {
            cout<<"Pressez la touche entrer pour lancer les "<<Nbde<<" dés\n";/*Affiche le nombre de dés*/
    }
    getchar();
    system("aplay -q Dé.wav");/*Permet de jouer un bruit de dé*/
    for (I=0;I<Nbde;I++)/*Affichage des valeurs et de la somme*/
    {
        cout<<"Votre dé n°"<<I+1<<" indique "<<val[I]<<"\n";
        switch (val[I])/*Permet d'afficher un dé en ASCII en fonction de sa valeur*/
        {
        case 1:/*Affiche un dé qui indique 1*/
            cout<<"╔═════════════════╗\n║                 ║\n║                 ║\n║                 ║\n║        _        ║\n║       (_)       ║\n║                 ║\n║                 ║\n║                 ║\n╚═════════════════╝\n\n";break;
        case 2:/*Affiche un dé qui indique 2*/
            cout<<"╔═════════════════╗\n║               _ ║\n║              (_)║\n║                 ║\n║                 ║\n║                 ║\n║ _               ║\n║(_)              ║\n║                 ║\n╚═════════════════╝\n\n";break;
        case 3:/*Affiche un dé qui indique 3*/
            cout<<"╔═════════════════╗\n║               _ ║\n║              (_)║\n║                 ║\n║         _       ║\n║        (_)      ║\n║                 ║\n║ _               ║\n║(_)              ║\n║                 ║\n╚═════════════════╝\n\n";break;
        case 4:/*Affiche un dé qui indique 4*/
            cout<<"╔═════════════════╗\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n║                 ║\n║                 ║\n║                 ║\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n╚═════════════════╝\n\n";break;
        case 5:/*Affiche un dé qui indique 5*/
            cout<<"╔═════════════════╗\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n║        _        ║\n║       (_)       ║\n║                 ║\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n╚═════════════════╝\n\n";break;
        case 6:/*Affiche un dé qui indique 6*/
            cout<<"╔═════════════════╗\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n║ _             _ ║\n║(_)           (_)║\n║                 ║\n╚═════════════════╝\n\n";break;
        }
    }
    cout<<"Ce qui fait au total "<<Somme<<"\n";/*Affichage de la somme des dés*/

    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Lecture_Repertoire_des_noms()/*Lecture du fichier dans lequel sont les noms*/
{
    system("clear");
    char Name[70] = "./";/*Permet de lire le répertoire des noms dont le nom est indiqué*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-Repertoire-des-noms.odt");
    fstream fichier(Name);/*Ouverture du fichier*/
    if(fichier)
    {
        string ligne {};
        cout<<"Répertoire des noms du livre : ~"<<Nom_du_livre<<"~\n";/*Affiche le nom du livre*/
        while(getline(fichier, ligne))
        {
            cout << ligne << endl;/*Affiche le contenu du fichier*/
        }
    }
    else
    {
        cout << "ERREUR il y a pas de répertoire fait pour ce livre commencez en un." << endl;
    }

    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de selection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Lecture_Calepin()/*Lecture du fichier où sont les indices et déductions*/
{
    system("clear");
    int Choix;
    char Name[70] = "./";/*Permet d’écrire le calepin dont le nom est indiqué*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    cout<<"Voulez-vous lire le calepin\n1) des Indices\n2) des Déductions\nMon choix : ";
    cin>>Choix;
    getchar();
    if(Choix == 1)
    {
        strcat (Name,"-calepin-indice.odt");
    }
    if(Choix == 2)
    {
        strcat (Name,"-calepin-deductions.odt");
    }
    fstream fichier(Name);/*Ouverture du fichier*/
    if(fichier)
    {
        string ligne {};
        cout<<"Calepin du livre : ~"<<Nom_du_livre<<"~\n";/*Affiche le nom du livre*/
        while(getline(fichier, ligne))
        {
            cout << ligne << endl;/*Affiche le contenu du fichier*/
        }
    }
    else
    {
        cout << "ERREUR il y a pas de calepin fait pour ce livre commencez un.\n";
    }

    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Creation_fiche_perso()/*Création de la fiche personnage*/
{
    char Nom_Aptitudes[6][20] = {{"Force"},{"Habileté"},{"Intuition"},{"Éducation"},{"Observation"},{"Connaissance"}};/*Permet d'afficher le nom de chaque aptitude*/
    char Nom_Monnaies[4][20] = {{"Pence"},{"Shilings"},{"Guinées"},{"Livres"}};/*Permet d'afficher les noms de chaque monnaie*/
    int I;
    int Total;
    int Somme = 6;/*Permet d'ajouter des bonus d'aptitudes*/
    int Rep;/*Permet de faire des choix*/
    int Nombre = 0;
    system("clear");
    Fonctions();
    cout<<"Pour commencer vous allez devoir distribuer vos bonus d'aptitudes\n";
    for(I=0;I<6;I++)/*Permet de redistribuer les points dans les aptitudes*/
    {

        cout<<"Combien voulez-vous mettre dans l’aptitude "<<Nom_Aptitudes[I]<<"\nIl vous reste "<<Somme<<" à mettre dans vos aptitudes \n";
        cin>>Aptitudes[I];/*Récupération de la valeur mise dans chaque aptitude*/
        if (Aptitudes[I]>=4)
        {
            do
            {
                cout<<"Vous devez mettre au maximum 3 bonus dans une aptitude\nJ'en mets : ";
                cin>>Aptitudes[I];
            }while(Aptitudes[I]>=4);
        }
        if (Aptitudes[I]>Somme)
        {
            do
            {
                cout<<"Vous ne pouvez pas mettre ce nombre de bonus dans l'aptitude "<<Nom_Aptitudes[I]<<" ";
                cout<<"Combien voulez-vous mettre dans cette aptitude ?\nJ'en mets : ";
                cin>>Aptitudes[I];
            }while(Aptitudes[I]>Somme);
        }
        Somme = Somme - Aptitudes[I];/*Met à jour la somme totale de bonus*/
    }
    for (I=0;I<4;I++)/*Permet d'obtenir la somme d'argent que possède le joueur dans chaque monnaie*/
    {
        cout<<"\nCombien avez-vous de "<<Nom_Monnaies[I]<<"\nJ’en possède : ";
        cin>>Argent[I];/*Récupération de la somme d'argent*/
        getchar();
    }
    cout<<"Avez-vous des Équipements ?\n1 : Oui\n2 : Non\n";
    cin>>Rep;/*Récupération du choix*/
    getchar();
    if(Rep == 1)/*Si la réponse est oui*/
    {
        cout<<"Combien d’équipements avez-vous ?\nJ’en possède : ";
        cin>>Nombre;/*Récupération du nombre d'équipements*/
        getchar();
        for(I=0;I<Nombre;I++)
        {
            do
            {
                cout<<"Quel est votre équipement N°"<<I+1<<"?\nMon équipement est : ";
                cin.getline(Equipements[I],40);/*Récupération des noms de chaque équipement*/
                Total = strlen(Equipements[I]);
                if(Total>20)
                {
                    cout<<"Le nom de votre équipement est trop grand recommencez\n";
                }
            }while(Total>20);
        }
    }
    cout<<"Entrez votre nom\nMon nom est : ";
    cin.getline(Nom_du_joueur,20);/*Récupération du nom du joueur*/
    Enregistrement_fiche_perso();
    system("clear");/*Effacement de l'écran*/
    Lecture_Fiche_perso();
    }
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Enregistrement_fiche_perso()
{
    int Total;/*Contiens le nombre de lettres dans des chaînes pour gérer l'affichage*/
    char Name[70] = "./";/*Permet d’écrire le calepin dont le nom est indiquer*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-fiche-perso.odt");
    fstream fichier(Name, ios::out);/*Ouverture ou création du fichier*/

        if(fichier)
        {
            fichier<<"╔═══════════════════════════════════════════════════════╗\n";
                      Total = strlen(Nom_du_livre);/*Récupération du nombre de lettre dans la chaîne du nom du livre*/
                      if((Total>=0) && (Total<=8))/*Si la chaîne fait entre 0 et 8 lettres afficher avec 4 tabulations*/
                          fichier<<"║Feuille d'Aventure : "<<Nom_du_livre<<"\t\t\t\t║\n";
                      if((Total>=9) && (Total<=17))/*Si la chaîne fait entre 9 et 17 lettres afficher avec 3 tabulations*/
                          fichier<<"║Feuille d'Aventure : "<<Nom_du_livre<<"\t\t\t║\n";
                      if((Total>=18) && (Total<=26))/*Si la chaîne fait entre 18 et 26 lettres afficher avec 2 tabulations*/
                          fichier<<"║Feuille d'Aventure : "<<Nom_du_livre<<"\t\t║\n";
                      if ((Total>=27) && (Total<35))/*Si la chaîne fait entre 27 et 35 lettres afficher avec 1 tabulation*/
                          fichier<<"║Feuille d'Aventure : "<<Nom_du_livre<<"\t║\n";
                      fichier<<"╠═══════════════════════════════════════════════════════╣\n";
                      Total = strlen(Nom_du_joueur);/*Récupération du nombre de lettres dans la chaîne du Nom du joueur*/
                      if(Total==0)/*Si la chaîne fait 0 lettre afficher avec 7 tabulations*/
                          fichier<<"║Nom : "<<Nom_du_joueur<<"\t\t\t\t\t\t\t║\n";
                      if((Total>=1) && (Total<=8))/*Si la chaîne fait entre 1 et 8 lettres afficher avec 6 tabulations*/
                          fichier<<"║Nom : "<<Nom_du_joueur<<"\t\t\t\t\t\t║\n";
                      if((Total>=9) && (Total<=17))/*Si la chaîne fait entre 9 et 17 lettres afficher avec 5 tabulations*/
                          fichier<<"║Nom : "<<Nom_du_joueur<<"\t\t\t\t\t║\n";
                      if((Total>=18) && (Total<=26))/*Si la chaîne fait entre 18 et 26 lettres afficher avec 4 tabulations*/
                          cout<<"║Nom : "<<Nom_du_joueur<<"\t\t\t\t║\n";
                      if ((Total>=27) && (Total<35))/*Si la chaîne fait entre 27 et 35 lettres afficher avec 3 tabulations*/
                          fichier<<"║Nom : "<<Nom_du_joueur<<"\t\t\t║\n";
                      fichier<<"║							║\n╠═══════════════════════════════╦═══════════════════════╣\n║Aptitudes  Bonus		║Équipements		║\n╠═══════════════════════════════╬═══════════════════════╣\n║Force : "<<Aptitudes[0]<<" 			║";
                      Total = strlen(Equipements[0]);/*Récupération du nombre de lettres dans la chaîne de l'équipement*/
                      if ((Total>=0) && (Total<=4))/*Si la chaîne fait entre 0 et 4 lettres afficher avec 3 tabulations*/
                          fichier<<"1)"<<Equipements[0]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))/*Si la chaîne fait entre 5 et 12 lettres afficher avec 2 tabulations*/
                          fichier<<"1)"<<Equipements[0]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))/*Si la chaîne fait entre 13 et 20 lettres afficher avec 1 tabulation*/
                          fichier<<"1)"<<Equipements[0]<<"\t║\n";
                      fichier<<"║        			║            		║\n║Habileté : "<<Aptitudes[1]<<"\t\t\t║";

                      Total = strlen(Equipements[1]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"2)"<<Equipements[1]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                        fichier<<"2)"<<Equipements[1]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                        fichier<<"2)"<<Equipements[1]<<"\t║\n";


                      fichier<<"║        			║            		║\n║Intuition : "<<Aptitudes[2]<<"\t\t\t║";

                      Total = strlen(Equipements[2]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"3)"<<Equipements[2]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"3)"<<Equipements[2]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"3)"<<Equipements[2]<<"\t║\n";

                      fichier<<"║        			║            		║\n║Éducation : "<<Aptitudes[3]<<"\t\t\t║";

                      Total = strlen(Equipements[3]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"4)"<<Equipements[3]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"4)"<<Equipements[3]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"4)"<<Equipements[3]<<"\t║\n";
                      fichier<<"║        			║            		║\n║Observation : "<<Aptitudes[4]<<"\t\t║";

                      Total = strlen(Equipements[4]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"5)"<<Equipements[4]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"5)"<<Equipements[4]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"5)"<<Equipements[4]<<"\t║\n";
                      fichier<<"║        			║            		║\n║Connaissances : "<<Aptitudes[5]<<"\t\t║";

                      Total = strlen(Equipements[5]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"6)"<<Equipements[5]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"6)"<<Equipements[5]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"6)"<<Equipements[5]<<"\t║\n";
                      fichier<<"║        			║           		║\n║        			║";

                      Total = strlen(Equipements[6]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"7)"<<Equipements[6]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"7)"<<Equipements[6]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"7)"<<Equipements[6]<<"\t║\n";
                      fichier<<"╠═══════════════════════════════╣            		║\n║ARGENT        			║";

                      Total = strlen(Equipements[7]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"8)"<<Equipements[7]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"8)"<<Equipements[7]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"8)"<<Equipements[7]<<"\t║\n";

                      if((Argent[0] >=0) && (Argent[0] <=9))/*Il peut y avoir un problème si on a plus de 10 pence il faut donc refaire l'affichage*/
                      fichier<<"║            	"<<Argent[0]<<" pence\t\t║            		║";
                      if (Argent[0] >=10)/*Si on a plus de 10 pence on retire une tabulation pour que l'affichage ne soit pas mauvais*/
                      fichier<<"║            	"<<Argent[0]<<" pence\t║            		║";

                      fichier<<"\n║                               ║";

                      Total = strlen(Equipements[8]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=4))
                        fichier<<"9)"<<Equipements[8]<<"\t\t\t║\n";
                      if((Total>=5) && (Total<=12))
                          fichier<<"9)"<<Equipements[8]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"9)"<<Equipements[8]<<"\t║\n";
                      fichier<<"║            	"<<Argent[1]<<" shillings 	║           		║\n║                       	║";

                      Total = strlen(Equipements[9]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=5))
                        fichier<<"10)"<<Equipements[9]<<"\t\t\t║\n";
                      if((Total>=6) && (Total<=12))
                          fichier<<"10)"<<Equipements[9]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"10)"<<Equipements[9]<<"\t║\n";
                      fichier<<"║            	"<<Argent[2]<<" guinées  	║            		║\n║        			║";

                      Total = strlen(Equipements[10]);/*Voir ligne 546*/
                      if ((Total>=0) && (Total<=5))
                        fichier<<"11)"<<Equipements[10]<<"\t\t\t║\n";
                      if((Total>=6) && (Total<=12))
                          fichier<<"11)"<<Equipements[10]<<"\t\t║\n";
                      if((Total>=13) && (Total<=20))
                          fichier<<"11)"<<Equipements[10]<<"\t║\n";

                      fichier<<"║               "<<Argent[3]<<" livres	║            		║\n╚═══════════════════════════════╩═══════════════════════╝\n";/*Écriture dans la fichier*/
                      Sauvegarde();
            fichier.close();/*Fermeture du fichier*/
            }
            else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Sauvegarde()
{
    char Name[70] = "./";/*Permet de sauvegarder les valeurs propres au joueur (Nom du joueur, Équipements…)*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/.");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-Sauvegarde.odt");
    int I;
    fstream fichier(Name, ios::out);
    if(fichier)
    {
        fichier<<Nom_du_livre<<"\n";
        fichier<<Nom_du_joueur<<"\n";
        for (I=0;I<11;I++)
        {
            fichier<<Equipements[I]<<"\n";
        }
        for(I=0;I<4;I++)
        {
            fichier<<Argent[I]<<"\n";
        }
        for(I=0;I<6;I++)
        {
            fichier<<Aptitudes[I]<<"\n";
        }
        fichier.close();
    }else
    {
        cout<<"Erreur de sauvegarde recommencez\n";
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
int Fonctions::Recuperation()
{
    int I;
    int Erreur = 0;
    char Name[70] = "./";/*Permet de récupérer les valeurs propres au joueur (Nom du joueur, Équipements…)*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/.");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-Sauvegarde.odt");
    fstream fichier(Name);
    system("clear");
    if(fichier)
    {

        fichier.getline(Nom_du_livre,40);
        fichier.getline(Nom_du_joueur,40);
        for(I=0;I<11;I++)
        {
            fichier.getline(Equipements[I],40);
        }
        for(I=0;I<4;I++)
        {
            fichier>>Argent[I];
        }
        for(I=0;I<6;I++)
        {
            fichier>>Aptitudes[I];
        }
        fichier.close();
    }else
    {
        cout<<"Aucune information sur la fiche perso de ce livre\n";
        Erreur = 1;
    }
    return Erreur;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Lecture_Fiche_perso()/*Lecture du fichier où se trouve la fiche personnage*/
{
    char Name[70] = "./";/*Permet de lire la fiche perso du livre dont le nom est indiqué*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-fiche-perso.odt");
    fstream fichier(Name);
    if(fichier)
    {
        system("clear");
        string ligne {};
        while(getline(fichier, ligne))
        {
            cout << ligne << endl;/*Affiche le contenu du fichier*/
        }
    }
    else
    {
        cout << "ERREUR il y a pas de fiche perso faite pour ce livre créez en une.\n";
    }
    fichier.close();
    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Ecriture_Notes()/*Saisie des notes*/
{
    char Name[70] = "./";/*Permet de créer un fichier Note avec le nom indiquer*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-notes.odt");
    fstream fichier(Name, ios::out|ios::app);
    system("clear");
    if(fichier)
    {
        cout<<"Quel est votre note ?"<<" : ";
        cin.getline(Notes,300);/*Récupération de l'indice*/
        fichier<<"\nNote : "<<Notes<<"\n---------------------------------------------------------------------";/*Écriture dans le fichier*/
        fichier.close();/*Fermeture du fichier*/
    }
    else
    {
        cout << "ERREUR Impossible de créer ce fichier.\n";
    }
    fichier.close();
    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Edition()
{
    int I;
    int Val;/*Permet de contenir les valeurs taper par l'utilisateur*/
    int Choix;/*Permet de contenir le choix de l'utilisateur*/
    int Erreur;/*Permet de gérer le cas où la fiche n'existe pas ou que les renseignements ne peuvent être obtenus*/
    char Nom_Aptitudes[6][20] = {{"Force"},{"Habileté"},{"Intuition"},{"Éducation"},{"Observation"},{"Connaissance"}};/*Permet d'afficher le nom de chaque aptitude*/
    char Nom_Monnaies[4][20] = {{"Pence"},{"Shilings"},{"Guinées"},{"Livres"}};/*Permet d'afficher les noms de chaque monnaie*/
    Erreur = Recuperation();/*Permet de savoir s’il y a une erreur lors de la récupération des informations*/
    if(Erreur == 1)/*S’il y a une erreur de récupération la boucle d'édition ne se fait pas*/
    {

    }
    else
    {
        cout<<"Que voulez-vous faire :\n1) Éditer les aptitudes\n2) Éditer les équipements\n3) Éditer le niveau d'argent\nMon choix : ";
        cin>>Choix;
        switch(Choix)
        {
        case 1:
            cout<<"Quelle aptitude voulez-vous éditer\n";
            for(I=0;I<6;I++)
            {
                cout<<I+1<<") "<<Nom_Aptitudes[I]<<" qui est de "<<Aptitudes[I]<<" \n";
            }
            cout<<"Mon choix : ";
            cin>>Choix;
            cout<<"À combien est l'aptitude "<<Nom_Aptitudes[Choix-1]<<"\nElle est de : ";
            cin>>Val;
            Aptitudes[Choix-1] = Val;
            cout<<"L'aptitude "<<Nom_Aptitudes[Choix-1]<<" est maintenant de "<<Aptitudes[Choix-1]<<"\n";
            getchar();
            break;
        case 2:
            cout<<"Quel est le numéro de l'équipement voulez-vous éditer ?\n";
            for(I=0;I<11;I++)
            {
                cout<<"Équipement N°"<<I+1<<" "<<Equipements[I]<<"\n";
            }
            cout<<"Mon choix : ";
            cin>>Choix;
            getchar();
            cout<<"Que est votre objet ?\nC'est : ";
            cin.getline(Equipements[Choix-1],40);
            cout<<"Vous avez en "<<Choix<<" "<<Equipements[Choix-1]<<"\n";
            break;
        case 3:
            cout<<"Quelle Monnaie voulez-vous modifier\n";
            for(I=0;I<4;I++)
            {
                cout<<I+1<<") "<<Argent[I]<<" "<<Nom_Monnaies[I]<<"\n";
            }
            cout<<"Mon choix : ";
            cin>>Choix;
            cout<<"Combien avez-vous de "<<Nom_Monnaies[Choix-1]<<"\n";
            cin>>Val;
            Argent[Choix-1] = Val;
            cout<<"Vous avez donc "<<Argent[Choix-1]<<" "<<Nom_Monnaies[Choix-1]<<"\n";
            getchar();
            break;
        default:
            cout<<"Erreur mauvais choix\n";
        }
        Enregistrement_fiche_perso();
    }
    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::Lecture_Notes()/*Lecture du fichier où se trouvent les notes*/
{
    char Name[70] = "./";/*Permet de lire un fichier de Note avec le nom indiquer*/
    strcat (Name,Nom_du_livre);
    strcat (Name,"/");
    strcat (Name,Nom_du_livre);
    strcat (Name,"-notes.odt");
    fstream fichier(Name);
    system("clear");
    if(fichier)
    {
        string ligne {};
        while(getline(fichier, ligne))
        {
            cout << ligne << endl;/*Affiche le contenu du fichier*/
        }
    }
    else
    {
        cout << "ERREUR il y a pas de notes de ce nom.\n";
    }
    cout<<"Pressez entrer pour retourner au menu";/*Retour au menu de sélection*/
    getchar();
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Fonctions::IHM()/*Affiche le menu et gère la saisie*/
{
    int Total;
    do
       {
        system("clear");
        cout<<"╔════════════════╦══════════════════════════════════════════════╗\n";
        Total = strlen(Nom_du_livre);
        if ((Total>=0) && (Total<=6))/*Affiche le nom du livre ouvert sur l'IHM selon le nombre de lettres de celui-ci*/
        {
              cout<<"║Detective Ultime║Livre : "<<Nom_du_livre<<"\t\t\t\t\t║";
        }
        if ((Total>=7) && (Total<=13))
        {
              cout<<"║Detective Ultime║Livre : "<<Nom_du_livre<<"\t\t\t\t║";
        }
        if ((Total>=14) && (Total<=20))
        {
              cout<<"║Detective Ultime║Livre : "<<Nom_du_livre<<"\t\t\t║";
        }
        if ((Total>=21) && (Total<=27))
        {
              cout<<"║Detective Ultime║Livre : "<<Nom_du_livre<<"\t\t║";
        }
        if ((Total>=28) && (Total<=33))
        {
              cout<<"║Detective Ultime║Livre : "<<Nom_du_livre<<"\t║";
        }
        if ((Total>=34) && (Total<=39))
        {
              cout<<"║Detective Ultime║Livre : "<<Nom_du_livre<<"  ║";
        }
        cout<<"\n╠════════════════╩══════════════════════════════════════════════╣\n║            Que voulez vous faire ?   	 	                ║\n║                                        	                ║\n║ 1) : Entrer le nom du livre            	                ║\n║ 2) : Entrer des informations dans le reperoire des noms       ║\n║ 3) : Entrer des indices et deductions dans le calepin         ║\n║ 4) : Entrer des notes dans mon carnet                         ║\n║ 5) : Crée sa fiche personnage                                 ║\n║ 6) : Lire le répertore des noms                               ║\n║ 7) : Lire le calepin		                                ║\n║ 8) : Lire mon carnet de notes                                 ║\n║ 9) : Afficher la fiche personnage                             ║\n║ 10) : Éditer la fiche personnage                              ║\n║ 11) : Simuler un lancer de dé                                 ║\n║ 12) : Fermer le programme                                     ║\n╚═══════════════════════════════════════════════════════════════╝\nMon choix : ";
        cin>>Choix;
        getchar();
        switch (Choix)/*Permet de lancer la bonne fonction*/
            {
            case 1:
                Nom_livre(); break;
            case 2:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Infos_personnages();
                }break;
            case 3:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Indices_deductions();
                }break;
             case 4:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Ecriture_Notes();
                }break;
             case 5:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Creation_fiche_perso();
                }break;
            case 6:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Lecture_Repertoire_des_noms();
                }break;
            case 7:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }
                else
                {
                    Lecture_Calepin();
                }break;
            case 8:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Lecture_Notes();/*Permet de lancer les dés*/
                }break;
            case 9:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Lecture_Fiche_perso();
                }break;
            case 10:
                if(Nom_du_livre[0] == '*')/*Permet d'inviter l'utilisateur à saisir le nom du livre si c'est pas déjà fait*/
                {
                    cout<<"\nEntrez le nom du livre avant\nPressez entrer pour retourner au menu";
                    getchar();
                }else
                {
                    Edition();
                }break;
            case 11:
                 Lancer_de_de();break;
            case 12:
                 cout<<"Au revoir jeune détective\n";break;/*Affiche un message avant de quitter le programme*/
            default:
                cout<<"Entrez un chiffre valide\nPressez entrer pour retourner au menu";
                getchar();
            }
        }while(Choix!=12);
}
