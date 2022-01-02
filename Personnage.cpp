#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Personnage.hpp"
#include "Lecture.hpp"

using namespace std;

Joueur joueur('>',DROITE);

void Personnage::set_x(int xval) {
	x=xval;
}  

void Personnage::set_y(int yval) {
	y=yval;
} 

void Personnage::set_symbole(char s) {
	symbole=s;
}  

void Personnage::set_direction(Orientation d) {
	direction=d;
}
 
void Personnage::diminuer_points_vie(int v) {
	pointsVie-=v;
	if (pointsVie<=0) vivant=false;
}

void Personnage::augmenter_points_vie(int v) {
	pointsVie+=v;
}

void Personnage::set_nouvelle_position(int xnew,int ynew) {
	//if (!vivant) return;
	charCache=lecran.getchar_ecran(xnew,ynew);
	x=xnew;
	y=ynew;
	lecran.positionner(x,y,symbole);
	//lecran.set_vu(x,y,rayon_decouverte);
	lecran.afficher();
}

void Personnage::dessiner_personnage() {
	lecran.positionner(x,y,symbole);
	lecran.afficher();
}

bool Joueur::case_possible(int xnew,int ynew) {
	char c=lecran.getchar_ecran(xnew,ynew);
	if ((c=='.') || (c=='#') || (c=='P') || (c=='S') || (c=='I') || (c=='T')) {
		return true;
	}
	return false;
}

bool case_contrainte_ok(int xmin, int ymin, char char_contrainte) {
	char c=lecran.getchar_ecran(xmin,ymin);
	return (c==char_contrainte);
}

void Personnage::se_diriger_vers(int xcible,int ycible) {
	if (!vivant) return;
	int min; 
	bool bouge=false;
	int xmin,ymin,xessai,yessai,dist2;
	min=(x-xcible)*(x-xcible) + (y-ycible)*(y-ycible);

	xessai=x; yessai=y-1; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x; yessai=y+1; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x-1; yessai=y; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x-1; yessai=y-1; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x-1; yessai=y+1; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x+1; yessai=y; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x+1; yessai=y-1; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}
	xessai=x+1; yessai=y+1; 
	dist2=(xessai-xcible)*(xessai-xcible) + (yessai-ycible)*(yessai-ycible);
	if ((dist2<min) && case_possible(xessai,yessai)) {
		xmin=xessai; ymin=yessai; bouge=true;
	}



	if (bouge) {
		if (contrainte) {
				if (case_contrainte_ok(xmin,ymin,char_contrainte)) {
						lecran.positionner(x,y,charCache); 
						set_nouvelle_position(xmin,ymin);
				}

		} else {
			lecran.positionner(x,y,charCache); 
			set_nouvelle_position(xmin,ymin);
		}
	}
}

bool Personnage::tester_position(int xpos,int ypos) {
	return ((x==xpos) && (y==ypos));
}

void Personnage::placer_personnage_attaque(Orientation o) {
	if (!vivant) return;
	int h=lecran.get_hauteur();
	int l=lecran.get_largeur();
	int xnew,ynew;

	if (o==HAUT) {
		xnew=x;
		ynew=y-1; if (ynew<0) ynew=0;
	} else if (o==BAS) {
		xnew=x;
		ynew=y+1; if (ynew==h) ynew=h-1;
	} else if (o==GAUCHE) {
		xnew=x-1; if (xnew<0) xnew=0;
		ynew=y;
	} else if (o==DROITE) {
		xnew=x+1; if (xnew==l) xnew=l-1;
		ynew=y;
	}
	lecran.positionner(x,y,charCache); //retablir char cache
	set_nouvelle_position(xnew,ynew);
}

void Personnage::retour_personnage_attaque(Orientation o) {
	if (!vivant) return;
	int h=lecran.get_hauteur();
	int l=lecran.get_largeur();
	int xnew,ynew;

	if (o==HAUT) {
		xnew=x;
		ynew=y-1; if (ynew<0) ynew=0;
	} else if (o==BAS) {
		xnew=x;
		ynew=y+1; if (ynew==h) ynew=h-1;
	} else if (o==GAUCHE) {
		xnew=x-1; if (xnew<0) xnew=0;
		ynew=y;
	} else if (o==DROITE) {
		xnew=x+1; if (xnew==l) xnew=l-1;
		ynew=y;
	}
	lecran.positionner(x,y,'T'); //retablir char cache
	set_nouvelle_position(xnew,ynew);
}



void Personnage::deplacer_personnage(Orientation o) {
	if (!vivant) return;
	int h=lecran.get_hauteur();
	int l=lecran.get_largeur();
	int xnew,ynew;

	if (o==HAUT) {
		xnew=x;
		ynew=y-1; if (ynew<0) ynew=0;
	} else if (o==BAS) {
		xnew=x;
		ynew=y+1; if (ynew==h) ynew=h-1;
	} else if (o==GAUCHE) {
		xnew=x-1; if (xnew<0) xnew=0;
		ynew=y;
	} else if (o==DROITE) {
		xnew=x+1; if (xnew==l) xnew=l-1;
		ynew=y;
	}

	if (case_possible(xnew,ynew)) {
		lecran.positionner(x,y,charCache); //retablir char cache
		set_nouvelle_position(xnew,ynew);
	} else {
		lecran.positionner(x,y,symbole);
		lecran.afficher();
	}
}

void Joueur::diminuer_points_vie(int v) {
	pointsVie-=v;
	if (pointsVie<=0) {
		vivant=false;
	}
}


void Joueur::deplacer_joueur(char c) {
	if (!vivant) {
		dessiner_personnage();
		return;
	}

			if (c==UP) {
				if ((direction)==HAUT) deplacer_personnage(HAUT);
				set_symbole('^');
				set_direction(HAUT);
			} else if (c==DOWN) {
				if ((direction)==BAS) deplacer_personnage(BAS);
				set_symbole('V');
				set_direction(BAS);
			} else if (c==RIGHT) {
				if ((direction)==DROITE) deplacer_personnage(DROITE);
				set_symbole('>');
				set_direction(DROITE);
			} else if (c==LEFT) {
				if ((direction)==GAUCHE) deplacer_personnage(GAUCHE);
				set_symbole('<');
				set_direction(GAUCHE);
			}
			lecran.afficher();
			dessiner_personnage();	
			if ((x==lesEtages[numEtageCourant].xS) && (y==lesEtages[numEtageCourant].yS)) {
				changer_etage(lesEtages[numEtageCourant].numEtageSuperieur,HAUT);
			} else if ((x==lesEtages[numEtageCourant].xI) && (y==lesEtages[numEtageCourant].yI)) {
				changer_etage(lesEtages[numEtageCourant].numEtageInferieur,BAS);
			}
}

void Joueur::changer_etage(int numetage,Orientation d) {
	if (!vivant) return;
		set_etage_visible(numetage);
		int xloc=0,yloc=0;
		if (d==HAUT) {
			xloc=lesEtages[numetage].xI;
			yloc=lesEtages[numetage].yI;
			numSalle=lesEtages[numetage].lesSalles.size()-1;
		} else if (d==BAS) {
			xloc=lesEtages[numetage].xS;
			yloc=lesEtages[numetage].yS;
			numSalle=0;
		}
		numEtage=numetage;  //etage du joueur.... c est etageCourant...
		set_nouvelle_position(xloc,yloc);

}

void Joueur::set_nouvelle_position(int xnew,int ynew) {
	if (!vivant) return;
	charCache=lecran.getchar_ecran(xnew,ynew);
	x=xnew;
	y=ynew;
	lecran.positionner(x,y,symbole);
	lecran.set_vu(x,y,rayon_decouverte);
	lecran.afficher();
}