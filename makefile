all: gramatica_main

gramatica_main: gramatica_main.o gramatica_func.o gramatica.o produccion.o simbolo.o
	g++ -o gramatica_main gramatica_main.o gramatica_func.o gramatica.o produccion.o simbolo.o -std=c++2a

gramatica_func.o: gramatica_func.cc
	g++ -c -o gramatica_func.o gramatica_func.cc -std=c++2a

gramatica_main.o: gramatica_main.cc
	g++ -c -o gramatica_main.o gramatica_main.cc -std=c++2a

gramatica.o: gramatica.cc
	g++ -c -o gramatica.o gramatica.cc -std=c++2a

produccion.o: produccion.cc
	g++ -c -o produccion.o produccion.cc -std=c++2a

simbolo.o: simbolo.cc
	g++ -c -o simbolo.o simbolo.cc -std=c++2a

clean:
	-rm gramatica_main.o gramatica_func.o gramatica.o produccion.o simbolo.o gramatica_main