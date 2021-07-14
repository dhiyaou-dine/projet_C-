
#include <iostream>
#include <fstream>

#include "cellule.h"
#include "maillage.h"
#include "lax_friedrichs.h"
using namespace std;


int main()
{

  Lax_Friedrichs LF(0.5,-2,2,100,0.01,0,0.005);//les paramètres sont(Tfin, Xdebut,Xfin, nombre de point initial du mailage,taile minimal d'une cellule, choix de la fonction initial,saut maximum ou raffiner)

    LF.solve();

    LF.saveMaillage();
 
    return 0;

}
