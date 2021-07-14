#include "cellule.h"



//Constructeurs de cellule

Cellule::Cellule():m_a(-1.),m_b(1.), m_uin(0.) // surcharge
{

}

Cellule::Cellule(double inf, double sup, double valeur): m_a(inf),m_b(sup), m_uin(valeur)
{
	// on utilise ici une liste d'initialisation
	// donc on a besoin de rien entre les acolades
}



Cellule::Cellule(const Cellule &c):m_a(c.m_a), m_b(c.m_b), m_uin(c.m_uin) // par copie
{

}

 
// méthodes de modofication

void Cellule::setValeur(double val)  // modification de la valeur de la cellule
{
	m_uin = val;
}


void Cellule::setInf(double inf)  // modification de la borne inf
{
	m_a = inf;
}

 
void Cellule::setSup(double sup) // modification de la borne sup

{
	m_b = sup;
}



//Surcharge del'operateur d'affichage

std::ostream &operator<<(std::ostream &ecrire, const Cellule &C)

{

    ecrire << "[" << C.m_a << "," << C.m_uin << "," << C.m_b << "]";

    return ecrire;

}
