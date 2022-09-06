all:
	gcc -c *.c
	gcc compacta.o arvore.o lista.o bitmap.o -o compacta
	gcc descompacta.o arvore.o lista.o bitmap.o -o descompacta

clean: 
	rm *.o
	rm compacta
	rm descompacta

run_compacta:
	./compacta teste.txt

run_descompacta:
	./descompacta teste.comp

