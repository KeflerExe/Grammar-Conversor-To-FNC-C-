/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramáticas
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 14/11/2022
/// Archivo: gramatica_func.cc
/// Contiene las diferentes funciones que son llamadas desde el main encargadas de realizar ciertas funciones

#include <iostream>
#include <string>
#include <cassert>

/// Comprueba que los argumentos introducidos por línea de comandos sean los 
/// correctos, además de proporcionar ayuda en caso de que el usuario no sepa como se han de introducir los argumentos.
void Usage(int argc, char *argv[]) {
  if (argc != 3) {
    std::string parametro_introducido = argv[1];
    if (parametro_introducido == "--help") {
      std::cout << "--Chomsky" << std::endl;
      std::cout << "Modo de uso: ./gramatica_main fichero_entrada_automata fichero_salida_gramatica" << std::endl;
      std::cout << "fichero_entrada_automata: Fichero de texto donde se define el autómata." << std::endl;
      std::cout << "fichero_salida_gramatica: Fichero de texto donde se escribe la gramática resultante." << std::endl;
      exit(EXIT_SUCCESS);
    } else {
      std::cout << "--Gramática " << std::endl;
      std::cout << "Modo de uso: ./gramatica_main fichero_entrada_automata fichero_salida_gramatica" << std::endl << "Pruebe ./gramatica_main --help para más información" << std::endl;
      exit(EXIT_FAILURE);
    }
  }   
}