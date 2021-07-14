#include <iostream>

#ifndef CELLULE_h

#define CELLULE_h



class Cellule{

  friend class Maillage;
	public :

	// attribut
  double m_a,m_b;

  double m_uin;

	// constructeur
  Cellule();// par defaut

  Cellule(const Cellule &c);// par copie

  Cellule(double inf, double sup, double valeur);// surcharge 

	// methodes
	
  void setValeur(double val); // ajoute d'une valeur

  void setInf(double inf);  // modification de la born inf 

  void setSup(double sup); // modification de la born sup
};



std::ostream &operator<<(std::ostream &ecrire, const Cellule &C);



#endif
