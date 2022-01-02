#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "Etage.hpp"
#include "Ecran.hpp"
#include "Lecture.hpp"

void Etage::ajouter_salle(Salle s) {
	lesSalles.push_back(s);
}

void Etage::ajouter_couloir(Couloir c) {
	lesCouloirs.push_back(c);
}

void Etage::ajouter_monstre(Monstre* m) {
	lesMonstres.push_back(m);
}

Monstre* Etage::monstre_devant_joueur() {
		if (joueur.direction==HAUT) {
			for (int i=0;i<(int)lesMonstres.size();i++) {
				if ((lesMonstres[i]->x==joueur.x) && (lesMonstres[i]->y==joueur.y-1) && lesMonstres[i]->vivant) return lesMonstres[i];
			}
		}
		if (joueur.direction==BAS) {
			for (int i=0;i<(int)lesMonstres.size();i++) {
				if ((lesMonstres[i]->x==joueur.x) && (lesMonstres[i]->y==joueur.y+1) && lesMonstres[i]->vivant) return lesMonstres[i];
			}
		}
		if (joueur.direction==DROITE) {
			for (int i=0;i<(int)lesMonstres.size();i++) {
				if ((lesMonstres[i]->x==joueur.x+1) && (lesMonstres[i]->y==joueur.y) && lesMonstres[i]->vivant) return lesMonstres[i];
			}
		}
		if (joueur.direction==GAUCHE) {
			for (int i=0;i<(int)lesMonstres.size();i++) {
				if ((lesMonstres[i]->x==joueur.x-1) && (lesMonstres[i]->y==joueur.y) && lesMonstres[i]->vivant) return lesMonstres[i];
			}
		}
		return nullptr;
}


void Etage::attaque_de_joueur() {
	Monstre* m=monstre_devant_joueur();
	if (m!=nullptr) {
		joueur.placer_personnage_attaque(joueur.direction);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		Orientation omoins=direction_inverse(joueur.direction);
		m->vivant=false;
		m->set_symbole('T');
		m->subir_attaque();
		rafraichir();
		joueur.retour_personnage_attaque(omoins);
	}
}

void Etage::dessiner_etage() {
	for(int i=0;i<(int)lesSalles.size();i++) {
		lesSalles[i].dessiner();
	}
	for(int i=0;i<(int)lesCouloirs.size();i++) {
		Porte p1=lesCouloirs[i].p1;
		Porte p2=lesCouloirs[i].p2;
		int xJ=lesCouloirs[i].xJ;
		int yJ=lesCouloirs[i].yJ;
		relier(p1,p2,xJ,yJ);
	}
	if (numEtageSuperieur!=-1) {
		xS=lesSalles[0].coin00.x+1;
		yS=lesSalles[0].coin00.y+1;
		lecran.positionner(xS,yS,'S');
	}
	if (numEtageInferieur!=-1) {
		int ind=lesSalles.size()-1;
		xI=lesSalles[ind].coin11.x-1;
		yI=lesSalles[ind].coin11.y-1;
		lecran.positionner(xI,yI,'I');
	}	
}

void Etage::trait_horizontal(int x0,int y0,int x1) {
	if (x1>=x0) {
		for(int i=x0;i<=x1;i++) {
			lecran.positionner(i,y0,'#');
		}
	} else {
		for(int i=x1;i<=x0;i++) {
			lecran.positionner(i,y0,'#');
		}
	}
  }

void Etage::trait_vertical(int x0,int y0,int y1) {
	if (y1>=y0) {
		for(int j=y0;j<=y1;j++) {
			lecran.positionner(x0,j,'#');
		}
	} else {
		for(int j=y1;j<=y0;j++) {
			lecran.positionner(x0,j,'#');
		}
	}
  }


void Etage::trait_porte(Porte p1,int xJ,int yJ) {
		if (p1.o==HAUT) {
			trait_vertical(p1.x,p1.y-1,p1.y-3);
			trait_horizontal(p1.x,p1.y-3,xJ);
			trait_vertical(xJ,p1.y-3,yJ);
		} else if (p1.o==BAS) {
			trait_vertical(p1.x,p1.y+1,p1.y+3);
			trait_horizontal(p1.x,p1.y+3,xJ);
			trait_vertical(xJ,p1.y+3,yJ);			
		} else if (p1.o==GAUCHE) {
			trait_horizontal(p1.x-1,p1.y,p1.x-3);
			trait_vertical(p1.x-3,p1.y,yJ);
			trait_horizontal(p1.x-3,yJ,xJ);
		} else if (p1.o==DROITE) {
			trait_horizontal(p1.x+1,p1.y,p1.x+3);
			trait_vertical(p1.x+3,p1.y,yJ);
			trait_horizontal(p1.x+3,yJ,xJ);

		} else {
			cout<<"erreur dans relier porte"<<endl;
		}	
}



void Etage::relier(Porte p1,Porte p2,int xJ,int yJ) { //x0,y0 point de jonction
		trait_porte(p1,xJ,yJ);
		trait_porte(p2,xJ,yJ);
	}


  
void Etage::ruee_sur_joueur() {
 fd_set ensemble;
 int nset; 
 char c;

  for(int i=0;i<100;i++) {
    FD_ZERO(&ensemble);
    FD_SET(0,&ensemble);
    system("stty raw");
    struct timeval t;
 	t.tv_sec = 0;
 	t.tv_usec = 500000;
    nset=select(1,&ensemble,NULL,NULL,&t);
    if (nset>0) {
      if(FD_ISSET(0,&ensemble)) {
			read(0,&c,1);
			if (c=='q') {break;}
			else if (c=='w') {
				system("stty cooked");
				lesEtages[numEtageCourant].attaque_de_joueur();
			} else {
				system("stty cooked");
				joueur.deplacer_joueur(c);
				}
		}
	}
	system("stty cooked");
	int fin=(int)lesEtages[numEtageCourant].lesMonstres.size();
	for (int i=0;i<fin;i++) {
		lesEtages[numEtageCourant].lesMonstres[i]->courir();
	}
  }
 system("stty cooked");
}
  