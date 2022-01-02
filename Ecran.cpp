#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include "Ecran.hpp"

using namespace std;


int Ecran::get_hauteur() {
	return hauteur;
}

int Ecran::get_largeur() {
	return largeur;
}


char Ecran::getchar_ecran(int x,int y) {
	return tab[x][y];
}

void Ecran::set_tableau() {
	tab=new char*[largeur];
	for(int i = 0; i < largeur; i++) {
    	tab[i] = new char[hauteur];
	}
	for (int i=0;i<largeur;i++) {
		for (int j=0;j<hauteur;j++) {
			tab[i][j]=' ';
		}
	}

	vu=new int*[largeur];
	for(int i = 0; i < largeur; i++) {
    	vu[i] = new int[hauteur];
	}
	for (int i=0;i<largeur;i++) {
		for (int j=0;j<hauteur;j++) {
			vu[i][j]=0;
		}
	}
	for (int i=0;i<largeur;i++) {
		vu[i][hauteur-2]=1;
	}	
}

void  Ecran::set_vu(int x0,int y0, int r) {
	for (int i=0;i<largeur;i++) {
		for (int j=0;j<hauteur;j++) {
			int d2=(i-x0)*(i-x0)+(j-y0)*(j-y0);
			if (d2<r*r) vu[i][j]=1;
		}
	}	
}	
    
void Ecran::ecrire_etage(string s) {
	effacer_ecrit(deb_ecrit_etage,fin_ecrit_etage);
	for (int i=0;i<(int)s.size();i++) {
		tab[deb_ecrit_etage+i][hauteur-2]=s[i];
	}
}

void Ecran::ecrire_vie(string s) {
	effacer_ecrit(deb_ecrit_vie,fin_ecrit_vie);
	for (int i=0;i<(int)s.size();i++) {
		tab[deb_ecrit_vie+i][hauteur-2]=s[i];
	}
}

void Ecran::ecrire_besace(string s) {
	effacer_ecrit(deb_ecrit_besace,fin_ecrit_besace);
	for (int i=0;i<(int)s.size();i++) {
		tab[deb_ecrit_besace+i][hauteur-2]=s[i];
	}
}

void Ecran::effacer_ecrit(int deb, int fin){
	for (int i=deb;i<fin;i++) {
		tab[i][hauteur-2]=' ';
	}
}


void Ecran::clear() {
	for (int i=0;i<largeur-1;i++) {
		for (int j=0;j<hauteur;j++) {
			tab[i][j]=' ';
		}
	}
	for (int i=0;i<largeur-1;i++) {
		for (int j=0;j<hauteur;j++) {
			vu[i][j]=0;
		}
	}
	for (int i=0;i<largeur;i++) {
		vu[i][hauteur-2]=1;
	}	
}

void Ecran::remplir() {
	for (int i=0;i<largeur;i++) {
		for (int j=0;j<hauteur;j++) {
			tab[i][j]='$';
		}
	}
	afficher();
}


void Ecran::positionner(int x,int y,char c) {
	tab[x][y]=c;
}

void Ecran::effacer(int x,int y) {
	tab[x][y]=' ';
}

void Ecran::afficher() {
	for (int i=0;i<60;i++) {
		cout<<endl;
	}		
	for (int j=0;j<hauteur;j++) {
		for (int i=0;i<largeur;i++) {
			if (i==0) {cout<<endl;}
				if (vu[i][j]==1) {cout<<tab[i][j];}
			else {cout<<" ";}
		}
	}
}
