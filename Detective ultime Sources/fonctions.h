#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <fstream>

class Fonctions
{
    char Nom_Perso[50];/*Tableau qui contient le nom du personnage dont on indique les informations*/
    char Infos[100];/*Tableau qui contient les Informations sur le personnage dont le nom est plus haut*/
    char Indices[1000];/*Tableau qui contient l'indices ecrit en toutes lettres*/
    char Nom_du_livre[50];/*Tableau qui contient le nom du livre qui permettra de crée le repertoire et les fichiers sous ce même nom
                                    Il est de base à * pour détecter quand le nom n'est pas péciser*/
    char Notes[300];
    char Nom_du_joueur[20];/*Contient le nom du joueur*/
    char Equipements[11][40];/*Contient les noms de équipements*/
    int Numero;/*Variable qui indique le numéro d'un indice ou une déduction*/
    int Choix;/*Variable qui contient le choix qui est fait dans l'IHM*/
    int Aptitudes[6];/*Stock les bonus d'aptitudes*/
    int Argent[3];/*Contient la somme que pocède le joueur par monnaies*/
    void Nom_livre();/*Fonction de saisie du nom du livre*/
    void Infos_personnages();/*Fonction de saisie de nom dans le repertoire des noms*/
    void Indices_deductions();/*Fonction de saisies d'indices et déductions*/
    void Lancer_de_de();/*Fonction qui simule un lancer de dé*/
    void Lecture_Repertoire_des_noms();/*Fonction qui permet la lecture du repertoire des noms*/
    void Lecture_Calepin();/*Fonction qui permet la lecture du calepin*/
    void Creation_fiche_perso();/*Fonction qui permet de crée une fiche personnage qui sera sauvegarder avec la fonction ligne 29*/
    void Lecture_Fiche_perso();/*Fonction qui Permet de lire la fiche personnage*/
    void Ecriture_Notes();/*Fonction qui Permet d'ecrire des notes*/
    void Lecture_Notes();/*Fonction qui Permet de lire les notes*/
    void Enregistrement_fiche_perso();/*Permet d'enregister la fiche perso dans un fichier*/
    void Sauvegarde();/*Permet de sauvegarder les valeurs propres au joueur (Nom du joueur, Equipements...)*/
    int Recuperation();/*Permet de rercuperer les valeurs propre au joueur (Nom du joueur, Equipements...) il permet aussi de revoyer une valeur si une erreur c'est produite*/
    void Edition();/*Permet d'éditer la fiche personnage du joueur pour modifier l'argent ou une aptitude*/
public:
    int Comparaison(char Lettre);
    Fonctions();/*Constructeur qui initialise Nom_du_livre Argent et Equipements*/
    void IHM();/*Fonction qui permet de lancer les autres fonctions*/
};

#endif // FONCTIONS_H
