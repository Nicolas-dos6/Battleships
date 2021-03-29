/*!
\file fonction.c
\brief fonctions de la bataille navale (fonctions)
\author Nicolas Dos Santos/Maxime Pegan/Théo Julien
\version 3.1
\date 8 décembre 2019
*/

//////////////////////////////////////////////////////////
/////////////--------------PROJET---------------//////////
//////////////////////////////////////////////////////////

#include "fonction.h"
/*
 * Fonction init
 * But : Initialiser et allouer le tableau tridimensionnel
 * Sortie : une structure tab
 * Argument : une structure tab, deux entier largeur(horizontale) puis longueur(verticale)
 */

struct tab init(struct tab tab_t){
	//Définition du tableau tri dimensionnel
	//tab_t.ppstate_grid [joueur(0;1)] [Abscisse(colonne)] [Ordonnée(ligne)]
	printf("Veuillez indiquer le nombre de colonne : ");
	int int_w = saisieEntier();
	printf("Veuillez indiquer le nombre de ligne : ");
	int int_l = saisieEntier();
	//----------------Allocation du tableau----------------//

	///----------Allocation nombre de joueur * pointeur de pointeur---------///
	tab_t.ppstate_grid=malloc(2*sizeof(struct state**));	
	///--------------Allocation nombre de colonne * pointeur ---------------///
		tab_t.ppstate_grid[0]=malloc(int_w*sizeof(struct state*));
		tab_t.ppstate_grid[1]=malloc(int_w*sizeof(struct state*));	
	///----------------Allocation nombre de ligne * state---------------///	
		for(int int_j=0;int_j<int_w;int_j++)
		{
			tab_t.ppstate_grid[0][int_j]=malloc(int_l*sizeof(struct state));
			tab_t.ppstate_grid[1][int_j]=malloc(int_l*sizeof(struct state));
		}

	//--------------Initialisation du tableau--------------//	
	for (int int_i=0;int_i<int_w;int_i++) //Abscisse
	{
		for(int int_j=0;int_j<int_l;int_j++) //Ordonnée
		{
			for(int int_k=0;int_k<2;int_k++) //Joueur
			{
				tab_t.ppstate_grid[int_k][int_i][int_j].int_tir=0;
				tab_t.ppstate_grid[int_k][int_i][int_j].int_hit=0;
				tab_t.ppstate_grid[int_k][int_i][int_j].bateau.int_size=0;
				tab_t.ppstate_grid[int_k][int_i][int_j].bateau.int_dir=0;
				tab_t.ppstate_grid[int_k][int_i][int_j].bateau.tint_coor[0]=0;
				tab_t.ppstate_grid[int_k][int_i][int_j].bateau.tint_coor[1]=0;
			}	
		}
	}
	//--------------Définition des dimensions et paramètres--------------//
	tab_t.int_wid=int_w;
	tab_t.int_len=int_l;
	tab_t.tint_nombreBateau[2]=0;
	tab_t.tint_nombreBateau[1]=0;
	tab_t.tint_nombreBateau[0]=0;
	tab_t.int_IA=0;
	
	//------------------Renvoi du tableau------------------//
	return(tab_t);
}


/*
 * Fonction AffichageTirAdverse
 * But : Afficher la couleur correspondante de l'état du bateau
 * Sortie : aucun
 * Argument : une struct tab, trois entiers (joueur et coordonnées)
 */
void AffichageTirAdverse(struct tab tab_t,int int_joueur,int int_i,int int_j){
	if (tab_t.ppstate_grid[int_joueur][int_i][int_j].bateau.int_size==0){
		/////-------------Affichage de l'eau--------------/////
		setcolor(11,0);
		addch(ACS_CKBOARD);
		unsetcolor(11,0);		
	}else{
		if(tab_t.ppstate_grid[1-int_joueur][int_i][int_j].int_hit==1)
		{
		/////-------------Affichage case bateau touché--------------/////
			setcolor(12,0);
			addch(ACS_CKBOARD);
			unsetcolor(12,0);
		}else if(tab_t.ppstate_grid[1-int_joueur][int_i][int_j].int_hit==2){
			/////-------------Affichage bateau coulé--------------/////
			setcolor(13,0);
			addch(ACS_CKBOARD);
			unsetcolor(13,0);
		}else{
			/////-------------Affichage case bateau intact--------------/////
			setcolor(10,0);
			addch(ACS_CKBOARD);
			unsetcolor(10,0);
		}
	}



}

/*
 * Fonction AffichageTir
 * But : Afficher la couleur correspondante de l'état de la case du plateau de tir
 * Sortie : aucun
 * Argument : une struct tab, trois entiers (joueur et coordonnées)
 */
void AffichageTir(struct tab tab_t,int int_joueur,int int_i,int int_j){
	if(tab_t.ppstate_grid[int_joueur][int_i][int_j].int_tir>0){
		if(tab_t.ppstate_grid[int_joueur][int_i][int_j].int_hit>0){
			if(tab_t.ppstate_grid[int_joueur][int_i][int_j].int_hit>1){
				/////-------------Affichage bateau coulé--------------/////
				setcolor(13,0);
				addch(ACS_CKBOARD);
				unsetcolor(13,0);
			}else{
				/////-------------Affichage bateau touché--------------/////
				setcolor(12,0);
				addch(ACS_CKBOARD);
				unsetcolor(12,0);
			}
		}else{
			/////-------------Affichage eau ciblé--------------/////
			setcolor(11,0);
			addch(ACS_CKBOARD);
			unsetcolor(11,0);
		}
	}else{
		/////-------------Affichage jamais ciblé--------------/////
		setcolor(10,0);
		addch(ACS_CKBOARD);
		unsetcolor(10,0);
	}

}


/*
 * Fonction Affichage
 * But : Affichage du tableau (le coeur de l'affichage est non défini)
 * Sortie : aucun
 * Argument : une structure tab,un entier le joueur actuel et un char le type de tableau à afficher
 */
void Affichage(struct tab tab_t,int int_joueur,char char_info){// 'b' comme bateau et 't' comme tir et 'a' comme adverse
	char alphabet[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	addch(ACS_DIAMOND);
	printw("Tableau joueur %d\n",int_joueur+1);
	//------------------Affichage du haut------------------//
		///-------------Correspondance des lettres--------------///
	printw("  ");
	for (int int_i = 0; int_i < tab_t.int_wid; ++int_i)
	{
		printw("   %c",alphabet[int_i]);
	}
		///-------------Première interligne--------------///
	printw("\n   ");
	addch(ACS_ULCORNER);
	for (int int_i = 1; int_i < tab_t.int_wid; ++int_i)
	{
		GraphThird();
		addch(ACS_TTEE);
	}
	GraphThird();
	addch(ACS_URCORNER);


	//------------------Affichage du coeur-----------------//
	for (int int_j = 0; int_j < tab_t.int_len; int_j++)
	{
		///-------------Correspondance des nombres--------------///
		if (int_j<9){printw("\n%d  ",int_j+1);}
		else{printw("\n%d ",int_j+1);}
		addch(ACS_VLINE);
		///-------------Affichage des données--------------///
		for (int int_i = 0; int_i < tab_t.int_wid; ++int_i)
		{	
			printw(" ");
			if (char_info=='b'){
				////-------------Affichage des bateaux--------------////
				if(tab_t.ppstate_grid[int_joueur][int_i][int_j].bateau.int_size>0){
				setcolor(12,0);
				addch(ACS_CKBOARD);
				unsetcolor(12,0);
				}else{
				setcolor(11,0);
				addch(ACS_CKBOARD);
				unsetcolor(11,0);
				}
			}else if (char_info=='t'){
				////-------------Affichage des tirs--------------////
				AffichageTir(tab_t,int_joueur,int_i,int_j);
			}else{
				////-------------Affichage des tirs adverses sur nos bateaux--------------////
				AffichageTirAdverse(tab_t,int_joueur,int_i,int_j);
			}
			
		printw(" ");addch(ACS_VLINE);
		}
		///-------------Affichage interlignes--------------///
		if(int_j<tab_t.int_len-1){
			printw("\n");
			addch(ACS_HLINE);
			printw("  ");
			for (int int_i = 0; int_i < tab_t.int_wid; ++int_i)
			{
				if(int_i!=0){addch(ACS_PLUS);GraphThird();}else{addch(ACS_LTEE);GraphThird();}
			}
			addch(ACS_RTEE);
		}
	}

	//-------------------Affichage du bas------------------//
		///-------------Dernière interligne--------------///
	printw("\n   ");
	addch(ACS_LLCORNER);
	for (int int_i = 1; int_i < tab_t.int_wid; ++int_i)
	{	
		GraphThird();
		addch(ACS_BTEE);
	}
	GraphThird();
	addch(ACS_LRCORNER);
printw("\n");
//-------------Mise à jour de l'écran--------------//
refresh();
}


/*
 * Fonction verifRectangle
 * But : Vérifier si l'emplacement de (x1,y1) jusqu'à (x2,y2) est légal (il n'y a pas de bateau)
 * Sortie : un entier
 * Argument : une structure tab, 5 entiers, le joueur et les coordonnées du rectangle
 */
int verifRectangle(struct tab tab_t,int int_joueur,int int_x1,int int_y1,int int_x2,int int_y2){
	for (int int_i = int_x1; int_i <= int_x2  ; int_i++)
	{
		for (int int_j = int_y1; int_j >= int_y2 ; int_j--)
		{
			if(tab_t.ppstate_grid[int_joueur][int_i][int_j].bateau.int_size>0){return(-1);}//Erreur, il y a un bateau dans le rectangle à verifier
		}
	}
	return(0);//tout va bien, on peut placer le bateau
}


/*
 * Fonction verifRectangle
 * But : definir le rectangle à vérifier pour le placement du bateau
 * Sortie : un entier
 * Argument : une structure tab, 5 entiers, le joueur, et l'identité du bateau (case de départ,taille et direction)
 */
int def_x_y(struct tab tab_t,int int_lettre,int int_chiffre,int int_joueur,int int_direction,int int_taille){
	int int_x1,int_x2,int_y1,int_y2;
	if((int_lettre<0) || (int_lettre>=tab_t.int_wid) || (int_chiffre<0) || (int_chiffre>=tab_t.int_len)){return(-1);}
		//La case est dans le tableau
	if(int_direction==0){//c'est horizontal
		if(int_lettre+int_taille>=tab_t.int_wid){return(-1);}else{
			//Le bateau est dans le tableau
		//----------Définition des dimensions du rectangle-----------//
			int_x1=int_lettre-1;
			int_x2=int_lettre+int_taille+1;
			int_y1=int_chiffre+1;
			int_y2=int_chiffre-1;
		}
	}
	if(int_direction==1){//c'est vertical
		if(int_chiffre-int_taille<0){return(-1);}else{
			//Le bateau est dans le tableau
		//----------Définition des dimensions du rectangle-----------//
			int_x1=int_lettre-1;
			int_x2=int_lettre+1;
			int_y1=int_chiffre+1;
			int_y2=int_chiffre-int_taille-1;
		}
	}
	//----------Adaptation des dimensions aux bordures de la grille-----------//
	if(int_x1<0){int_x1=0;}
	if(int_x2>=tab_t.int_wid){int_x2=tab_t.int_wid-1;}
	if(int_y1>=tab_t.int_len){int_y1=tab_t.int_len-1;}
	if(int_y2<0){int_y2=0;}
	//----------Vérification du rectangle-----------//
	if(verifRectangle(tab_t,int_joueur,int_x1,int_y1,int_x2,int_y2)==-1){return(-1);}
	return(0);//tout va bien
}


/*
 * Fonction placement
 * But : Demander à l'utilisateur où il veut placer son bateau
 * Sortie : une structure tab
 * Argument : une structure tab, le joueur actuel et la taille du bateau
 */
struct tab placement (struct tab tab_t,int int_joueur,int int_taille)
{
	//----------Déclaration/initialisation des variables-----------//
	int int_posX,int_posY,int_ch;
	int int_lettre, int_chiffre, int_direction;
	int int_verification;
	int_posX = 5;int_lettre=0;
 	int_posY = 3;int_chiffre=0;
  	int_direction=0;
	do{
		//----------Affichage des bateaux-----------//
		clear();
		Affichage(tab_t,int_joueur,'b');
		printIndicationPlacement();
		//----------Placement des diamants(caractère) en fonction de la taille/direction du bateau-----------//
		/* Place le curseur à la position de départ */
 		for (int int_i = 0; int_i < int_taille; ++int_i)
  		{
        	if(def_x_y(tab_t,int_lettre,int_chiffre,int_joueur,int_direction,int_taille-1)==0){
    			setcolor(10,0);//Vert -> On peut placer le bateau ici
    			if(int_direction==0){
    				mvaddch(int_posY, int_posX+int_i*4, ACS_DIAMOND);
    			}else{
    				mvaddch(int_posY-int_i*2, int_posX, ACS_DIAMOND);
    			}
       			unsetcolor(10,0);
   			}else{
				setcolor(12,0);//Rouge -> On ne peut pas placer le bateau ici
        		if(int_direction==0){
    				mvaddch(int_posY, int_posX+int_i*4, ACS_DIAMOND);
    			}else{
    				mvaddch(int_posY-int_i*2, int_posX, ACS_DIAMOND);
    			}
        		unsetcolor(12,0);
   			}
    	}
    	//----------Mise à jour de la fenêtre-----------//
  		refresh();
 
  /* Routine principale */
  		while((int_ch = getch()) != 10) {
    /* On efface le curseur (remplacement du curseur par le caractère/couleur correspondant)*/ 
		    for (int int_i = 0; int_i < int_taille; ++int_i)
		    {	

		    	if(int_direction==0){
		    		if(tab_t.ppstate_grid[int_joueur][int_lettre+int_i][int_chiffre].bateau.int_size>0){
		    			setcolor(12,0);
		    			mvaddch(int_posY, int_posX+int_i*4, ACS_CKBOARD);
		    			unsetcolor(12,0);
		    		}else{
		    			setcolor(11,0);
		    			mvaddch(int_posY, int_posX+int_i*4, ACS_CKBOARD);
		    			unsetcolor(11,0);
		    		}
		    	}else{
		    		if(tab_t.ppstate_grid[int_joueur][int_lettre][int_chiffre-int_i].bateau.int_size>0){
		    			setcolor(12,0);
		    			mvaddch(int_posY-int_i*2, int_posX, ACS_CKBOARD);
		    			unsetcolor(12,0);
		    		}else{
						setcolor(11,0);
		    			mvaddch(int_posY-int_i*2, int_posX, ACS_CKBOARD);
		    			unsetcolor(11,0);
		    		}
		    	}
		    }
	    /* On calcule la nouvelle position et si on a le droit*/
		    switch(int_ch){
		      case KEY_LEFT:
			    if(int_posX > 5){
			    	int_lettre-=1;
					int_posX-=4;
				}else{beep();}
			    break;
		      case KEY_RIGHT:
			    if(((int_posX < 5+(4*tab_t.int_wid)-int_taille*4) && (int_direction==0)) || ((int_posX < 5+(4*(tab_t.int_wid-1))) && (int_direction==1))){
			    	int_lettre+=1;
					int_posX+=4;
				}else{beep();}
			    break;
		      case KEY_UP:
			    if(((int_posY > 3) && (int_direction==0)) || ((int_posY > 1+int_taille*2) && (int_direction==1))){
			    	int_chiffre-=1;
					int_posY-=2;
				}else{beep();}
			    break;
		      case KEY_DOWN:
			    if(int_posY < 1+(2*tab_t.int_len)){
			    	int_chiffre+=1;
			    	int_posY+=2;
				}else{beep();}
			    break;
		   	 case 32://Espace
		   	 		if((int_posY>int_taille*2) && (int_direction==0)){
		   	 			int_direction=1;
		   	 		}else if((int_posX < 6+(4*tab_t.int_wid)-int_taille*4) && (int_direction==1)){
		   	 			int_direction=0;
		   	 		}
			    break;
			  default:
			  break;
		    }

		    //----------Mise en variable de la fonction def_x_y pour l'utiliser plusieurs sans la recalculer-----------//
		    int_verification=def_x_y(tab_t,int_lettre,int_chiffre,int_joueur,int_direction,int_taille-1);
		    /* On affiche le curseur */
		    for (int int_i = 0; int_i < int_taille; ++int_i)
		    {
		    	if(int_verification==0){
		    		setcolor(10,0);//Couleur verte
		    		if(int_direction==0){
		        		mvaddch(int_posY, int_posX+int_i*4, ACS_DIAMOND);
		        	}else{
		        		mvaddch(int_posY-int_i*2, int_posX, ACS_DIAMOND);
		        	}
		       		unsetcolor(10,0);
		   		}else{
					setcolor(12,0);//Couleur rouge
		        	if(int_direction==0){
		        		mvaddch(int_posY, int_posX+int_i*4, ACS_DIAMOND);
		        	}else{
		        		mvaddch(int_posY-int_i*2, int_posX, ACS_DIAMOND);
		        	}
		        	unsetcolor(12,0);
		   		}
		    }
		    //----------Mise à jour de la fenêtre-----------//
	    	refresh();
 		}
	}while(def_x_y(tab_t,int_lettre,int_chiffre,int_joueur,int_direction,int_taille-1)!=0);//int_taille-1 car on compte le 0
	//On demande de choisir un emplacement tant que l'emplacement choisi n'est pas disponible
	clear();
	//----------Indication au joueur que le bateau est placé-----------//
	mvaddstr(LINES / 2 - 1,COLS / 2 -8,"Bateau placé ! ");
	getch();
	//----------Definition de l'identité du bateau(chaque bateau a une case de départ, une direction et une taille)-----------//
	for (int int_i = 0; int_i < int_taille; int_i++)
	{
		if(int_direction==0){
			tab_t.ppstate_grid[int_joueur][int_lettre+int_i][int_chiffre].bateau.tint_coor[0]=int_lettre;
			tab_t.ppstate_grid[int_joueur][int_lettre+int_i][int_chiffre].bateau.tint_coor[1]=int_chiffre;
			tab_t.ppstate_grid[int_joueur][int_lettre+int_i][int_chiffre].bateau.int_size=int_taille;
			tab_t.ppstate_grid[int_joueur][int_lettre+int_i][int_chiffre].bateau.int_dir=0;
		}else{
			tab_t.ppstate_grid[int_joueur][int_lettre][int_chiffre-int_i].bateau.tint_coor[0]=int_lettre;
			tab_t.ppstate_grid[int_joueur][int_lettre][int_chiffre-int_i].bateau.tint_coor[1]=int_chiffre;
			tab_t.ppstate_grid[int_joueur][int_lettre][int_chiffre-int_i].bateau.int_size=int_taille;
			tab_t.ppstate_grid[int_joueur][int_lettre][int_chiffre-int_i].bateau.int_dir=1;
			}
	}
	return(tab_t);
}


/*
 * Fonction verifDimensionsBash
 * But : Force l'utilisateur à utiliser une taille de terminal optimal
 * Sortie : aucun
 * Argument : une structure tab
 */
void verifDimensionsBash(struct tab tab_t){

while(1) {
	clear();
	//----------Indication du nombre de colonne/ligne actuel-----------//
   		mvaddstr((LINES / 2) +1,(COLS / 2) -27,"Le terminal actuel comporte");
        printw(" %d lignes et %d colonnes\n", LINES, COLS);
    //----------Indication du nombre de colonne/ligne necessaire-----------//
        mvaddstr((LINES / 2)+2,(COLS / 2) -30,"Le terminal doit comporter au moins");
        printw(" %d lignes et %d colonnes\n", 3+2*tab_t.int_len, 34+4*tab_t.int_wid);
        refresh();  // Rafraîchit la fenêtre par défaut (stdscr) afin d'afficher le message
        if((getch() != 410) && (LINES>=3+2*tab_t.int_len) && (COLS>=34+4*tab_t.int_wid))  // 410 est le code de la touche générée lorsqu'on redimensionne le terminal
        	//Si les conditions sont respectées on peut continuer
            break;
    }

}


/*
 * Fonction CreaBateau
 * But : Definition du nombre et de la taille des bateaux, cette fonction appelle la fonction de placement des bateaux
 * une fois que le nombre et la taille a été définie
 * Sortie : une structure tab
 * Argument : une structure tab
 */
struct tab CreaBateau(struct tab tab_t){
	//----------Définition des variables-----------//
	int int_taille;
	char char_ch;
	int *tint_nbr=NULL;
	clrscr();
	do{
	//----------Demande le nombre et la taille des bateaux-----------//
		printf("Taille du plateau de jeu %dx%d\n",tab_t.int_wid,tab_t.int_len);
		printf("Donnez la taille du plus grand bateau : ");
		int_taille = saisieEntier();
	}while((int_taille>tab_t.int_wid) && (int_taille>tab_t.int_len));//On ne peut pas placer de bateau plus grand que le plateau 
	//----------Création d'un tableau permettant de stocker le nombre de bateau selon leur taille-----------//
	tint_nbr=malloc(int_taille*sizeof(int));
	for (int int_i = int_taille; int_i > 0 ; int_i--)
	{
		printf("Nombre de bateau de %d case(s) : ",int_i);
		tint_nbr[int_i-1]=saisieEntier();//Demande du nombre de bateau selon la taille de manière décroissante
		tab_t.tint_nombreBateau[2] += tint_nbr[int_i-1]*int_i;//Definition du nombre de case bateau pour le score
	}
	CurseInit();//Démarrage du mode ncurses
	/* Verification des dimensions du terminal */
	verifDimensionsBash(tab_t);
	/* Verification du support de la couleur */
	if(has_colors() == FALSE) {
		endwin();
		fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
		exit(EXIT_FAILURE);
	}
	//----------Initialisation des couleurs ncurses-----------//
	start_color();
    init_colorpairs();
    //----------Appel du placement des bateau en fonction du statut du joueur (humain ou IA)-----------//
	for (int int_joueur = 0; int_joueur < 2; int_joueur++)//pour les deux joueurs
	{	
		printJoueur(int_joueur);
		for (int int_tailleBateau = int_taille-1; int_tailleBateau >= 0; int_tailleBateau--)//Pour chaque taille de bateau
		{
			for (int int_nombreBateau = 0; int_nombreBateau < tint_nbr[int_tailleBateau]; int_nombreBateau++)//Pour le nombre de bateau de cette taille
			{
				if((tab_t.int_IA==1) && (int_joueur==1)){//l'IA sera toujours le second joueur (int_joueur=1)
					tab_t=IA_PLACE(tab_t,int_tailleBateau+1);//placement IA
				}else{
					tab_t=placement(tab_t,int_joueur,int_tailleBateau+1);//Placement humain
				}
			}
		}
	}
	//----------Demande d'affichage des placements des bateaux de l'IA-----------//
	if(tab_t.int_IA==1){
		clear();
		mvaddstr(0,0,"Voulez-vous afficher les placements de l'IA ?(o/n)");//permettre de vérifier les placements de l'IA
		char_ch=getch();
		if((char_ch==111)||(char_ch==79)){//Si la touche 'o' est préssée alors on affiche
			clear();
			Affichage(tab_t,1,'b');
			getch();
		}
	}
	return(tab_t);
}

/*
 * Fonction toucherCouler
 * But : Met à jour le tableau de tir si le bateau a été touché assez de fois pour être coulé
 * Sortie : une structure tab
 * Argument : une structure tab, un entier pour le joueur et deux entier pour les coordonnées
 */
struct tab toucherCouler(struct tab tab_t,int int_joueur,int int_x,int int_y){
	int int_direction = tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.int_dir;
	//----------Vérification des tirs sur le bateau-----------//
	if(int_direction==0){//Horizontal
		for (int int_i = 0; int_i <  tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.int_size; int_i++)
		{
			if(tab_t.ppstate_grid[int_joueur][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[0]+int_i][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[1]].int_tir==0){
			return(tab_t);//Non coulé
			}
		}
	}else{//Vertical
		for (int int_i = 0; int_i <  tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.int_size; int_i++)
		{
			if(tab_t.ppstate_grid[int_joueur][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[0]][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[1]-int_i].int_tir==0){
			return(tab_t);//Non coulé
			}
		}
	}
	//----------Mise à jour de touché à coulé d'un bateau-----------//
	if(int_direction==0){//Horizontal
		for (int int_i = 0; int_i <  tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.int_size; int_i++)
		{
			tab_t.ppstate_grid[int_joueur][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[0]+int_i][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[1]].int_hit=2;//coulé
		}
	}else{//Vertical
		for (int int_i = 0; int_i <  tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.int_size; int_i++)
		{
			tab_t.ppstate_grid[int_joueur][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[0]][tab_t.ppstate_grid[int_joueur<1?1:0][int_x][int_y].bateau.tint_coor[1]-int_i].int_hit=2;//coulé
		}
	}
	return(tab_t);//tout s'est bien passé
}


/*
 * Fonction viserTirer
 * But : Demander à l'utilisateur où il veut tirer sur la flotte ennemie
 * Sortie : une structure tab
 * Argument : une structure tab, le joueur actuel
 */
struct tab viserTirer(struct tab tab_t,int int_joueur){
	//----------Déclaration/initialisation des variables-----------//
	int int_posX,int_posY,int_ch,int_echec,int_ch2;
	int int_tabX=0,int_tabY=0,int_save=0;
	int_posX = 5;
 	int_posY = 3;
 	int_echec = 0;
	do{
		//----------Affichage des tirs possible/déjà effectué et de la légende-----------//
		clear();
		Affichage(tab_t,int_joueur,'t');
		printIndicationTir(tab_t,int_joueur);
	  	mvaddstr(12,COLS-25,"Partie non sauvegardée");//Partie non sauvegardée par défaut
	  	int_save=0;
	  	//----------Placement du curseur en haut à gauche du tableau-----------//
		/* Place le curseur à la position de départ et colore en fonction de la possibilité de tir*/
		if(tab_t.ppstate_grid[int_joueur][int_tabX][int_tabY].int_tir>0){
			setcolor(12,0);
	   		mvaddch(int_posY,int_posX,ACS_BULLET);
	   		unsetcolor(12,0);
		}else{
			setcolor(10,0);
	    	mvaddch(int_posY,int_posX,ACS_BULLET);
	    	unsetcolor(10,0);
		}
	  	refresh();

	/* Routine principale */
	  	while((int_ch = getch()) != 10) {
 		int_echec = 0;
	    /* On efface le curseur (on remplace par le caractère qui était censé être là*/
	  		mvaddch(int_posY,int_posX-1,' ');
	  		AffichageTir(tab_t,int_joueur,int_tabX,int_tabY);
	  		if(int_save==1){mvaddstr(12,COLS-25,"Partie sauvegardée    ");}//si la partie à été sauvegardée, on l'indique
	  		else{mvaddstr(12,COLS-25,"Partie non sauvegardée");}//sinon on l'indique aussi
		    /* On calcule la nouvelle position */
		    switch(int_ch){
		    case KEY_LEFT:
			    if(int_posX > 5){
			    	int_tabX-=1;
					int_posX-=4;
				}else{beep();}
			    break;
			case KEY_RIGHT:
				if(int_posX < 5+(4*(tab_t.int_wid-1))){
				    int_tabX+=1;
					int_posX+=4;
				}else{beep();}
				break;
			case KEY_UP:
				if(int_posY > 3){
				    int_tabY-=1;
					int_posY-=2;
				}else{beep();}
				break;
			case KEY_DOWN:
				if(int_posY < 1+(2*tab_t.int_len)){
					int_tabY+=1;
				    int_posY+=2;
				}else{beep();}
				break;
			//----------Sauvegarde lors de la pression de la touche 's'-----------//
			case 115://s
			case 83://S
				ecriture(tab_t,int_joueur);//sauvegarde dans un fichier binaire
				mvaddstr(12,COLS-25,"Partie sauvegardée    ");//Indication que la partie a été sauvegardée
				int_save=1;
				break;
			//----------Arrêt du programme si l'utilisateur presse 'q' puis 'o' pour valider-----------//
			case 113://q
			case 81://Q
				mvaddstr(12,COLS-25,"Etes-vous sûr ?(o/n): ");//Demande de validation de l'utilisateur
				int_ch2 = getch();
				if((int_ch2 == 111) || (int_ch2 == 79)){//Si la touche 'o' a été préssée alors on qui le programme
					clear();
					stop_ncurses();//Arrêt de ncurses
				///----------Désallocation du tableau-----------///
					for(int int_j=0;int_j<tab_t.int_wid;int_j++)
					{
						free(tab_t.ppstate_grid[0][int_j]);
						free((tab_t).ppstate_grid[1][int_j]);
					}
					free(tab_t.ppstate_grid[0]);
					free(tab_t.ppstate_grid[1]);
				///----------Fermeture forcée du programme-----------///
					exit(EXIT_SUCCESS);
				}
				break;
			//----------Affichage des tirs adverses sur nos bateau pour l'avancement de la partie lors de la pression sur 'w'-----------//
			case 119://w
			case 87://W
				clear();
				///----------Affichage des tirs ennemis sur nos bateaux-----------///
				Affichage(tab_t,int_joueur,'a');
				printIndicationTirAdverse();
				getch();
				clear();
				//---------- Re-Affichage du plateau de tir du joueur actuel-----------//
				Affichage(tab_t,int_joueur,'t');
				printIndicationTir(tab_t,int_joueur);
	  			mvaddstr(12,COLS-25,"Partie non sauvegardée");//par défaut partie non sauvegardée 

				break;
			//----------Si une autre touche a été préssée alors il ne se passe rien-----------//
			default:
				break;
			}

			/* On affiche le curseur à sa nouvelle position*/
			if(tab_t.ppstate_grid[int_joueur][int_tabX][int_tabY].int_tir>0){
				setcolor(12,0);
			   	mvaddch(int_posY,int_posX,ACS_BULLET);
			   	unsetcolor(12,0);
			}else{
				setcolor(10,0);
			   	mvaddch(int_posY,int_posX,ACS_BULLET);
			   	unsetcolor(10,0);
			}
			//----------Mise à jour de la fenêtre-----------//
		    refresh();
	 	}
	 	//----------Tir à un emplacement où l'on a déjà tiré-----------//
	 	if (tab_t.ppstate_grid[int_joueur][int_tabX][int_tabY].int_tir==1){
	 		beep();
	 		int_echec = 1 ;
	 	}else{
	 	//----------Mise à jour du tir-----------//
	 		tab_t.ppstate_grid[int_joueur][int_tabX][int_tabY].int_tir=1;
	 		clear();
	 		///----------Si l'on touche alors on affecte 1 à tir-----------///
	 		if(tab_t.ppstate_grid[int_joueur<1?1:0][int_tabX][int_tabY].bateau.int_size>0){
	 			tab_t.ppstate_grid[int_joueur][int_tabX][int_tabY].int_hit=1;
	 			tab_t.tint_nombreBateau[int_joueur]++;//augmentation de 1 du score
	 			tab_t = toucherCouler(tab_t,int_joueur,int_tabX,int_tabY); //Mise à jour si le bateau a été coulé
	 			if(tab_t.ppstate_grid[int_joueur][int_tabX][int_tabY].int_hit==1){
	 				///----------Bateau touché-----------///
	 				setcolor(12,0);
				    mvaddstr((LINES/2)-1,(COLS/2)-5,"BOOUUM !");
				    unsetcolor(12,0);
	 			}else{//Egal à 2 en théorie
	 				///----------Bateau coulé-----------///
	 				setcolor(13,0);
				    mvaddstr((LINES/2)-1,(COLS/2)-8,"GIGA BOOUUM !");
				    unsetcolor(13,0);
	 			}
	 		}else{
	 			///----------Tir dans l'eau-----------///
		 		setcolor(11,0);
			    mvaddstr((LINES/2)-1,(COLS/2)-4,"PLOUF !");
			    unsetcolor(11,0);
	 		}
	 		getch();
	 	}
	//----------On recommence tant qu'on a touché un bateau ennemi ou alors si on a gagné la partie-----------//
	}while(((tab_t.ppstate_grid[int_joueur<1?1:0][int_tabX][int_tabY].bateau.int_size>0) && (int_echec==0) && (tab_t.tint_nombreBateau[int_joueur]<tab_t.tint_nombreBateau[2])) || (int_echec==1));
	return(tab_t);
}


/*
 * Fonction ecriture
 * But : Sauvegarder les données de la partie actuelle dans un fichier en mode binaire
 * Sortie : une entier
 * Argument : une structure tab, le joueur actuel
 */
int ecriture(struct tab tab_t,int int_joueur){
	//----------Affectation des paramètre essentiels-----------//
	//dimensions de la grille, score des joueurs, joueur qui joue actuellement, si il existe un IA
	int tint_parametre[7] = { tab_t.int_wid, tab_t.int_len, tab_t.tint_nombreBateau[0], tab_t.tint_nombreBateau[1], tab_t.tint_nombreBateau[2], int_joueur,tab_t.int_IA};
	//----------Ouverture du fichier "BatailleNavale.save" en mode ecriture (écrasante) binaire-----------//
	FILE* file_fp = fopen("BatailleNavale.save", "wb");
	if (file_fp == NULL)
    {
        fprintf(stderr, "Le fichier BatailleNavale.save n'a pas pu être ouvert\n");
        exit(EXIT_FAILURE);//Erreur
    }
    //----------Ecriture des paramètres dans le fichier-----------//
    if (fwrite(&tint_parametre, sizeof(tint_parametre), 1, file_fp) != 1)
    {
            fprintf(stderr, "Erreur lors de l'écriture du tableau\n");
            exit(EXIT_FAILURE);//Erreur
    }
    //----------Ecriture de chaque case de chaque joueur du tableau dans le fichier-----------//
    for (int int_i = 0; int_i < tab_t.int_len; ++int_i)
    {
    	for (int int_j = 0; int_j < tab_t.int_wid; ++int_j)
    	{
    		if (fwrite(&tab_t.ppstate_grid[0][int_j][int_i], sizeof(tab_t.ppstate_grid[0][int_j][int_i]), 1, file_fp) != 1)//Case du joueur 1
   			{
   			stop_ncurses();
            fprintf(stderr, "Erreur lors de l'écriture du tableau\n");
            exit(EXIT_FAILURE);//Erreur
    		}
    		if (fwrite(&tab_t.ppstate_grid[1][int_j][int_i], sizeof(tab_t.ppstate_grid[1][int_j][int_i]), 1, file_fp) != 1)//Case du joueur 2
   			{
   			stop_ncurses();
            fprintf(stderr, "Erreur lors de l'écriture du tableau\n");
            exit(EXIT_FAILURE);//Erreur
   			}
    	}
    }
    //----------Fermeture du fichier-----------//
    if (fclose(file_fp) == EOF)//Fermeture quand on arrive à la fin du fichier
    {
    	stop_ncurses();
        fprintf(stderr, "Erreur lors de la fermeture du flux\n");
        exit(EXIT_FAILURE);//Erreur       
    }

return(EXIT_SUCCESS);//Tout s'est bien passé

}

/*
 * Fonction lecture
 * But : Recuperer les données d'une partie en lisant un fichier en mode binaire
 * Sortie : une entier
 * Argument : une structure tab, un pointeur pour renvoyer joueur auquel de jouer
 */
struct tab lecture(int *pint_joueur){
	int tint_parametre[7]; //Déclaration du tableau qui comprendra les paramètres
	struct tab tab_t; //Création de notre variable général comprennant toutes les informations du jeu
	//----------Lecture du fichier en mode binaire-----------//
	FILE* file_fp = fopen("BatailleNavale.save", "rb");
	if (file_fp == NULL)
    {
        fprintf(stderr, "Le fichier BatailleNavale.save n'a pas pu être ouvert\n");
        exit(EXIT_FAILURE);//Erreur
    }
    if (fread(&tint_parametre, sizeof(tint_parametre), 1, file_fp) != 1)//Affectation des 7 premiers entiers du fichier dans le tableau des paramètres
    {		
            fprintf(stderr, "Erreur lors de la lecture du tableau\n");
         exit(EXIT_FAILURE);//Erreur
    }
    //----------Affectation des paramètres à notre variable générale-----------//
    tab_t.int_wid=tint_parametre[0];//longueur
	tab_t.int_len=tint_parametre[1];//largeur
	tab_t.tint_nombreBateau[0]=tint_parametre[2];//score du joueur 1
	tab_t.tint_nombreBateau[1]=tint_parametre[3];//score du joueur 2
	tab_t.tint_nombreBateau[2]=tint_parametre[4];//nombre de case comprennant un bateau
	*pint_joueur = tint_parametre[5];//Joueur à qui c'était de jouer
	tab_t.int_IA = tint_parametre[6];//Existence d'un intelligence artificielle
		///----------Allocation nombre de joueur * pointeur de pointeur---------///
		tab_t.ppstate_grid=malloc(2*sizeof(struct state**));	
		///--------------Allocation nombre de colonne * pointeur ---------------///
			tab_t.ppstate_grid[0]=malloc(tab_t.int_wid*sizeof(struct state*));
			tab_t.ppstate_grid[1]=malloc(tab_t.int_wid*sizeof(struct state*));	
		///----------------Allocation nombre de ligne * state---------------///	
			for(int int_j=0;int_j<tab_t.int_wid;int_j++)
			{
				tab_t.ppstate_grid[0][int_j]=malloc(tab_t.int_len*sizeof(struct state));
				tab_t.ppstate_grid[1][int_j]=malloc(tab_t.int_len*sizeof(struct state));
			}

	//----------Affectation données dans chaque case du tableau-----------//
    for (int int_i = 0; int_i < tab_t.int_len; ++int_i)
    {
    	for (int int_j = 0; int_j < tab_t.int_wid; ++int_j)
    	{
    		if (fread(&tab_t.ppstate_grid[0][int_j][int_i], sizeof(tab_t.ppstate_grid[0][int_j][int_i]), 1, file_fp) != 1)
   			{
	            fprintf(stderr, "Erreur lors de la lecture du tableau\n");
	            exit(EXIT_FAILURE);//Erreur
    		}
    		if (fread(&tab_t.ppstate_grid[1][int_j][int_i], sizeof(tab_t.ppstate_grid[1][int_j][int_i]), 1, file_fp) != 1)
   			{	
	            fprintf(stderr, "Erreur lors de la lecture du tableau\n");
	            exit(EXIT_FAILURE);//Erreur
   			}
    	}
    }
    //----------Fermeture du fichier-----------//
    if (fclose(file_fp) == EOF)//Fermeture du fichier lorsqu'on arrive à la fin du fichier
    {
        fprintf(stderr, "Erreur lors de la fermeture du flux\n");
       exit(EXIT_FAILURE);//Erreur   
    }
    
return(tab_t);//Tout s'est bien passé

}


/*
 * Fonction batailleNavale
 * But : Cordonner les différentes fonctions du programme pour faire fonctionner le jeu
 * Sortie : un entier
 * Argument : aucun
 */
int batailleNavale(){
//------ Definition des paramètres -----------//
	char char_ch;
	struct tab tab_t;
	int int_joueur,int_gagnant,int_IALocal,int_difficultee=0;
	//------Lecture du fichier pour voir si il existe-----------//
	FILE * file_fichier = fopen("BatailleNavale.save", "r+");
	if (file_fichier == NULL)
	{	
		///------Si il n'existe pas alors définition des paramètres par l'utilisateur-----------///
		tab_t.ppstate_grid = NULL;
		tab_t = init(tab_t);
		do{
		printf("Veuillez indiquer s'il y a une IA (1) ou pas (0) : ");//Existence de l'IA
		int_IALocal = saisieEntier();
		}while((int_IALocal<0) ||(int_IALocal>1));
		tab_t.int_IA=int_IALocal;
		if(tab_t.int_IA==1){
			do{
			printf("Difficultée facile (0) ou moins facile (1) : ");//Difficulté de l'IA
			int_difficultee = saisieEntier();
			}while((int_difficultee<0) ||(int_difficultee>1));
		}
		tab_t = CreaBateau(tab_t);//Création et placement des bateaux
	}
	else
	{
	    /* Le fichier existe et on le referme aussitôt */
	    fclose(file_fichier);
	    //------Proposer de reprendre la partie sauvegardée-----------//
	    printf("Une sauvegarde existe, voulez-vous la charger (o/n): ");
	    scanf("%c",&char_ch);
	    if(char_ch=='o'){
	    	///------Si oui alors chargement et reprise de la partie grâce au fichier-----------///
	    	tab_t=lecture(&int_joueur);
	    	int_joueur = 1-int_joueur;
			CurseInit();
			/* Verification des dimensions du terminal */
			verifDimensionsBash(tab_t);
			/* Verification du support de la couleur */
			if(has_colors() == FALSE) {
				endwin();
				fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
				exit(EXIT_FAILURE);//ERreur
			}
			//Initialisation des couleurs ncurses
			start_color();
		    init_colorpairs();
	    }else{
	    	///------Si non alors redefinition des paramètres par l'utilisateur-----------///
	    	tab_t.ppstate_grid = NULL;
			tab_t = init(tab_t);
			do{
			printf("Veuillez indiquer s'il y a une IA (1) ou pas (0) : ");//Existence
			int_IALocal = saisieEntier();
			}while((int_IALocal<0) ||(int_IALocal>1));
			tab_t.int_IA=int_IALocal;
			if(tab_t.int_IA==1){
				do{
				printf("Difficultée facile (0) ou moins facile (1) : ");//Difficulté de l'IA
				int_difficultee = saisieEntier();
				}while((int_difficultee<0) ||(int_difficultee>1));
			}
			tab_t = CreaBateau(tab_t);//Création et placement des bateaux
	    }
	}

	//-------------Lancement du jeu-------------//
	while((tab_t.tint_nombreBateau[0]<tab_t.tint_nombreBateau[2]) && (tab_t.tint_nombreBateau[1]<tab_t.tint_nombreBateau[2])){
		int_joueur= int_joueur<1 ? 1:0;
		printJoueur(int_joueur);
		if((tab_t.int_IA==1) && (int_joueur==1))
		{
		///------l'IA tir-----------///
			tab_t=IA_TIRE(tab_t,int_difficultee);
			clear();
			Affichage(tab_t,1,'t');
			mvprintw(0,0,"Tableau de tir de l'IA");
			//Affichage des tirs de l'IA afin de mieux controler le déroulement du jeu
			printIndicationTir(tab_t,1);
			getch();
		}else{
		///------l'humain tir-----------///
			tab_t = viserTirer(tab_t,int_joueur);
		}
	}	
	//-------------Définition du joueur gagnant-------------//
	clear();
    mvaddstr(LINES / 2 - 1, COLS / 2 -17, "Le joueur gagnant est : ");
    if(tab_t.tint_nombreBateau[0]<tab_t.tint_nombreBateau[2]){
    	printw("Joueur 2");
    	int_gagnant = 2;
    }else{
    	printw("Joueur 1");
    	int_gagnant = 1;

    }
    getch();
	clrscr();
	//---------Désallocation du tableau--------//
	for(int int_j=0;int_j<tab_t.int_wid;int_j++)
		{
			free(tab_t.ppstate_grid[0][int_j]);
			free((tab_t).ppstate_grid[1][int_j]);
		}
	free(tab_t.ppstate_grid[0]);
	free(tab_t.ppstate_grid[1]);
	//--------FIN----------//
	stop_ncurses();
	//--------Affichage dans le terminal du joueur gagnant----------//
	printf("Le joueur gagnant est le joueur %d\n",int_gagnant);
	flash();

	
    return(EXIT_SUCCESS);
}


/*
 * Fonction IA_PROBA
 * But : Choisir un case non-vide aléatoirement
 * Sortie : les coordonnés d'une case non-vide choisi aléatoirement
 * Argument : un tableau d'entiers sa longueur et sa largeur
 */
int* IA_PROBA(int** ppint_t,int int_wid,int int_len)
{
	int ttint_c[int_wid*int_len][2];//tableau de coordonnées qui a au plus longueur*largeur case(s) non-vide
	int int_r;//nombre aléatoire
	int* int_temp;//coordonnées 
	int_temp=malloc(2*sizeof(int));//allocation;
	int int_count=0;
	for(int int_i=0;int_i<int_wid;int_i++)
	{
		for(int int_j=0;int_j<int_wid;int_j++)
		{
			if(ppint_t[int_i][int_j]!=0)
			{
				ttint_c[int_count][0]=int_i;//mise des coordonnées des cases non-vide dans notre tableau de coordonnées
				ttint_c[int_count][1]=int_j;
				int_count++;//nombre de case non-vide						
			}
		}
	}
		int_r=rand()%int_count;//nombre aléatoire entre 0 et int_count-1
		int_temp[0]=ttint_c[int_r][0];//on assigne ces coordonnés à int_temp et on les renvoi
		int_temp[1]=ttint_c[int_r][1];

	return(int_temp);//renvoi des coordonnés
}
/*
 * Fonction IA_PLACEMENT
 * But : choisir des coordonnées légale pour placer un bateau
 * Sortie : coordonnés légales choisi aléatoirement
 * Argument : une structure tab et la taille du bateau à placer
 */
int* IA_PLACEMENT(struct tab tab_t,int int_taille)
{	
	int** ppint_t;//tableau d'entier qui sera traité par IA_PROBA
	int* tint_temp;//coordonnées 

	tint_temp=malloc(3*sizeof(int));//allocation
	ppint_t=malloc(tab_t.int_wid*sizeof(int*));//allocation
	for  (int int_i=0;int_i<tab_t.int_wid;int_i++)
	{
		ppint_t[int_i]=malloc(tab_t.int_len*sizeof(int));//allocation
	}


	for (int int_i=0;int_i<tab_t.int_wid;int_i++)//on vérifie pour chaque case du tableau dans quelle sens un bateau d'une certaine taille pourrait être placé
	{
		for (int int_j=0;int_j<tab_t.int_len;int_j++) // 3=plaçable dans les deux sens 2=plaçable verticalement  1=plaçable horizontalement 0=n'est pas plaçable 
		{
			if ((def_x_y(tab_t,int_i,int_j,1,0,int_taille-1)==0)&&(def_x_y(tab_t,int_i,int_j,1,1,int_taille-1)==0))//on vérifie s'il est plaçable dans les deux sens
			{
				ppint_t[int_i][int_j]=3;
			}
			else if(def_x_y(tab_t,int_i,int_j,1,0,int_taille-1)==0)//plaçable seulement horizontalement
			{
				ppint_t[int_i][int_j]=1;
			}
			else if(def_x_y(tab_t,int_i,int_j,1,1,int_taille-1)==0)//plaçable seulement verticalement
			{
				ppint_t[int_i][int_j]=2;
			}
			else//n'est pas plaçable
			{	
				ppint_t[int_i][int_j]=0;
			}
		}
	}
	tint_temp=IA_PROBA(ppint_t,tab_t.int_wid,tab_t.int_len);//on  choisi des coordonnés aléatoire parmi celle possibles
	if (ppint_t[tint_temp[0]][tint_temp[1]]==1 )//on stocke la direction à coté des coordonnés dans la meme liste
	{
		tint_temp[2]=0;//horizontale
	}
	else if((ppint_t[tint_temp[0]][tint_temp[1]]==2 ))
	{
		tint_temp[2]=1;//verticale
	}
	else if((ppint_t[tint_temp[0]][tint_temp[1]]==3 ))
	{
		tint_temp[2]=rand()%2;//on choisit aléatoirement entre horizontale et verticale si les deux sont possibles
	}
	else//si le tableau est trop petit pour le nombre de bateau, on retourne une erreur
	{
		tint_temp[0]=-1;
		tint_temp[1]=-1;
		tint_temp[2]=-1;
		stop_ncurses();
		fprintf(stderr,"L'intelligence artificielle n'a pas réussi à organiser ses bateaux pour les placer correctement, veuillez exiger moins de bateau.");//impression d'une erreur
		exit(EXIT_FAILURE);
		return(tint_temp);
	}
	for  (int int_i=0;int_i<tab_t.int_wid;int_i++)//desallocation
	{
		free(ppint_t[int_i]);//de chaque lignes
	}	
	free(ppint_t);//de chaque colonnes
	return(tint_temp);
}
/*
 * Fonction IA_PLACE
 * But : retourne un tableau avec un bateau placé de plus qu'avant
 * Sortie : une structure tab tableau avec un bateau placé en plus
 * Argument : une structure tab et la taille du bateau à placer
 */
struct tab IA_PLACE(struct tab tab_t,int int_taille)
{

	int* pint_xyd=IA_PLACEMENT(tab_t,int_taille);//coordonnée données aléatoirement par rapport aux cases légales du tableau en argument
	int int_x=pint_xyd[0];//affectation a une autre variable 
	int int_y=pint_xyd[1];
	int int_direc=pint_xyd[2];
	
	for (int int_i=0;int_i<int_taille;int_i++)
	{
		if (int_direc==0)
		{	
			tab_t.ppstate_grid[1][int_x+int_i][int_y].bateau.tint_coor[0]=int_x;// on affecte chaque case sur la longueur du bateau en leur donnant les coordonnés de la case principale 
			tab_t.ppstate_grid[1][int_x+int_i][int_y].bateau.tint_coor[1]=int_y;			
			tab_t.ppstate_grid[1][int_x+int_i][int_y].bateau.int_dir=int_direc;//sa direction
			tab_t.ppstate_grid[1][int_x+int_i][int_y].bateau.int_size=int_taille;//sa taille				
		}	
		else
		{
			tab_t.ppstate_grid[1][int_x][int_y-int_i].bateau.tint_coor[0]=int_x;//meme chose pour l'autre direction
			tab_t.ppstate_grid[1][int_x][int_y-int_i].bateau.tint_coor[1]=int_y;			
			tab_t.ppstate_grid[1][int_x][int_y-int_i].bateau.int_dir=int_direc;
			tab_t.ppstate_grid[1][int_x][int_y-int_i].bateau.int_size=int_taille;						
		}
	}
	return(tab_t);
}

/*
 * Fonction RIA_VISE
 * But : choisir des coordonnées aléatoire sur lesquelles on peut tirer
 * Sortie : coordonnés légales choisi aléatoirement
 * Argument : une structure tab
 */
int* RIA_VISE(struct tab tab_t)
{
	int** ppint_t;//tableau de proba
	ppint_t=malloc(tab_t.int_wid*sizeof(int*));//allocation
	for  (int int_i=0;int_i<tab_t.int_wid;int_i++)
	{
		ppint_t[int_i]=malloc(tab_t.int_len*sizeof(int));//allocation
	}
	
	for(int int_i=0;int_i<tab_t.int_wid;int_i++)
	{
		for(int int_j=0;int_j<tab_t.int_len;int_j++)
		{
			if(tab_t.ppstate_grid[1][int_i][int_j].int_tir==0)// on vérifie si l'on à déja tiré sur cette case
			{				
				ppint_t[int_i][int_j]=1;//si non on mets la case correspondante dans notre tableau de proba à 1
			}
			else
			{
				ppint_t[int_i][int_j]=0;// si oui on la met à 0
			}
		}
	}
	int* pint_xy;//coordonnés aléatoire
	pint_xy=malloc(2*sizeof(int));//allocation 
	pint_xy= IA_PROBA(ppint_t,tab_t.int_wid,tab_t.int_len);//on calcule une coordonnée aléatoire en fonction du tableau de proba qu'on vient de créer
	return(pint_xy);// on les retourne
}
/*
 * Fonction IA_FINE
 * But : créer un tableau de proba(simple) par rapport à une case que l'on sait touchée
 * Sortie : tableau de proba(double liste dynamique d'entier)
 * Argument : une structure tab et la taille du bateau à placer
 */
int** IA_FINE(struct tab tab_t,int int_x,int int_y)
{
	int** ppint_t;//tableau de proba
	ppint_t=malloc(tab_t.int_wid*sizeof(int*));//allocation
	for  (int int_i=0;int_i<tab_t.int_wid;int_i++)
	{
		ppint_t[int_i]=malloc(tab_t.int_len*sizeof(int));//allocation
	}
		
	for(int int_i=0;int_i<tab_t.int_wid;int_i++)
	{
		for(int int_j=0;int_j<tab_t.int_len;int_j++)
		{
			ppint_t[int_i][int_j]=0;//initialisation du tableau à 0
		 }
	}
	int int_acc=0;//accumulateur stockant le nombre de tir possible
	// on vérifie dans chaque direction si l'on y a tiré 
	if(int_x<tab_t.int_wid-1)//on verifie si la case à droite existe 
	{
		if(tab_t.ppstate_grid[1][int_x+1][int_y].int_tir==0)// on verifie si on y a tiré
		{
			ppint_t[int_x+1][int_y]=1;
			int_acc +=1;//on incrémente l'accumulateur
		}	
	}
	if(int_x>0)//on verifie si la case à gauche existe
	{
		if(tab_t.ppstate_grid[1][int_x-1][int_y].int_tir==0)// on verifie si on y a tiré
		{
			ppint_t[int_x-1][int_y]=1;
			int_acc +=1;//on incrémente l'accumulateur
		}	
	}
	if(int_y<tab_t.int_len-1)//on verifie si la case en haut existe
	{
		if(tab_t.ppstate_grid[1][int_x][int_y+1].int_tir==0)// on verifie si on y a tiré
		{
			ppint_t[int_x][int_y+1]=1;
			int_acc +=1;//on incrémente l'accumulateur
		}
	}
	if(int_y>0)//on verifie si la case en bas existe
	{
		if(tab_t.ppstate_grid[1][int_x][int_y-1].int_tir==0)// on verifie si on y a tiré
		{
			ppint_t[int_x][int_y-1]=1;
			int_acc +=1;//on incrémente l'accumulateur
		}	
	}
	if (int_acc==0){ppint_t[0][0]=-1;}//si aucun tire n'est possible on mets la premiere case du tableau à -1
	return ppint_t;//on retourne le tableau de proba calculé
}


/*
 * Fonction IA_VISE
 * But : retourner une coordonné choisi de façcon plus optimisé que purement aléatoire
 * Sortie : coordonnées choisi de façon plus optimisées
 * Argument : une structure tab
 */
int* IA_VISE(struct tab tab_t)
{
	int** ppint_t;//tableau des tirs touchés
	int int_tempcount=0;//accumulateur comptant le nombre de bateau touchés  
	ppint_t=malloc(tab_t.int_wid*sizeof(int*));//allocation
	for  (int int_i=0;int_i<tab_t.int_wid;int_i++)
	{
		ppint_t[int_i]=malloc(tab_t.int_len*sizeof(int));//allocation
	}
	for(int int_i=0;int_i<tab_t.int_wid;int_i++) //on parcourt le tableau et mettons à 1 les cases correspondant à une case touchés
	{
		for(int int_j=0;int_j<tab_t.int_len;int_j++)
		{
			if(tab_t.ppstate_grid[1][int_i][int_j].int_hit==1)
			{	
				ppint_t[int_i][int_j]=1;//cette case correspond a une case touché
				int_tempcount++;//incrémentation de l'accumulateur
			}
			else
			{
				ppint_t[int_i][int_j]=0;//cette case ne correspond pas à une case touché
			}

		}

	}
	if(int_tempcount==0){return(RIA_VISE(tab_t));}// si l'accumulateur est nul ca veut dire qu'aucune case n'a été touché  donc on tire au hasard
	int* pint_rhit;//cordonnées aléatoire d'une case touchée
	int* pint_hit;//coordonnés de tir choisi de facon mieux optmisée
	pint_rhit=malloc(2*sizeof(int));// allocation
	pint_hit=malloc(2*sizeof(int));// allocation
	pint_rhit=IA_PROBA(ppint_t,tab_t.int_wid,tab_t.int_len);//on choisit aléatoirement une case touché 
	ppint_t=IA_FINE(tab_t,pint_rhit[0],pint_rhit[1]);//on stocke notre tableau de proba
	if(ppint_t[0][0]==-1){//si toutes  les cases du tableau de proba sont a 0
		pint_hit=RIA_VISE(tab_t);//on retourne une case aléatoire
		return(pint_hit);
	}
	pint_hit=IA_PROBA(ppint_t,tab_t.int_wid,tab_t.int_len);//on choisi aléatoirement une case autour d'une case touché
	return pint_hit;
}
/*
 * Fonction IA_TIRE
 * But : retourne un tableau avec un tir de plus qu'avant choisi selon une difficulté
 * Sortie : structure de tableau avec une case tiré de plus 
 * Argument : structure tab et un entier difficulté
 */
struct tab IA_TIRE(struct tab tab_t, int int_diff)
{
	int* pint_xy; //coordonnées de tir
	int int_verif=0;//=0 si n'a pas touché un bateau au tour d'avant =1 sinon
	pint_xy=malloc(2*sizeof(int));
	do{//on fait les instructions suivant au moins une fois
		int_verif=0;//on remet/met à 0 la variable verif
		if (int_diff==0)// si l'IA est aléatoire on choisi nos coordonnées aléatoirement
		{
			pint_xy=RIA_VISE(tab_t);//choisi aléatoirement
		}	
		else
		{
			pint_xy=IA_VISE(tab_t);//choisi de façon plus optimisée
		}
	tab_t.ppstate_grid[1][pint_xy[0]][pint_xy[1]].int_tir=1;//on tire sur la case choisi
	if(tab_t.ppstate_grid[0][pint_xy[0]][pint_xy[1]].bateau.int_size>0){//s'il y a un bateau au coordonnées de tir
		tab_t.ppstate_grid[1][pint_xy[0]][pint_xy[1]].int_hit=1;//on dit q'il est aussi touché
		int_verif=1;//on peut tirer à nouveau
	 	tab_t.tint_nombreBateau[1]++;//on augmente le score
	 	tab_t = toucherCouler(tab_t,1,pint_xy[0],pint_xy[1]);//on transforme les bateau touché sur toute leur longueur en bateau coulé
	}
	}while((int_verif==1) && (tab_t.tint_nombreBateau[1]<tab_t.tint_nombreBateau[2]));//on repète les instructions ci dessus si la partie n'est pas fini et que l'IA a touché un bateau 

	return tab_t;
}
