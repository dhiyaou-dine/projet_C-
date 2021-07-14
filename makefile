exe : main.o cellule.o lax_friedrichs.o maillage.o 

	g++ -o exe main.o cellule.o lax_friedrichs.o maillage.o 

Cellule.o : cellule.cpp cellule.h

	g++ -c cellule.cpp -o cellule.o

Lax_friedrichs.o : cellule.h maillage.h lax_friedrichs.h lax_friedrichs.cpp

	g++ -c lax_friedrichs.cpp -o lax_friedrichs.o

Maillage.o :cellule.h maillage.h maillage.cpp

	g++ -c maillage.cpp -o maillage.o 

Main.o : main.cpp cellule.h

	g++ -c main.cpp -o Main.o

clean :

	rm *.o
