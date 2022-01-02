#ifndef SALLE_H
#define SALLE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Utilities.hpp"

using namespace std;


class Salle {
	public:
		Point coin00,coin11;
		vector<Porte> lesPortes;
		
		Salle(Point coin00,Point coin11,vector<Porte> vp) {
			this->coin00=coin00;
			this->coin11=coin11;
			this->lesPortes=vp;
		}
        void dessiner();

};

#endif
