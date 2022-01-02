#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Utilities.hpp"
#include "Salle.hpp"
#include "Ecran.hpp"

using namespace std;


class Personnage {

	public:
		Orientation direction;
		bool vivant=true;
		int pointsVie=100;
		int pasPointsVie=100;
		int x=-1,y=-1;
		int numEtage=-1;
		int numSalle=-1;
		int numCouloir=-1;
		char symbole;
		char charCache;
		int rayon_decouverte=0;
		bool contrainte=false;
		char char_contrainte='.';  

		Personnage(char s,Orientation d){
			symbole=s;
			direction=d;
		}

		void set_symbole(char s);
		void set_x(int xval);
		void set_y(int yval);
		void set_direction(Orientation d);
		virtual void set_nouvelle_position(int x,int y);
		virtual bool case_possible(int xnew,int ynew)=0;
		void deplacer_personnage(Orientation o);
		void placer_personnage_attaque(Orientation o);
		void retour_personnage_attaque(Orientation o);
		//void deplacer_joueur(char c);
		void dessiner_personnage();
		void se_diriger_vers(int xcible,int ycible);
		bool tester_position(int xpos,int ypos);
		virtual void diminuer_points_vie(int v);
		void augmenter_points_vie(int v);
  
		  
  
};

class Joueur: public Personnage {
	public:
		void deplacer_joueur(char c);
		void changer_etage(int numetage,Orientation d);
		virtual void set_nouvelle_position(int x,int y);
		virtual bool case_possible(int xnew,int ynew);
		virtual void diminuer_points_vie(int v);
		Joueur(char s,Orientation d):Personnage(s,d){
			rayon_decouverte=30;
			pasPointsVie=15;
			pointsVie=80;
		}
	};

extern Joueur joueur;


#endif
