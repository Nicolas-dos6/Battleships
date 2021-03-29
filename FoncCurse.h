/*!
\file FoncCurse.h
\brief Fichier d'entête des fonctions liées à l'affichage
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 1 
\date 8 décembre 2019
*/
 

#ifndef __Fonctions_Curse_
#define __Fonctions_Curse_


//----Importation de la bibliothèque principale---//
#include "FcBasique.h"



//----Fonctions pour les couleurs de ncurses----//
//Prise sur internet et modifiée dans notre intêrêt
int is_bold(int fg);
void init_colorpairs(void);
short curs_color(int fg);
int colornum(int fg, int bg);
void setcolor(int fg, int bg);
void unsetcolor(int fg, int bg);

//----Fonctions pour les indications lors de l'affichage du plateau de jeu----//
void GraphThird();
void CurseInit();//Fonction qui lance le mode ncurse
void printJoueur(int int_joueur);
void printIndicationPlacement();
void printIndicationTir();
void stop_ncurses();//Fonction qui éteint le mode ncurse 
void printIndicationTirAdverse();
#endif