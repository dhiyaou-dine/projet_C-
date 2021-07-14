#ifndef MAILLAGE_H

#define MAILLAGE_H

#include <vector> // utilisation  de STL pour faciliter les manipulations

#include <iostream>


#include "cellule.h"

// Ici les prototypes des methodes de la clase maillage 

class Maillage

{

public:
		// Constructeurs

    Maillage(); // par defaut

    Maillage(double binf, double bsup, int nb_cell); // surchargé pour des cellules prés definies

    Maillage(const Maillage &m); //par recopie





    // MÉTHODES DE MODIFICATION

    // Ajout a une position

    void add_position(double valeur, int position);

    // Retrait a une position

    void remove_position(int position);

    // METHDOES DE CONSULTATION

    int consult_position(int position, int & valeur) const;

    // SURCHARGE D’OPERATEUR

    // Donner la valeur de u_i^n dans maille d’indice=position

    double operator[] (int position);



    int getNbCell() const; // returne  nombre de cellule

    double getInfCell(int i) const; // returne borne inf de la cellule

    double getSupCell(int i) const; // returne borne sup celule

    double getDxCell(int i) const; // retourne la taille de la cellule i

    double getValeurCell(int i) const; // numero cellule

    void setValueCell(int i, double val); // valeur de u_in dans la cellule selon la position



friend std::ostream & operator<<(std::ostream &ecrire, const Maillage &M);



protected:

    int nbr_cellules;

    // Nombre de cellules du maillage.

    std::vector<Cellule*> m_val; 

};
#endif 
