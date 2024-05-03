/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Chomsky
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 22/11/2022
/// Archivo: produccion.h
/// Contiene la clase Produccion encargada de crear objetos tipo produccion y de proporcionar métodos para los mismos.

#include <iostream>
#include <set>
#include <vector>

#include "simbolo.h"

#ifndef PRODUCCION_H
#define PRODUCCION_H

/// @brief Clase Produccion, encargada de crear y manejar los objetos tipo produccion
class Produccion {  
 public:
  /// Constructor 
  Produccion() : simbolo_origen_{}, destino_produccion_{} {}

  /// Métodos para modificar los atributos de la clase Produccion
  void InsertaDestinoProduccion(const std::string& cadena);
  void InsertaOrigen(const Simbolo& simbolo);
  void LimpiaDestinoProduccion();

  /// Métodos para obtener información de los atributos de la clase Produccion
  int TamanioDestinoProduccion() const;

  /// Getters
  Simbolo get_simbolo_origen() const { return simbolo_origen_; }

  /// Sobrecarga de operadores
  std::string operator[](int posicion) const;
 private:
  Simbolo simbolo_origen_; ///< Atributo simbolo que define el "simbolo de arranque" de la producción
  std::vector<std::string> destino_produccion_; ///< Atributo tipo vector que contiene los simbolos que se sustituyen en la gramatica por el simbolo de origen
};

#endif