#include <ncurses.h>
#include "labIO.h"
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;



bool empile(pile & p, couple c)             // La fonction empiler ajoute un couple de coordonnées (c) au sommet d'une pile (p).
{
       if((p.nbe)<p.taille)                // Vérifie si la pile n'est pas pleine.
           {
            p.T[p.nbe]=c;                // Ajoute le couple c au tableau de couples dans la pile.
            (p.nbe)++;                  // Incrémente le nombre d'éléments dans la pile.
              return true;             // Renvoie true pour indiquer que l'ajout a été réussi.
                 }
                 else
                 {
                   cout<<"pile pleine"<<endl ;                // Si la pile est pleine, affiche un message d'erreur.
                     exit(1) ;                             // Quitte le programme 
                      }  
                        }
                        couple depiler(pile & p)              // La fonction depiler retire et renvoie le dernier couple ajouté à une pile.
                    {
                   if(p.nbe>0)                               // Vérifie si la pile contient au moins un élément.
                    {
                      p.nbe--;                                // Décrémente le nombre d'éléments dans la pile.
                      return(p.T[p.nbe]);                      // Retourne le dernier couple ajouté à la pile.
                        }
                  else
                       {                                     // Si la pile est vide, affiche un message d'erreur.
                           cout<<" pile vide"<<endl;
                            exit(1);                              // Quitte le programme
                            }
                        }
bool vide(pile & P)                                                // La fonction vide vérifie si une pile est vide.
{
if(P.nbe==0) return true;                                    // Si le nombre d'éléments dans la pile est égal à zéro, la pile est vide.
else return false;
}



void init(Case & c)                                      // La fonction init initialise une case avec des valeurs par défaut.
{
	c.N=c.S=c.E=c.W=false;                               // Initialise les murs dans toutes les directions à false.
	c.etat=false;                           // Initialise l'état de la case à false.
	c.explore=false;                               // Initialise l'exploration de la case à false.
}

void init(laby & L, int p, int q)
{
	L.p=p; L.q=q;                                     // Affecte le nombre de lignes (p) et de colonnes (q) au labyrinthe L.
	L.tab=new Case *[p];                              // Alloue dynamiquement un tableau de cases pour représenter le labyrinthe.
	for(int i=0;i<p;i++) L.tab[i]=new Case[q];
	for(int i=0;i<p;i++)                           // Initialise chaque case dans le labyrinthe en appelant la fonction init.
	{
		for(int j=0;j<q;j++) init(L.tab[i][j]);
	}
}

void init(pile & p, int taille)                          // La fonction init initialise une pile avec une taille donnée.

{
	p.taille=taille;                                  // Affecte la taille spécifiée à la pile.
	p.nbe=0;                                   // Initialise le nombre d'éléments dans la pile à zéro.
	p.T=new couple[taille];                            // Alloue dynamiquement un tableau de couples à la pile.
}
//Ces fonctions permettent de gérer une pile, une structure de données utilisée pour stocker les emplacements visités ou à visiter.
void empiler(pile &P, couple c)
{
    // Vérifier si la pile n'est pas pleine
    if (P.nbe < P.taille)
    {
        // Ajouter le couple à la position P.nbe du tableau
        P.T[P.nbe] = c;

        // Incrémenter le nombre d'éléments dans la pile
        P.nbe++;
    }
}

bool vide(const pile &P)
{
    // La fonction retourne true si le nombre d'éléments dans la pile est égal à zéro, sinon false.
    return P.nbe == 0;
}


void depiler(pile &P, couple &c) {
    // Vérifier si la pile n'est pas vide
    if (!vide(P)) {
        // Assigner la valeur du dernier élément de la pile à la variable 'c'
        c = P.T[P.nbe - 1];
        // Décrémenter le nombre d'éléments dans la pile
        P.nbe--;
    }
}





laby *lire_Laby(const char  *filename)
{
	ifstream my_cin;

	my_cin.open(filename);

	laby *L;
	L=new laby;
	my_cin>>(*L).p>>(*L).q;
	init((*L),(*L).p,(*L).q);

	for(int i=0;i<(*L).p;i++)
	{
		for(int j=0;j<(*L).q;j++)
		{
			my_cin>>(*L).tab[i][j].W>>(*L).tab[i][j].N>>(*L).tab[i][j].S>>(*L).tab[i][j].E;
		}
	}
	return L;
}



  


 void deplacement(laby & L, bool & f1, bool & lost) {
    int i, j;
    int p, q;
    int commande;
    p = L.p;
    q = L.q;
    i = 0;
    j = 0;

    // Marque la case de départ.
    Mark_Case(i, j);
    L.tab[i][j].etat = true;

    // Initialise les indicateurs de fin de jeu.
    lost = false;
    f1 = false;


    // Boucle principale du déplacement dans le labyrinthe.
    while (i != L.p - 1 || j != L.q - 1) {
        commande = LireCommande(); // Lit la commande du joueur.
        UMark_Case(i, j);

        if (commande == -1) { // Vérifie si le joueur a abandonné.
            f1 = true;
            lost = false;
            break;
            
        }


        // Déplacements possibles dans les différentes directions.
        if (commande== 3 && L.tab[i][j].E && j + 1 < q && !L.tab[i][j + 1].etat) {
            j++;
        } else if (commande == 6 && L.tab[i][j].S && i + 1 < p && !L.tab[i + 1][j].etat) {
            i++;
        } else if (commande == 9 && L.tab[i][j].W && j - 1 >= 0 && !L.tab[i][j - 1].etat) {
            j--;
        } else if (commande == 12 && L.tab[i][j].N && i - 1 >= 0 && !L.tab[i - 1][j].etat) {
            i--;
        } else if (commande == -1){

            EndCurses();
            cout << "Vous avez quitté le labyrinthe. Échec." << endl;
        }

        Mark_Case(i, j);
        L.tab[i][j].etat = true;
    }

    // Vérifie si le joueur est arrivé à la sortie du labyrinthe.
    if (i == L.p - 1 && j == L.q - 1 && !lost) {
        cout << "Félicitations ! Vous avez gagné !" << endl;
    } else if(!f1){
        cout << "Vous avez perdu !" << endl;
    
    }



    // Si on sort de la boucle, c'est parce que le joueur a abandonné
    if (f1) {
        cout << "Vous avez abandonné !" << endl;
    }
}









bool direction_possible(laby &L,int ligne,int colone,char & M)
{
	char a[4];
	int compt;  
	compt=0;
	if((ligne>0)&&(L.tab[ligne-1][colone].etat==false))
	{
		a[compt]='N';
		compt++;
		}
		if((ligne<L.p-1)&&(L.tab[ligne+1][colone].etat==false))
		{
			a[compt]='S';
			compt++;
		}
		if((colone>0)&&(L.tab[ligne][colone-1].etat==false))
		{
			a[compt]='W';
			compt++;
		}
		if((colone<L.q-1)&&(L.tab[ligne][colone+1].etat==false))
		{
			a[compt]='E';
			compt++;
		}
		
		if(compt==0)
		{
			return false;
		}
		else  {
			srand(time(NULL));
			M=a[rand()%compt];
			return true;
			}
	}

void direction_possible2(laby &L, int ligne, int colonne, char &M) {
	// Un tableau pour stocker les directions possibles.
    char a[4];
    int compt = 0;
    
	// Vérifie si le voisin au nord est possible et non visité.
    if (ligne > 0 && !L.tab[ligne - 1][colonne].explore && L.tab[ligne][colonne].N) {
        a[compt] = 'N';
        compt++;
    }
    // Vérifie si le voisin au sud est possible et non visité.
    if (ligne < L.p - 1 && !L.tab[ligne + 1][colonne].explore && L.tab[ligne][colonne].S) {
        a[compt] = 'S';
        compt++;
    }
    // Vérifie si le voisin à l'ouest est possible et non visité.
    if (colonne > 0 && !L.tab[ligne][colonne - 1].explore && L.tab[ligne][colonne].W) {
        a[compt] = 'W';
        compt++;
    }
    // Vérifie si le voisin à l'est est possible et non visité.
    if (colonne < L.q - 1 && !L.tab[ligne][colonne + 1].explore && L.tab[ligne][colonne].E) {
        a[compt] = 'E';
        compt++;
    }
    
    if (compt == 0) {
        M = '\0'; // Mise à jour de M pour indiquer aucune direction possible
    } else {
		// Si des voisins sont possibles, sélectionne aléatoirement une direction parmi eux.

        srand(time(NULL));
        M = a[rand() % compt];
    }
}



// La fonction prend en paramètres le labyrinthe L, les coordonnées k et k1 des deux cases adjacentes,
    // et la direction d (N, S, E, ou W) qui indique le côté à ouvrir.

    // Selon la direction, met à jour les murs entre les deux cases pour ouvrir un passage.
   

void ouvrir (laby &L,couple k,couple k1,char d)
{
	if(d=='N')
	{
		L.tab[k.i][k.j].N=true;// La case k a un mur au nord (N).
		L.tab[k1.i][k1.j].S=true;// La case k1 a un mur au sud (S).
	}
	
	if(d=='S')
	{
		L.tab[k.i][k.j].S=true; // La case k a un mur au sud (S).
		L.tab[k1.i][k1.j].N=true; // La case k1 a un mur au nord (N).
	}
	
	if(d=='E')
	{
		L.tab[k.i][k.j].E=true;   // La case k a un mur à l'est (E).
		L.tab[k1.i][k1.j].W=true;// La case k1 a un mur à l'ouest (W).
	}
	
	if(d=='W')
	{
		L.tab[k.i][k.j].W=true;  // La case k a un mur à l'ouest (W).
		L.tab[k1.i][k1.j].E=true;// La case k1 a un mur à l'est (E).
	}
}
	
laby * My_Creation(int p, int q) 
{// Initialisation de la graine pour la génération de nombres aléatoires.
	srand(time(NULL));
	char d;
	laby *L=new laby;// Création d'un nouveau labyrinthe.
	init (*L,p,q);

	pile *P = new pile;// Initialisation d'une pile pour le suivi du chemin de génération.
	init(*P,(p*q));

	couple k,k1; // Sélection aléatoire des coordonnées de départ.
	empiler(*P,k);// Empile la case de départ.
	L->tab[k.i][k.j].etat=true;

	// Boucle principale de génération du labyrinthe.
	while(!vide(*P))
	{
		depiler(*P,k);  
        L->tab[k.i][k.j].etat = true;  // Marque la case comme visitée   
		if(direction_possible(*L,k.i,k.j,d))        // Choix aléatoire d'une direction possible.
		{
			            // Calcul des coordonnées de la case voisine.
        if(d=='N')
        {
				k1.i=k.i-1;
				k1.j=k.j;
				ouvrir(*L,k,k1,d);            // Ouvre un passage entre la case courante et la case voisine.
			}
		if(d=='E')
			{
				k1.i=k.i;
				k1.j=k.j+1;
			    ouvrir(*L,k,k1,d);
			}
		if(d=='S')
			{
				k1.i=k.i+1;
				k1.j=k.j;
				ouvrir(*L,k,k1,d);
			}
	    if(d=='W')
			{
				k1.i=k.i;
				k1.j=k.j-1;
				ouvrir(*L,k,k1,d);            // Ouvre un passage entre la case courante et la case voisine.
			}
			L->tab[k1.i][k1.j].etat=true; // Marque la case voisine comme visitée.
			
			 // Empile les cases courante et voisine pour continuer la génération.
			empiler(*P,k);
			empiler(*P,k1);

		}
	}
	return L; // Retourne le labyrinthe généré.
}


pile explorer(laby &L)
{
	char r;
	pile A; // Initialisation de la pile pour suivre le chemin exploré.
	int t=L.p*L.q;
	init (A,t);
	couple s,s1;// Initialisation des couples pour représenter les coordonnées des cases.

	s.i=s1.i=0;
	s.j=s1.j=0;
	empiler(A,s);// Empile la case de départ et marque comme explorée.
	L.tab[s.i][s.j].explore=true;
	
	
	// Boucle principale de l'algorithme 
	while ((s1.i != L.p - 1) || (s1.j != L.q - 1)) {
    s = depiler(A);// Dépile la case courante.
    
	
	bool voisin_est_possible = false;// Variables pour stocker la direction choisie et vérifier la possibilité des voisins.
    
	
	direction_possible2(L, s.i, s.j, r); // Sélection aléatoire d'une direction possible.
    
	// Calcul des coordonnées de la case voisine selon la direction choisie.
	if (r == 'N') {
        s1.i = s.i - 1;
        s1.j = s.j;
        voisin_est_possible = true;
    } else if (r == 'E') {
        s1.i = s.i;
        s1.j = s.j + 1;
        voisin_est_possible = true;
    } else if (r == 'S') {
        s1.i = s.i + 1;
        s1.j = s.j;
        voisin_est_possible = true;
    } else if (r == 'W') {
        s1.i = s.i;
        s1.j = s.j - 1;
        voisin_est_possible = true;
    }
	        
			
	// Si un voisin est possible, empile la case courante et la case voisine.

    if (voisin_est_possible) {
        empiler(A, s);
        L.tab[s1.i][s1.j].explore = true;
        empiler(A, s1);
    }
}
// Retourne la pile qui contient le chemin exploré
 return A;
}
void affiche_chemin(pile&p,laby l)// Marque toutes les cases du labyrinthe comme non explorées
{
	for(int i=0;i<l.p;i++){
		for(int j=0;j<l.q;j++){
			UMark_Case(i,j);
			}
		}
	Mark_Case_Pile(p);    // Marque les cases du chemin exploré (extrait de la pile) comme explorées

}


void jeux()
{
    // Lecture du labyrinthe depuis un fichier texte
    laby *L1 = lire_Laby("laby.txt");

    // Exploration du labyrinthe pour trouver le chemin
    pile w = explorer(*L1);

    // Initialisation des indicateurs de jeu
    bool f1 = false;  // Indique si le joueur a abandonné
    bool lost = false; // Indique si le joueur a perdu

    // Initialisation de l'interface curses
    InitCurses();

    // Affichage du labyrinthe
    Show_Lab(*L1);

    // Déplacement du joueur dans le labyrinthe
    deplacement(*L1, f1, lost);

    // Gestion des cas où le joueur a abandonné ou perdu
    if (f1 == true || lost == true)
    {
        // Affiche le chemin exploré en cas d'abandon
        if (f1 == true)
        {
            affiche_chemin(w, *L1);
            EndCurses();
            cout << "Vous avez quitté le labyrinthe. Échec." << endl;
        }
        
        // Termine le programme si le joueur a perdu
        if (lost == true)
        {
            EndCurses();
            cout <<  "   Partie interrompue. Échec      " << endl;
            exit(1);
        }
    }

    // Si le joueur n'a ni abandonné ni perdu, affiche un message de échec
    {
        EndCurses();
        cout << " Félicitation, Vous avez trouvé la sortie !" << endl;
    }

     // Libérer la mémoire allouée pour le labyrinthe et le chemin
    delete L1;
     // Attendre une entrée de l'utilisateur avant de quitter
    getch();

    // Terminer l'interface utilisateur curses
    EndCurses();
}


int main()
{
 // Appelle la fonction principale du jeu
    jeux();

//laby *L1=lire_Laby("laby.txt");
    laby *L1 = My_Creation(10, 10);


     // Explorer le labyrinthe pour trouver le chemin
    pile w = explorer(*L1);

    // Appel explicite de la fonction init pour initialiser l'objet laby
    //init(*L1, 10, 10);



    InitCurses();
    Show_Lab(*L1);
    //deplacement (*L1);
    wgetch(stdscr);
	EndCurses();

    // Assurez-vous de libérer la mémoire si vous utilisez des pointeurs
    delete L1; // À utiliser si L1 est alloué dynamiquement avec new

    return 0;
}