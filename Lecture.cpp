#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Lecture.hpp"
#include <chrono>
#include <ctime>
#include <thread>
#include <random>
#include <algorithm>
#include <vector>
#include "Ecran.hpp"
#include "Utilities.hpp"
#include "Salle.hpp"
#include "Etage.hpp"


using namespace std;


vector<Etage> lesEtages;
int numEtageCourant;
vector<int> listeNumEtages();
vector<int> laListeNumEtages;

void ranger_etages() {
	vector<int> rv=listeNumEtages();

	srand(unsigned(time(NULL)));
	std::random_shuffle(rv.begin(), rv.end() );
	int taille=(int)rv.size();
	if (taille==1) {
		lesEtages[rv[0]].numEtageSuperieur=-1;
		lesEtages[rv[0]].numEtageInferieur=-1;		
	}
	if (taille>1) {
		lesEtages[rv[0]].numEtageSuperieur=rv[1];
		lesEtages[rv[0]].numEtageInferieur=-1;
		lesEtages[rv[taille-1]].numEtageSuperieur=-1;
		lesEtages[rv[taille-1]].numEtageInferieur=rv[taille-2];		
	}
	for (int i=1;i<(int)rv.size()-1;i++) {
		lesEtages[rv[i]].numEtageSuperieur=rv[i+1];
		lesEtages[rv[i]].numEtageInferieur=rv[i-1];		
	}
	laListeNumEtages=rv;
}

int points_vie_monstres() {
	int res=0;
	for (int i=0;i<(int)lesEtages.size();i++) {
		int lim=(int)lesEtages[i].lesMonstres.size();
		for (int j=0;j<lim;j++) {
			res+=lesEtages[i].lesMonstres[j]->pointsVie;
		}
	}
	return res;
}


void rafraichir() {
	lesEtages[numEtageCourant].dessiner_etage();
	int fin=lesEtages[numEtageCourant].lesMonstres.size();
	for (int i=0;i<fin;i++) {
		int xval=lesEtages[numEtageCourant].lesMonstres[i]->x;
		int yval=lesEtages[numEtageCourant].lesMonstres[i]->y;
		lesEtages[numEtageCourant].lesMonstres[i]->set_nouvelle_position(xval,yval);
	}
	int taille=lesEtages.size();
	string stretage="",strvie="",strbesace="";
	stretage.append("Etage: ");
	stretage.append(to_string(numEtageCourant+1));
	stretage.append(" de ");
	stretage.append(to_string(taille));
	strvie.append("Points de vie: Joueur-> ");
	strvie.append(to_string(joueur.pointsVie));
	if (joueur.pointsVie<=0) {
		strbesace.append("YOU ARE DEAD!");
	}
	strvie.append("  Monstres-> ");
	int totmonstres=points_vie_monstres();
	strvie.append(to_string(totmonstres));
	if (totmonstres<=0) {
		strbesace.append("YOU WON!  temps passe:");
		int temps=time(nullptr)-topDepart;
		strbesace.append(to_string(temps));
		strbesace.append(" s");
	}	

	lecran.ecrire_etage(stretage);
	lecran.ecrire_vie(strvie);
	lecran.ecrire_besace(strbesace);
	lecran.afficher();
} 

void set_etage_visible(int num) {
	numEtageCourant=num;
	lecran.clear();
	lesEtages[numEtageCourant].dessiner_etage();
	int fin=lesEtages[numEtageCourant].lesMonstres.size();
	for (int i=0;i<fin;i++) {
		int xval=lesEtages[numEtageCourant].lesMonstres[i]->x;
		int yval=lesEtages[numEtageCourant].lesMonstres[i]->y;
		lesEtages[numEtageCourant].lesMonstres[i]->set_nouvelle_position(xval,yval);
	}
	int taille=lesEtages.size();
	string stretage,strvie,strbesace;
	stretage.append("Etage: ");
	stretage.append(to_string(numEtageCourant+1));
	stretage.append(" de ");
	stretage.append(to_string(taille));
	
	strvie.append("Points de vie: Joueur-> ");
	strvie.append(to_string(joueur.pointsVie));
	strvie.append("  Monstres-> ");
	strvie.append(to_string(points_vie_monstres()));

	lecran.ecrire_etage(stretage);
	lecran.ecrire_vie(strvie);
	lecran.afficher();
} 


ifstream monFlux("data.txt");
string stringlu;

void lire_portes(vector<Porte>& vp) {
	while (true) {
		Porte p;
		monFlux>>p.x; //cout<<p.x<<endl;
		monFlux>>p.y; //cout<<p.y<<endl;
		monFlux>>stringlu; //cout<<stringlu<<endl;
		if (stringlu=="HAUT") {p.o=HAUT;}
		else if (stringlu=="BAS") {p.o=BAS;}
		else if (stringlu=="DROITE") {p.o=DROITE;}
		else if (stringlu=="GAUCHE") {p.o=GAUCHE;}
		else {cout<<"Erreur lecture orientation porte"<<endl;}

		vp.push_back(p); //cout<<"j ajoute une porte"<<endl;
		monFlux>>stringlu; //cout<<stringlu<<endl;
		if (stringlu!="PORTE") {break;};
	}
	return;
}

void lire_etage(Etage& unEtage) {
	monFlux>>stringlu; //cout<<stringlu<<endl;
	while(true) {
		if (stringlu!="SALLE") {break;}
		Point p00,p11;
		vector<Porte> vp;
		monFlux>>p00.x; //cout<<p00.x<<endl;
		monFlux>>p00.y; //cout<<p00.y<<endl;
		monFlux>>p11.x; //cout<<p11.x<<endl;
		monFlux>>p11.y; //cout<<p11.y<<endl;
		monFlux>>stringlu;	//cout<<stringlu<<endl;	
		if (stringlu=="PORTE") {
			lire_portes(vp);
			//continue;
			}
		//else {
		//	lire_portes(vp);
		//}
		Salle uneSalle(p00,p11,vp);
		unEtage.ajouter_salle(uneSalle); //cout<<"j ajoute une salle"<<endl;		
	}
	return;
}

void lire_couloirs() {
	while(true) {
		int numetage1,numsalle1,numporte1;
		monFlux>>numetage1; //cout<<numetage1<<endl;
		monFlux>>numsalle1; //cout<<numsalle1<<endl;
		monFlux>>numporte1; //cout<<numporte1<<endl;

		int numetage2,numsalle2,numporte2;
		monFlux>>numetage2; //cout<<numetage2<<endl;
		monFlux>>numsalle2; //cout<<numsalle2<<endl;
		monFlux>>numporte2; //cout<<numporte2<<endl;

		int xJ,yJ;
		monFlux>>xJ; //cout<<xJ<<endl;
		monFlux>>yJ; //cout<<yJ<<endl;

		Porte p1=lesEtages[numetage1].lesSalles[numsalle1].lesPortes[numporte1];
		Porte p2=lesEtages[numetage2].lesSalles[numsalle2].lesPortes[numporte2];
		Couloir c={p1,p2,xJ,yJ};
		lesEtages[numetage1].ajouter_couloir(c);

		monFlux>>stringlu;	//cout<<stringlu<<endl;
		if (stringlu=="COULOIR") {
			continue;
			} else {break;}		
	}
	return;
	}

void lire_raptor(){
	int numetage, xval,yval;
	monFlux>>numetage;
	monFlux>>xval;
	monFlux>>yval;
	Raptor* raptor=new Raptor('?',DROITE);
	raptor->set_x(xval);
	raptor->set_y(yval);
	lesEtages[numetage].ajouter_monstre(raptor);
	monFlux>>stringlu;
}

void lire_diplodocus(){
	int numetage, xval,yval;
	monFlux>>numetage;
	monFlux>>xval;
	monFlux>>yval;
	Diplodocus* diplo=new Diplodocus('@',DROITE);
	diplo->set_x(xval);
	diplo->set_y(yval);
	lesEtages[numetage].ajouter_monstre(diplo);
	monFlux>>stringlu;
}

void lire_brontosaure(){
	int numetage, xval,yval;
	monFlux>>numetage;
	monFlux>>xval;
	monFlux>>yval;
	Brontosaure* bronto=new Brontosaure('%',DROITE);
	bronto->set_x(xval);
	bronto->set_y(yval);
	lesEtages[numetage].ajouter_monstre(bronto);
	monFlux>>stringlu;
}

void lire_tyranosaure(){
	int numetage, xval,yval;
	monFlux>>numetage;
	monFlux>>xval;
	monFlux>>yval;
	Tyranosaure* tyrano=new Tyranosaure('$',DROITE);
	tyrano->set_x(xval);
	tyrano->set_y(yval);
	lesEtages[numetage].ajouter_monstre(tyrano);
	monFlux>>stringlu;
}

void lire_iguanodon(){
	int numetage, xval,yval;
	monFlux>>numetage;
	monFlux>>xval;
	monFlux>>yval;
	Iguanodon* iguano=new Iguanodon('!',DROITE);
	iguano->set_x(xval);
	iguano->set_y(yval);
	lesEtages[numetage].ajouter_monstre(iguano);
	monFlux>>stringlu;
}

void lire_config() {
	if(monFlux) {
		monFlux>>stringlu; //cout<<stringlu<<endl;
        while (true) {
        	if (stringlu=="FIN") {break;}
       		if (stringlu=="ETAGE") {
       			Etage unEtage;  //cout<<"j ajoute un etage"<<endl;
       			lire_etage(unEtage); 
       			lesEtages.push_back(unEtage);
       			}
       		if (stringlu=="COULOIR") {
       			lire_couloirs();
       		}
       		if (stringlu=="RAPTOR") {
       			lire_raptor();
       		}
       		if (stringlu=="DIPLODOCUS") {
       			lire_diplodocus();
       		}
       		if (stringlu=="BRONTOSAURE") {
       			lire_brontosaure();
       		}
       		if (stringlu=="TYRANOSAURE") {
       			lire_tyranosaure();
       		}  
        	if (stringlu=="IGUANODON") {
       			lire_iguanodon();
       		}        		     		
         }
        
    	monFlux.close();
    	return;
	}else {
		cout<<"Erreur dans l ouverture du fichier"<<endl;
	}
}

vector<int> listeNumEtages() {
	vector<int> rv;
	for (int i=0;i<(int)lesEtages.size();i++) {
		rv.push_back(i);
	}
	return rv;
}

