#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Monstre.hpp"
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

void Monstre::courir() {
	
}

bool Monstre::case_possible(int xnew,int ynew) {
	char c=lecran.getchar_ecran(xnew,ynew);
	if ((c=='.') || (c=='#') || (c=='P') || (c=='S') || (c=='I')||(c=='T')) {
		return true;
	}
	return false;
}




void Raptor::courir(){
	se_diriger_vers(joueur.x,joueur.y);
}

void Raptor::bouger() {
}

void Raptor::subir_attaque(){
	diminuer_points_vie(pasPointsVie);
	joueur.diminuer_points_vie(joueur.pasPointsVie);
}



void Diplodocus::bouger() {
}

void Diplodocus::diminuer_points_vie(int v) {
	pointsVie-=v;
}

void Diplodocus::subir_attaque(){
	diminuer_points_vie(pasPointsVie);
	joueur.augmenter_points_vie(45);
}


void Brontosaure::bouger() {
	se_diriger_vers(joueur.x,joueur.y);
}

void Brontosaure::subir_attaque(){
	diminuer_points_vie(pasPointsVie);
	joueur.diminuer_points_vie(joueur.pasPointsVie);
}


void Tyranosaure::bouger() {
	se_diriger_vers(joueur.x,joueur.y);
}

void Tyranosaure::subir_attaque(){
	diminuer_points_vie(pasPointsVie);
	joueur.diminuer_points_vie(joueur.pasPointsVie);
}


void Iguanodon::bouger() {
	
}

void Iguanodon::subir_attaque(){
	diminuer_points_vie(pasPointsVie);
	joueur.diminuer_points_vie(joueur.pasPointsVie);
}
