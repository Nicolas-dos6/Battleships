/*!
\file fonction.h
\brief fonctions de la bataille navale (entête)
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 3.1
\date 8 décembre 2019
*/
 

#ifndef __fonction_H_
#define __fonction_H_

//----Importation de la bibliothèque FoncCurse et FcBasique(comprise dedans)---//
#include "FoncCurse.h"


//----Initialisation du plateau de jeu---//
struct tab init(struct tab tab_t);

//----Affichages des différentes phases de la partie---//
void AffichageTirAdverse(struct tab tab_t,int int_joueur,int int_i,int int_j);
void AffichageTir(struct tab tab_t,int int_joueur,int int_i,int int_j);
void Affichage(struct tab tab_t,int int_joueur,char char_info);

//----Placement des bateaux---//
int verifRectangle(struct tab tab_t,int int_joueur,int int_x1,int int_y1,int int_x2,int int_y2);
int def_x_y(struct tab tab_t,int int_lettre,int int_chiffre,int int_joueur,int int_direction,int int_taille);
struct tab placement (struct tab tab_t,int int_joueur,int int_taille);
void verifDimensionsBash(struct tab tab_t);//Vérification des dimensions du terminal pour un affichage optimal
struct tab CreaBateau(struct tab tab_t);

//----Tir sur les bateaux ennemis---//
struct tab toucherCouler(struct tab tab_t,int int_joueur,int int_x,int int_y);
struct tab viserTirer(struct tab tab_t,int int_joueur);

//----Sauvegarde de la partie en cours---//
int ecriture(struct tab tab_t,int int_joueur);
struct tab lecture(int* pint_joueur);

//----Fonction principal pour la gestion des différentes phases de la partie---//
int batailleNavale();

//----Fonctions liées à l'intelligence artificielle---//
int* IA_PROBA(int** ppint_t,int int_wid,int int_len);
///----Placement de l'intelligence artificielle---///
int* IA_PLACEMENT(struct tab tab_t,int int_taille);
struct tab IA_PLACE(struct tab tab_t,int int_taille);
///----Tir de l'intelligence artificielle---///
int* RIA_VISE(struct tab tab_t);
int** IA_FINE(struct tab tab_t,int int_x,int int_y);
int* IA_VISE(struct tab tab_t);
struct tab IA_TIRE(struct tab tab_t, int int_diff);
#endif

