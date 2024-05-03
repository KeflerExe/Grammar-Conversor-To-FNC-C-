/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Chomsky
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 22/11/2022
/// Archivo: gramatica_main.cc
/// Contiene la función main del proyecto que usa las diferentes clases y llama a otras funciones
/// para realizar las operaciones requeridas por el usuario.

#include <iostream>
#include <fstream>

#include "gramatica.h"

/// @brief Función main encargada de crear la gramática correspondiente y de realizar las diferentes llamadas a funciones y métodos para obtener los resultados deseados por el usuario.
/// @param argc 
/// @param argv 
int main (int argc, char *argv[]) {
  Usage(argc, argv);
  std::string nombre_archivo_entrada = argv[1];
  std::string nombre_archivo_salida = argv[2];
  Gramatica gramatica1{nombre_archivo_entrada};
  gramatica1.ConvierteAFNC();
  std::ofstream archivo_gramatica_salida;
  archivo_gramatica_salida.open(nombre_archivo_salida);
  archivo_gramatica_salida << gramatica1;
  archivo_gramatica_salida.close();
  return 0;
}