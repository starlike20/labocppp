.SILENT:

COMP=g++#D DEBUG
CLASSES=classes/
Test1: Test1.cpp objets/ImageNG.o
	echo creation de Test1
	g++ -o Test1 Test1.cpp  objets/ImageNG.o 
	#ne j'ai eu une erreur ici -o Test1 Test1

objets/ImageNG.o: $(CLASSES)ImageNG.cpp $(CLASSES)ImageNG.h
	echo creation de ImageNG.o
	g++ classes/ImageNG.cpp -c -o objets/ImageNG.o

clean:
	rm -f objets/*.o core

clobber:	clean
	rm -f Test1