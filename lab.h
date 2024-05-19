#ifndef lab
#define lab
#include <iostream>
using namespace std;

struct Case
{
    bool N,W,S,E; // Portes de la case bool marg; // True si on est déjà passé par la case (deplacement) 
    bool etat; // Quand on ouvre les portes (my creatton) 
    bool explore; // Pour trouver la solution du chemin (explore)
    bool minotaure;
};

struct laby
{
    int p; // Nombre de lignes du labyrinthe 
    int q; // Nombre de colonnes d du labyrinthe 
    Case **tab; // Tableau de structures "case"
};

struct couple
{
    int i; // numéro de la ligne
    int j; // numéro de la colonne
};

struct pile
{
    int nbe;// nombre d'éléments de la pile
    int taille; //taille de la pile
    couple *T; // Tableau de "couple"
};

#endif
