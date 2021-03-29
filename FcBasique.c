/*!
\file FcBasique.c
\brief fichier d'entête (fonctions)
	fonctions essentielles
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 1
\date 8 décembre 2019
*/


#include "FcBasique.h"
/*
 * Fonction saisieEntier
 * But : Vérifier la saisie de l'utilisateur
 * Sortie : un entier
 * Argument : aucun
 */
int saisieEntier(void){
	int int_retour,int_n; //int_retour -> retour des scanf | int_n -> valeur à renvoyer
	float float_n; //float_n -> valeur que l'utilisateur va rentrer
	int_retour = scanf("%f",&float_n); //Rentrée de la valeur de l'utilisateur
	assert(int_retour!=0); //Arrête le programme si la valeur rentrée n'est pas un nombre 
	assert(floor(float_n)==float_n); //Arrête le programme si la valeur rentrée n'est pas un entier
	int_n = floor(float_n); //Transformation d'un réel en entier pour le renvoie de la fonction
	return(int_n); //Renvoie de l'entier correctement entré par l'utilisateur
	}
/*
 * Fonction clrscr
 * But : Effacer le contenu du terminal
 * Sortie : aucun
 * Argument : aucun
 */
void clrscr()
{	
	printf("\e[1;1H\e[2J");//Effacement du terminal
}

/*
 * Fonction resetColor
 * But : Remet la couleur de base du text
 * Sortie : aucun
 * Argument : aucun
 */
void resetColor()
{	
	printf("\033[0m");//Remise de la couleur par defaut
}

/*
 * Fonction ColorBlue
 * But : Modifie la couleur du texte en bleu
 * Sortie : aucun
 * Argument : aucun
 */
void ColorBlue()
{	
	printf("\033[1;36m");//Modification de couleur
}

/*
 * Fonction ColorRed
 * But : Modifie la couleur du texte en rouge
 * Sortie : aucun
 * Argument : aucun
 */
void ColorRed()
{	
	printf("\033[1;31m");//Modification de couleur
}

/*
 * Fonction ColorMag
 * But : Modifie la couleur du texte en magenta
 * Sortie : aucun
 * Argument : aucun
 */
void ColorMag()
{	
	printf("\033[1;35m");//Modification de couleur
}

