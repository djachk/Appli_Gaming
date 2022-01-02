#include <iostream>
#include <cstdlib>
#include <string>
#include "Salle.hpp"
#include "Ecran.hpp"


using namespace std;



void Salle::dessiner() {
	int deb,fin,trait;

	deb=coin00.x;
	fin=coin11.x;
	trait=coin00.y;
	for (int i=deb;i<=fin;i++) {
		lecran.positionner(i,trait,'-');
	}

	deb=coin00.y+1;
	fin=coin11.y;
	trait=coin11.x;
	for (int j=deb;j<=fin;j++) {
		lecran.positionner(trait,j,'|');
	}

	deb=coin00.y+1;
	fin=coin11.y;
	trait=coin00.x;
	for (int j=deb;j<=fin;j++) {
		lecran.positionner(trait,j,'|');
	}

	deb=coin00.x;
	fin=coin11.x;
	trait=coin11.y;

	for (int i=deb;i<=fin;i++) {
		lecran.positionner(i,trait,'-');
	}

	for (int i=coin00.x+1;i<=coin11.x-1;i++) {
			for (int j=coin00.y+1;j<=coin11.y-1;j++) {
				lecran.positionner(i,j,'.');	
			}
	}

	int nbportes=lesPortes.size();
	for (int i=0;i<nbportes;i++) {
		int x=lesPortes[i].x;
		int y=lesPortes[i].y;
		//Orientation o=lesPortes[i].o;
		lecran.positionner(x,y,'P');
	}


}

