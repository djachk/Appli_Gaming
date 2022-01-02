#ifndef LECTURE_H
#define LECTURE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include "Etage.hpp"
//#include "Monstre.hpp"

using namespace std;

void lire_config();

extern vector<Etage> lesEtages;
extern int numEtageCourant;

void set_etage_visible(int num);
void rafraichir();
void ranger_etages();

extern vector<int> listeNumEtages();
extern vector<int> laListeNumEtages;

#endif