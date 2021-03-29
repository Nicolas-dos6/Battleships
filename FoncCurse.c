/*!
\file FoncCurse.c
\brief fichier d'entête (fonctions liées à l'affichage)
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 1 
\date 8 décembre 2019
*/


#include "FoncCurse.h"

/*
 * Fonction is_bold
 * But : Vérifier si l'entier correspond aux charactères en gras
 * Sortie : un entier
 * Argument : un entier
 */
int is_bold(int fg)
{
    /* return the intensity bit */

    int i;

    i = 1 << 3;
    return (i & fg);//ET binaire
    //1010 1101 & 1111 1110 (renvoie :) 1010 1100
}


/*
 * Fonction init_colorpairs
 * But : Initialiser les couleurs que l'on utilisera avec ncurse
 * Sortie : aucun
 * Argument : aucun
 */
void init_colorpairs(void)
{
    int fg, bg;
    int colorpair;
//---------------Initialisation des couleurs(foreground et background)---------------//
    for (bg = 0; bg <= 7; bg++) {
        for (fg = 0; fg <= 7; fg++) {
            colorpair = colornum(fg, bg);
            init_pair(colorpair, curs_color(fg), curs_color(bg));
        }
    }
}

/*
 * Fonction curs_color
 * But : fonction auxiliaire à init_colorpairs afin de faire
 correspondre un entier à une constante de ncurse
 * Sortie : un short(entier plus court)
 * Argument : un entier
 */
short curs_color(int fg)
{
//---------------Renvoi des constantes en fonction de l'entier---------------//
    switch (7 & fg) {           /* RGB */
    case 0:                     /* 000 */
        return (COLOR_BLACK);
    case 1:                     /* 001 */
        return (COLOR_BLUE);
    case 2:                     /* 010 */
        return (COLOR_GREEN);
    case 3:                     /* 011 */
        return (COLOR_CYAN);
    case 4:                     /* 100 */
        return (COLOR_RED);
    case 5:                     /* 101 */
        return (COLOR_MAGENTA);
    case 6:                     /* 110 */
        return (COLOR_YELLOW);
    case 7:                     /* 111 */
        return (COLOR_WHITE);
    }
return (COLOR_WHITE);
}

/*
 * Fonction colornum
 * But : fonction auxiliaire à init_colorpairs afin de faire
 correspondre un entier à une couleur
 * Sortie : un entier
 * Argument : deux entier 
 */
int colornum(int fg, int bg)
{
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);//OU binaire
    //1010 1101 | 1111 1110 (renvoie :) 1111 1111
}

/*
 * Fonction setcolor
 * But : fonction permettant de decider la couleur dont on veut que 
 l'ecriture et le fond soit
 * Sortie : aucune
 * Argument : deux entier correspondant à l'ecriture et au fond (foreground et background) 
 */
void setcolor(int fg, int bg)
{
    /* set the color pair (colornum) and bold/bright (A_BOLD) */

    attron(COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        attron(A_BOLD);
    }
}

/*
 * Fonction unsetcolor
 * But : fonction permettant de desactiver la couleur dont on a voulu que 
 l'ecriture et le fond soit
 * Sortie : aucune
 * Argument : deux entier correspondant à l'ecriture et au fond (foreground et background) 
 */
void unsetcolor(int fg, int bg)
{
    /* unset the color pair (colornum) and
       bold/bright (A_BOLD) */

    attroff(COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        attroff(A_BOLD);
    }
}

/*
 * Fonction GraphThird
 * But : Ecrire trois barres horizontales (utile pour la fonction affichage dans fonction.c)
 * Sortie : aucune
 * Argument : aucun 
 */
void GraphThird(){
    addch(ACS_HLINE);//Affichage d'un caractère correspondant à une barre horizontale
    addch(ACS_HLINE);
    addch(ACS_HLINE);   
}

/*
 * Fonction CurseInit
 * But : Initialiser l'affichage pour utiliser ncurses
 * Sortie : aucune
 * Argument : aucun 
 */
void CurseInit(){

    initscr();            /* Demarre le mode ncurses */
    cbreak();         /* Pour les saisies clavier (desac. mise en buffer) */
    noecho();             /* Desactive l'affichage des caracteres saisis */
    keypad(stdscr, TRUE); /* Active les touches specifiques */
    refresh();            /* Met a jour l'affichage */
    curs_set(FALSE);      /* Masque le curseur */
}

/*
 * Fonction printJoueur
 * But : Ecrire au milieu de l'écran le joueur qui doit jouer
 * Sortie : aucun
 * Argument : un entier(le joueur à afficher) 
 */
void printJoueur(int int_joueur){
    clear();
    mvaddstr(LINES / 2 - 1, COLS / 2 -6, "JOUEUR ");//Affichage de JOUEUR au milieu de l'ecran
    printw("%d",int_joueur+1);//Puis affichage du numéro du joueur à la suite
    getch();//Attente d'une pression de touche pour continuer
}

/*
 * Fonction printIndicationPlacement
 * But : Ecrire en haut à droite les indication liées au placement des bateaux
 * Sortie : aucun
 * Argument : aucun 
 */
void printIndicationPlacement(){
    mvaddstr(2,COLS-29,"Flèches : Se déplacer");
    mvaddstr(3,COLS-29,"Espace : Change de direction");
    mvaddstr(4,COLS-29,"Entrer : Valider");
}

/*
 * Fonction printIndicationTir
 * But : Ecrire en haut à droite les indication liées au tir 
 de meme que les touches à presser pour sauvegarder/quitter la partie 
 ou pour afficher ses propres bateaux
 * Sortie : aucun
 * Argument : la structure tab et un entier (le joueur actuel)
 */
void printIndicationTir(struct tab tab_t,int int_joueur){
    //---------------Indication sur les touches---------------/
    mvaddstr(2,COLS-23,"Flèches : Se déplacer");
    mvaddstr(3,COLS-23,"Entrer : Valider");
    mvaddstr(4,COLS-23,"W : Voir ses bateaux");
    mvaddstr(5,COLS-23,"S : Sauvegarder");
    mvaddstr(6,COLS-23,"Q : Quitter");
    //---------------Légende du tableau---------------//
    setcolor(13,0);
    mvaddch(7,COLS-23,ACS_CKBOARD);
    printw(" : Bateau coulé");
    unsetcolor(13,0);
    setcolor(12,0);
    mvaddch(8,COLS-23,ACS_CKBOARD);
    printw(" : Bateau touché");
    unsetcolor(12,0);
    setcolor(11,0);
    mvaddch(9,COLS-23,ACS_CKBOARD);
    printw(" : Eau");
    unsetcolor(11,0);
    setcolor(10,0);
    mvaddch(10,COLS-23,ACS_CKBOARD);
    printw(" : Jamais ciblé");
    unsetcolor(10,0);
    setcolor(14,0);
    //---------------Affichage du score---------------//
    mvaddstr(11,COLS-21,"Score : ");
    printw("%d / %d",tab_t.tint_nombreBateau[int_joueur],tab_t.tint_nombreBateau[2]);
    unsetcolor(14,0);

}

/*
 * Fonction CurseInit
 * But : enleve le mode ncurses et remet les paramètres par défaut
 * Sortie : aucune
 * Argument : aucun 
 */
void stop_ncurses(){
    endwin(); /* Arrête le mode ncurses */
    echo(); /* Active l'affichage des caracteres saisis */
    curs_set(TRUE); /* Affiche le curseur */
}


/*
 * Fonction printIndicationTirAdverse
 * But : Ecrire en haut à droite les indication liées au statut de nos bateaux
 (si le joueur ennemi les a touché) 
 * Sortie : aucun
 * Argument : aucun
 */
void printIndicationTirAdverse(){
    //---------------Correspondance des couleurs---------------//
   setcolor(10,0);
   mvaddch(2,COLS-23,ACS_CKBOARD);
   printw(" : Bateau non touché");
   unsetcolor(10,0);
   setcolor(13,0);
   mvaddch(4,COLS-23,ACS_CKBOARD);
   printw(" : Bateau coulé");
   unsetcolor(13,0);
   setcolor(12,0);
   mvaddch(3,COLS-23,ACS_CKBOARD);
   printw(" : Bateau touché");
   unsetcolor(12,0);
   setcolor(11,0);
   mvaddch(5,COLS-23,ACS_CKBOARD);
   printw(" : Eau");
   unsetcolor(11,0);
}
