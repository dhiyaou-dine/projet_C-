#include "maillage.h"


// Ici on implemente les methodes de la classe maillage les contructeurs y compris
//Constructeurs de maillage

Maillage::Maillage():nbr_cellules(0)
{

}


// on crée une cellule définie avec les valeurs de la constructeur surchargé
Maillage::Maillage(double binf, double bsup, int nbr_cell)
{

    double dx;

    dx = (bsup-binf)/static_cast<double>(nbr_cell);// pas de discretisation 

    nbr_cellules = nbr_cell;

    for (int i=0;i<nbr_cell;i++)
	{

        Cellule *tmp = new Cellule(binf + i*dx,binf + (i+1)*dx,0);

        m_val.push_back(tmp);// push_back, methode d'ajout à la fin de la liste

        if(i == nbr_cell-1)
        {

            tmp->setSup(bsup);



        }

    }



}

// construction par copie 
Maillage :: Maillage(const Maillage &m) 
{

    nbr_cellules = m.nbr_cellules;

}



//Ajoute une cellule au maillage

void Maillage::add_position(double valeur, int position)

{

    if(nbr_cellules == 0)

    {

        Cellule *tmp = new Cellule(0., 1., valeur);

        m_val.push_back(tmp);

        nbr_cellules++;

        return;

    }



    double inf = m_val.at(position)->m_a;

    double mid = ( inf + m_val.at(position)->m_b) / 2.;

    m_val.at(position)->setInf(mid);



    Cellule *tmp = new Cellule(inf, mid, valeur);



    m_val.insert(m_val.begin() + position, 1, tmp);

    nbr_cellules++;

}



// supression d'une cellule au maillage

void Maillage::remove_position(int position)

{

    double inf = m_val.at(position)->m_a;

    //Supprime la cellule alloué

    delete m_val.at(position);



    //Supprime la case du tableau avec la methode 'erase'

    m_val.erase( m_val.begin() + position);



    m_val.at(position)->setInf(inf);

    nbr_cellules--;

}



//retourne la valeur de la cellule ou -42 si la position n'est pas dans le maillage

double Maillage::operator[](int position)

{

    if( (position < 0) || (position >= nbr_cellules) )

        return -42.;

    return m_val.at(position)->m_uin;

}



// retourne le nombre de cellule du maillage

int Maillage::getNbCell() const

{

    return nbr_cellules;

}



//retourne la borne inf de la cellule i du maillagef

double Maillage::getInfCell(int i) const

{

    return m_val.at(i)->m_a;

}



//retourne la borne sup de la cellule i du maillage

double Maillage::getSupCell(int i) const

{

    return m_val.at(i)->m_b;

}



//retourne la taille de la cellule i

double Maillage::getDxCell(int i) const

{

    return getSupCell(i)-getInfCell(i);

}



//retourne la valeur de la cellule i

double Maillage::getValeurCell(int i) const

{

    return m_val.at(i)->m_uin;

}



//modifie la valeur de la cellule i 

void Maillage::setValueCell(int i, double val)

{

    m_val.at(i)->setValeur(val);

}



// surcharge de l'operateur affichage

std::ostream &operator<<(std::ostream &ecrire, const Maillage &M)

{

    for (int i=0; i<M.nbr_cellules; ++i)

    {

        ecrire << *M.m_val.at(i) << std::endl;

    }

    return ecrire;

}
