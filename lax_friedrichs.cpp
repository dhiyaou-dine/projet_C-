#include "lax_friedrichs.h"

#include <cmath>

// implémentation de la methode de resulation par lax_friendrichs

Lax_Friedrichs::Lax_Friedrichs(double Tfin,double inf, double sup,int nb_cell, double dx_crit, int n_fonc,double Eps)

{

    m_Tfin = Tfin;// temps maximal

    m_dx_crit = dx_crit;

    m_nFonc = n_fonc;//choix de la fonction

    m_Eps=Eps;// estimation de l'erreur



    a =4.;// coefficient pour la fonction a*u



    m_tmp = new Maillage(inf,sup,nb_cell);// allocation dynamique des maillages

    m_M = new Maillage(inf,sup,nb_cell);

    init_maill();

}



void Lax_Friedrichs::solve()

{

    double t=0;

    double dt;

    double Dx;

    std::vector<double> f_tmp;

    while(t<m_Tfin){

        this->Raffinement();// appelle de la methode de raffinement pour raffiner le mallage. 

        dt=get_dt();

        t=t+dt;

        f_tmp.reserve(m_M->getNbCell());

        f_tmp.resize(m_M->getNbCell());

        for( int i=0;i<m_M->getNbCell();i++){ //calcul les valeurs de f_i

            f_tmp.at(i) =fonc(m_M->getValeurCell(i));

        }

        for(int i=1; i<(m_M->getNbCell() - 1); i++)

        {

            double val;

            Dx=m_M->getDxCell(i);

            val=0.5*(m_M->getValeurCell(i+1)+m_M->getValeurCell(i-1))-0.5*dt/Dx*(f_tmp.at(i+1)-f_tmp.at(i-1));

            m_tmp->setValueCell(i, val);

        }

        std::swap(m_tmp, m_M);//Echange les deux maillages



    }

}

// implémentation de la methode de raffinement
// on peut la nigliger et resoudre le problème sur un maillage moins raffiner

void Lax_Friedrichs:: Raffinement(){

    for(int i=0; i<m_M->getNbCell()-1 ;i++){

        if(std::abs(m_M->getValeurCell(i)-m_M->getValeurCell(i+1))>m_Eps && m_M->getDxCell(i)>m_dx_crit){// on raffine le maillage sous certaines conditions

            double Val_i=m_M->getValeurCell(i);

            m_M->add_position(Val_i,i);

            m_tmp->add_position(Val_i,i);



            i++;

        }

    }



}




//Initialisation du maillage et choix de la fonction initiale



void Lax_Friedrichs::init_maill()

{

    if(m_nFonc==0){

        for(int i=0; i<m_M->getNbCell();i++){

            double mil;

            mil=m_M->getInfCell(i)+m_M->getDxCell(i)*0.5;

            m_M->setValueCell(i,std::sin(2.*mil*M_PI));

        }

    }

    else{



        for(int i=0; i<m_M->getNbCell();i++){

            double mil;

            mil=m_M->getInfCell(i)+m_M->getDxCell(i)*0.5;

            if(mil<-0.5 || mil>0.5){

                m_M->setValueCell(i,0);

            }

            else{

                m_M->setValueCell(i,1);

            }

        }

    }

}



//Choix de la fonction



double Lax_Friedrichs::fonc(double x)

{

    if(m_nFonc==0){

        return a*x;

    }

    else{

        return 0.5*x*x;

    }

}


// accès aucx attribut
double Lax_Friedrichs::get_dt()

{

    double dx_min=m_M->getDxCell(0);

    double u_max=m_M->getValeurCell(0);

    for (int i=1;i<m_M->getNbCell(); i++){

        if(u_max<m_M->getValeurCell(i)){

            if(m_nFonc==0){

                u_max=m_M->getSupCell(i);

            }

            else{

                u_max=a;

            }

        }

        if(dx_min>m_M->getDxCell(i)){

            dx_min=m_M->getDxCell(i);

        }

    }

    return dx_min/u_max;



}

double Lax_Friedrichs::get_Dx(){

    double dx_min=m_M->getDxCell(0);

    double u_max=m_M->getValeurCell(0);

    for (int i=1;i<m_M->getNbCell(); i++){

            if(dx_min>m_M->getDxCell(i)){

            dx_min=m_M->getDxCell(i);

        }

    }

    return dx_min;





}


// sauvegarde du maillage pour gnuplot
void Lax_Friedrichs::saveMaillage()

{

    std::ofstream f("resultat.dat");
    for(int i=0; i<m_M->getNbCell(); ++i)
    	{
    		f <<m_M->getInfCell(i) + m_M->getDxCell(i)/2.<<"\t";// on met une tabulation pour avoir deux colonnes en sortie
        f <<m_M->getValeurCell(i)<<std::endl;
      }
    f.close();


}
