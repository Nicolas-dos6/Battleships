/*!
\file programme.c
\brief programme principal pour la bataille navale
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 1 
\date 8 décembre 2019
*/


#include "fonction.h"
/*
 * Fonction main
 * But : Programme principal exécutant la bataille navale
 * Sortie : un entier
 * Entrée : un entier (le nombre d'argument lors de l'appel du programme) et les arguments (lors de l'appel du programme)
 */
int main(int argc, char **argv)
{	
	srand(time(NULL));//Initialisation de la fonction aléatoire
	clrscr();//Efface l'affichage
	//--------------Declaration du début du programme-------------//
	ColorBlue();
	printf("---------------------------------\n");
	ColorRed();
	printf("---Bienvenue dans le programme---\n");
	ColorMag();
	printf("---------------------------------\n");
	resetColor();//Remise de la couleur par défaut
	//--------------Lancement de la bataille navale-------------//
	batailleNavale();
	return 0;
}
