/*!
\file FcBasique.h
\brief Fichier d'entête des fonctions essentielles et structures
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 1 
\date 8 décembre 2019
*/
 
 /*
  * A faire (si non makefile)
  * gcc -c programme.c -o programme.o -lm
  * gcc -c FcBasique.c -o FcBasique.o -lm
  * gcc programme.o FcBasique.o -o Programme -lm
  sans oublier les autres fichiers qui peuvent y être lié
 */

#ifndef __fonction_Basique_
#define __fonction_Basique_

//----Importation des bibliothèques de base----//
#include <stdio.h>//bibliothèque d'entrée/sortie standard
#include <unistd.h>//Importation de la bibliothèque standard d'unix
#include <stdlib.h>//bibliothèque standard
#include <ctype.h>//Pour transformer une minuscule en majuscule et inversement
#include <string.h>//Pour les fonctions en lien avec les chaînes de caractère
#include <time.h>//Pour ce qui nécéssite de l'aléatoire
#include <math.h>//Pour les opérations mathématiques
#include <assert.h>//Pour la fonction saisieEntier
#include <ncurses.h>//Pour les graphismes
//------Definitions des structures-------

///------Structure d'un bateau-------
struct boat
{
	int tint_coor[2];//coordonnée de la case la plus en bas a gauche du bateau
	//tint_coor[0]=case lettrée et tint_coor[1]=case chiffrée
	int int_size;//Taille du bateau
	int int_dir;//Direction :
	//0 : vers la droite
	//1 : vers le haut
	
};

///------Structure d'une case-------
struct state
{
	int int_tir;//Indication de tir :
	//0 : Jamais ciblé
	//1 : Déjà ciblé
	int int_hit;//Indication d'un bateau touché :
	//0 : manqué ou jamais ciblé
	//1 : touché d'un bateau adverse
	//2 : bateau coulé
	struct boat bateau; //structure des informations sur le bateau
};


///------Structure d'un tableau de dimension 3 avec longueur et largeur-------
struct tab
{
	struct state*** ppstate_grid;//Tableau tridimensionnel
	int int_wid;//Largeur du tableau - horizontal
	int int_len;//Longueur du tableau | vertical
	int int_IA;
	//0 pas d'ia 
	//1 une ia
	int tint_nombreBateau[3];//Nombre de case contenant un bateau
	//tint_nombreBateau[2] correspond au nombre total
	//tint_nombreBateau[1] score du joueur 2
	//tint_nombreBateau[0] score du joueur 1
	
};


//------Controle de la saisie d'un entier-------
int saisieEntier(void);
//------Effacement du terminal-------
void clrscr();
//------Changement de la couleur du text-------
void resetColor();//Remise de la couleur de base
void ColorBlue();//Couleur bleu
void ColorRed();//Couleur rouge
void ColorMag();//Couleur magenta
#endif

