#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>
#include "Ecran.hpp"
#include "Utilities.hpp"
#include "Salle.hpp"
#include "Etage.hpp"
#include "Lecture.hpp"
#include <chrono>
#include <ctime>
#include <thread>
#include <random>
#include <algorithm>
#include <stdio.h> 
#include "Personnage.hpp"
#include "Monstre.hpp"


using namespace std;

int main() {

	lire_config();
	ranger_etages();
	
	int ind=0;
	numEtageCourant=laListeNumEtages[ind];

	int x0=lesEtages[numEtageCourant].lesSalles[0].coin00.x;
	int y0=lesEtages[numEtageCourant].lesSalles[0].coin00.y;
	int x1=lesEtages[numEtageCourant].lesSalles[0].coin11.x;
	int y1=lesEtages[numEtageCourant].lesSalles[0].coin11.y;
	int xp=(x1+x0)/2;
	int yp=(y1+y0)/2;
	
	set_etage_visible(numEtageCourant);
	joueur.set_nouvelle_position(xp,yp);
	int t;
	t=time(nullptr);
	char c;
	while(true) {
			system("stty raw");
			read(0,&c,1);
			
			//c=getchar();
			system("stty cooked");
			if (c=='&') break;
			else if (c=='r') {
				lesEtages[numEtageCourant].ruee_sur_joueur();
			}
			else if (c=='w') {
				lesEtages[numEtageCourant].attaque_de_joueur();
			}
			else if (c=='v') {
				joueur.rayon_decouverte=200;

			} else if (time(nullptr)-t>20) {
				lesEtages[numEtageCourant].ruee_sur_joueur();
				t=time(nullptr);
			}

			else {
				joueur.deplacer_joueur(c);
			}
			int fin=(int)lesEtages[numEtageCourant].lesMonstres.size();
			for (int i=0;i<fin;i++) {
				lesEtages[numEtageCourant].lesMonstres[i]->bouger();
			}
		}
	}

