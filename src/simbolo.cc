/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Chomsky
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 22/11/2022
/// Archivo: simbolo.cc
/// Contiene la implementación de la clase Simbolo encargada de proporcionar métodos para los objetos tipo simbolo.

#include "simbolo.h"

/// @brief Sobrecarga del operador de salida
/// @param salida 
/// @param simbolo 
/// @return Retorna el objeto ofstream salida
std::ofstream& operator<<(std::ofstream& salida, const Simbolo& simbolo) {
  salida << simbolo.simbolo_;
  return salida;
}

/// @brief Devuelve true si el simbolo es mayuscula, false si no lo es
/// @return Retorna true si el simbolo es mayuscula
bool Simbolo::EsMayuscula() const {
  return isupper(simbolo_);
}

/// @brief Sobrecarga del operador ==
/// @param simbolo 
/// @param simbolo2 
/// @return Retorna true si los simbolos son iguales
bool operator==(const Simbolo& simbolo, const Simbolo& simbolo2) {
  if (simbolo.get_simbolo() == simbolo2.get_simbolo()) {
    return true;
  } else {
    return false;
  }
}
