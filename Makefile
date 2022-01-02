CPP=g++ -std=c++11 -Wall

all : DnD

DnD : DnD.o Salle.o Etage.o Ecran.o Utilities.o Lecture.o Personnage.o Monstre.o Salle.hpp Ecran.hpp Utilities.hpp Etage.hpp Lecture.hpp Personnage.hpp Monstre.hpp
	$(CPP) -o DnD DnD.o Ecran.o Salle.o Etage.o Utilities.o Lecture.o Personnage.o Monstre.o

DnD.o : DnD.cpp Ecran.hpp Etage.hpp Personnage.hpp Monstre.hpp Utilities.hpp Salle.hpp Monstre.hpp
	$(CPP) -o DnD.o -c DnD.cpp

Ecran.o: Ecran.cpp Ecran.hpp Utilities.hpp Etage.hpp Personnage.hpp Lecture.cpp  Monstre.hpp
	$(CPP) -o Ecran.o -c Ecran.cpp

Salle.o: Salle.cpp Salle.hpp Utilities.hpp Etage.hpp Personnage.hpp Ecran.hpp Monstre.hpp
	$(CPP) -o Salle.o -c Salle.cpp

Etage.o: Etage.cpp Etage.hpp Utilities.hpp Salle.hpp Personnage.hpp  Ecran.hpp Lecture.cpp Monstre.hpp
	$(CPP) -o Etage.o -c Etage.cpp

Lecture.o: Lecture.cpp Lecture.hpp Utilities.hpp Salle.hpp Etage.hpp Personnage.hpp Ecran.hpp  Monstre.hpp
	$(CPP) -o Lecture.o -c Lecture.cpp

Utilities.o: Utilities.cpp Utilities.hpp Ecran.hpp Etage.hpp Personnage.hpp Lecture.cpp 
	$(CPP) -o Utilities.o -c Utilities.cpp

Personnage.o: Personnage.cpp Personnage.hpp Salle.hpp Ecran.hpp Utilities.hpp Etage.hpp Lecture.hpp Monstre.hpp
	$(CPP) -o Personnage.o -c Personnage.cpp	


Monstre.o: Monstre.cpp Monstre.hpp Salle.hpp Ecran.hpp Utilities.hpp Etage.hpp Lecture.hpp Personnage.hpp
	$(CPP) -o Monstre.o -c Monstre.cpp	

clean : 
	rm *.o testecran DnD
