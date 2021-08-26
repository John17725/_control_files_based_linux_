all:
	gcc -g -c -Wall prueba.c -o prueba.o
	gcc -g -Wall prueba.o -o ControlFile

clean:
	rm *.o
	rm ControlFile
