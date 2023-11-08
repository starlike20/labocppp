.SILENT:

COMP=g++ -D DEBUG
CLASSES=classes/
Test2: Test2.cpp objets/ImageNG.o objets/Dimension.o
	echo creation de Test2
	$(COMP) -o Test2 Test2.cpp objets/ImageNG.o objets/Dimension.o  
	#ne j'ai eu une erreur ici -o Test1 Test1

objets/ImageNG.o: $(CLASSES)ImageNG.cpp $(CLASSES)ImageNG.h
	echo creation de ImageNG.o
	$(COMP) classes/ImageNG.cpp -c -o objets/ImageNG.o

objets/Dimension.o:$(CLASSES)Dimension.cpp $(CLASSES)Dimension.h
	echo creation de Dimension.o
	$(COMP) classes/Dimension.cpp -c -o objets/Dimension.o

clean:
	rm -f objets/*.o core

clobber:	clean
	rm -f Test1