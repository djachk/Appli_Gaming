#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Ecran.hpp"
//#include "Personnage.hpp"
//#include "Salle.hpp"
//#include "Etage.hpp"
//#include "Lecture.hpp"
#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68

using namespace std;  

enum Orientation {
	HAUT,BAS,DROITE,GAUCHE
};
typedef enum Orientation Orientation;

struct Porte {
	int x;
	int y;
	Orientation o;
};
typedef struct Porte Porte;

struct Couloir {
	Porte p1;
	Porte p2;
	int xJ;  //point de jonction
	int yJ;
};
typedef struct Couloir Couloir;

struct Point {
	int x;
	int y;
};
typedef struct Point Point;

Orientation direction_inverse(Orientation o);

extern int topDepart;
extern Ecran lecran;
//extern Joueur joueur;

#endif