#ifndef MONSTRE_H
#define MONSTRE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include "Utilities.hpp"
//#include "Salle.hpp"
//#include "Etage.hpp"
//#include "Ecran.hpp"
//#include "Lecture.hpp"
#include "Personnage.hpp"

using namespace std;


class Monstre: public Personnage {
	public:
		Monstre(char s,Orientation d):Personnage(s,d){}
		virtual void courir();
		virtual void bouger()=0;
		virtual bool case_possible(int xnew,int ynew);
		virtual void subir_attaque()=0;
		
};

class Raptor: public Monstre { //court vite = '?''
	public:
		Raptor(char s,Orientation d):Monstre(s,d){
			pasPointsVie=100;
		}
		virtual void courir();
		virtual void bouger();
		virtual void subir_attaque();
};


class Diplodocus: public Monstre {  //immobile ='@'
	public:
		Diplodocus(char s,Orientation d):Monstre(s,d){
			pasPointsVie=100;
			contrainte=true;
			char_contrainte='X'; //ne peut pas bouger...
		}
		virtual void bouger();
		virtual void diminuer_points_vie(int v);
		virtual void subir_attaque();
};

class Brontosaure: public Monstre {  // salle ='%'
	public:
		Brontosaure(char s,Orientation d):Monstre(s,d){
			pasPointsVie=100;
			contrainte=true;
			char_contrainte='.';
		}
		virtual void bouger();
		virtual void subir_attaque();
};


class Tyranosaure: public Monstre {  // couloir = '$'
	public:
		Tyranosaure(char s,Orientation d):Monstre(s,d){
			pasPointsVie=100;
			contrainte=true;
			char_contrainte='#';
		}
		virtual void bouger();
		virtual void subir_attaque();
};


class Iguanodon: public Monstre {  // se teleporte = '!'
	public:
		Iguanodon(char s,Orientation d):Monstre(s,d){
			pasPointsVie=100;
			contrainte=true;
			char_contrainte='X';  //ne bouge pas
		}
		virtual void bouger();
		virtual void subir_attaque();
};


#endif  