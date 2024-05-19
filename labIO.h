#ifndef labIO
#define labIO

#include "lab.h"

void Show_Lab(laby &L);
void Verif_Lab(laby &L);
void Show_Case(int i, int j, Case c);
void Mark_Case(int li, int col);
void Mark_Case_Pile(pile &p);
void UMark_Case(int li, int col);
int LireCommande();
void InitCurses();
void EndCurses();

#endif
