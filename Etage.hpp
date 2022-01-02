#ifndef ETAGE_H
#define ETAGE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Utilities.hpp"
#include "Salle.hpp"
#include "Monstre.hpp"

class Etage {
public:
	vector<Salle> lesSalles;
	vector<Couloir> lesCouloirs;
	vector<Monstre*> lesMonstres;
	int numEtageSuperieur;
	int numEtageInferieur;
	int xS=-1,yS=-1,xI=-1,yI=-1;

	Etage() {}

	void ajouter_salle(Salle s);
	void ajouter_couloir(Couloir c);
	void ajouter_monstre(Monstre* m);
	void dessiner_etage();
	Monstre* monstre_devant_joueur(); 

	static void relier(Porte p1,Porte p2, int xJ,int yJ);
	static void trait_horizontal(int x0,int y0,int x1);
	static void trait_vertical(int x0,int y0,int y1); 
	static void trait_porte(Porte p1,int xJ,int yJ);

	void ruee_sur_joueur();
	void attaque_de_joueur();
};


#endif