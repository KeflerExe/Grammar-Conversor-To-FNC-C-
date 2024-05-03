/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Chomsky
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 22/11/2022
/// Archivo: simbolo.h
/// Contiene la clase Simbolo encargada de crear objetos tipo simbolo y de proporcionar métodos para los mismos.

#include <iostream>

#ifndef SIMBOLO_H
#define SIMBOLO_H

/// @brief Clase Simbolo, encargada de crear y manejar los objetos tipo simbolo
class Simbolo {  
 public:
  /// Constructores
  Simbolo() : simbolo_{} {}
  Simbolo(const char simbolo) : simbolo_{simbolo} {}
  Simbolo(const std::string& cadena) : simbolo_{cadena[0]} {}

  /// Métodos que devuelven información de los atributos de la clase simbolo
  bool EsMayuscula() const;
  
  /// Getters
  char get_simbolo() const { return simbolo_; }

  /// Sobrecarga de operadores
  friend std::ofstream& operator<<(std::ofstream& salida, const Simbolo& simbolo);
 private:
  char simbolo_; ///< Atributo simbolo que define al propio simbolo 
};

bool operator==(const Simbolo& simbolo, const Simbolo& simbolo2);

#endif