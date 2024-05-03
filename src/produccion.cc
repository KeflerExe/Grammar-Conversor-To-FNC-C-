/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Chomsky
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 22/11/2022
/// Archivo: produccion.cc
/// Contiene la implementación de la clase Produccion encargada de proporcionar métodos para los objetos tipo produccion..

#include "produccion.h"

/// @brief Inserta los simbolos en el vector de destino de la produccion
/// @param cadena 
void Produccion::InsertaDestinoProduccion(const std::string& cadena) {
  destino_produccion_.push_back(cadena);
}

/// @brief Inserta los el "simbolo de arranque" de la produccion
/// @param simbolo 
void Produccion::InsertaOrigen(const Simbolo& simbolo) {
  simbolo_origen_ = simbolo;
}

/// @brief Sobrecarga del operador [] que retorna el valor del destino de la produccion en una determinada posición
/// @param posicion 
/// @return Retorna el elemento en la posicion definida del vector destino_produccion
std::string Produccion::operator[](int posicion) const {
  return destino_produccion_.at(posicion);
}

/// @brief Retorna el tamaño del destino de la producción
/// @return Retorna el tamaño del vector destino_produccion_
int Produccion::TamanioDestinoProduccion() const {
  return destino_produccion_.size();
}

/// @brief Elimina el contenido del destino de la producción
void Produccion::LimpiaDestinoProduccion() {
  destino_produccion_.clear();
  Simbolo simbolo_auxiliar;
  simbolo_origen_ = simbolo_auxiliar;
}