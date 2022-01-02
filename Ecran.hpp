#ifndef ECRAN_H
#define ECRAN_H

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Ecran {
	private:
		int hauteur,largeur;
		char** tab;
		int** vu;
		int deb_ecrit_etage=10,fin_ecrit_etage=30;
		int deb_ecrit_vie=35,fin_ecrit_vie=85;
		int deb_ecrit_besace=95,fin_ecrit_besace=120;

	public:
		Ecran(int l,int h) {
			hauteur=h;
			largeur=l;
			set_tableau();
		}
        //void set_hauteur(int h);
        int get_hauteur();
        int get_largeur();
        //void set_largeur(int l);
        void set_tableau();
        void clear();
        void positionner(int x,int y,char c);
        void effacer(int x,int y); 
        void afficher();
        void remplir();   

        char getchar_ecran(int x,int y);
        void set_vu(int x0,int y0, int r);
        void ecrire_etage(string s);
        void ecrire_vie(string s);
        void ecrire_besace(string s);
        void effacer_ecrit(int deb, int fin);
};

#endif
