#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Ecran.hpp"
#include "Utilities.hpp"

using namespace std;

Ecran lecran(130,40);
//Joueur joueur('>',DROITE);
int topDepart=time(nullptr);

Orientation direction_inverse(Orientation o) {
	if (o==HAUT) return BAS;
	if (o==BAS) return HAUT;
	if (o==DROITE) return GAUCHE;
	if (o==GAUCHE) return DROITE;
	return HAUT;  //pour plus de warning!
}