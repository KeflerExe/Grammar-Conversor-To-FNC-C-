/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 8: Chomsky
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 22/11/2022
/// Archivo: gramatica.cc
/// Contiene la implementacion de la clase Gramatica encargada de proporcionar métodos para los objetos tipo gramatica.

#include "gramatica.h"

/// @brief Constructor de la clase Gramatica que recibe el nombre de un fichero con la defininición de una gramática 
/// @param nombre_archivo_entrada 
Gramatica::Gramatica(const std::string& nombre_archivo_entrada) {
  std::ifstream archivo_entrada;
  std::string linea_extraida_archivo;
  archivo_entrada.open(nombre_archivo_entrada);
  getline(archivo_entrada, linea_extraida_archivo);
  int cantidad_simbolos_terminales = std::stoi(linea_extraida_archivo);
  Simbolo simbolo_auxiliar;
  for (int iterador = 0; iterador < cantidad_simbolos_terminales; ++iterador) {
    getline(archivo_entrada, linea_extraida_archivo);
    simbolo_auxiliar = linea_extraida_archivo;
    terminales_.push_back(simbolo_auxiliar);
  }
  getline(archivo_entrada, linea_extraida_archivo);
  int cantidad_simbolos_no_terminales = std::stoi(linea_extraida_archivo);
  for (int iterador = 0; iterador < cantidad_simbolos_no_terminales; ++iterador) {
    getline(archivo_entrada, linea_extraida_archivo);
    simbolo_auxiliar = linea_extraida_archivo;
    no_terminales_.push_back(simbolo_auxiliar);
  }
  getline(archivo_entrada, linea_extraida_archivo);
  simbolo_auxiliar = linea_extraida_archivo;
  simbolo_arranque_ = simbolo_auxiliar;
  getline(archivo_entrada, linea_extraida_archivo);
  int cantidad_producciones = std::stoi(linea_extraida_archivo);
  Produccion produccion_auxiliar;
  std::string string_auxiliar;
  for (int iterador = 0; iterador < cantidad_producciones; ++iterador) {
    getline(archivo_entrada, linea_extraida_archivo);
    produccion_auxiliar.InsertaOrigen(linea_extraida_archivo[0]);
    int posicion_destino_produccion = linea_extraida_archivo.find_first_of('>') + 2;
    for (int iterador2 = posicion_destino_produccion; iterador2 < linea_extraida_archivo.size(); ++iterador2) {
      if (linea_extraida_archivo[iterador2] != ' ') {
        string_auxiliar.push_back(linea_extraida_archivo[iterador2]);    
      } else {
        produccion_auxiliar.InsertaDestinoProduccion(string_auxiliar);
        string_auxiliar.clear();
        iterador2 += 2; 
      }
    }
    produccion_auxiliar.InsertaDestinoProduccion(string_auxiliar);
    string_auxiliar.clear();
    producciones_.push_back(produccion_auxiliar);
    produccion_auxiliar.LimpiaDestinoProduccion();
  }
}

/// @brief Método que comprueba si hay producciones vacías o unitarias
/// @return true si hay producciones vacias o unitarias, false si no las hay
bool Gramatica::CompruebaSiHayProduccionUnitariaOVacia() const {
  std::string destino_produccion;
  Produccion produccion_auxiliar;
  for (int iterador = 0; iterador < producciones_.size(); ++iterador) {
    produccion_auxiliar = producciones_[iterador];
    for (int iterador2 = 0; iterador2 < produccion_auxiliar.TamanioDestinoProduccion(); ++iterador2) {
      destino_produccion = produccion_auxiliar[iterador2];
      if (produccion_auxiliar.TamanioDestinoProduccion() == 1 && destino_produccion.size() == 1) {
        if (isupper(destino_produccion[0])) {
          return true;
        }
        if (destino_produccion[0] == '&') {
          return true;
        }
      }
    }
  }
  return false;
}

/// @brief Método que convierte la gramática a forma normal de Chomsky
void Gramatica::ConvierteAFNC() {
  if (CompruebaSiHayProduccionUnitariaOVacia() == true) {
    std::cout << "Existen producciones vacias o unitarias, por lo que no puede aplicarse la conversión a FNC" << std::endl;
    exit(EXIT_SUCCESS);
  } 
  Produccion produccion_auxiliar;
  Produccion produccion_nueva;
  std::string destino_produccion;
  std::string string_auxiliar;
  std::vector<std::pair<Simbolo, char>> no_terminal_vinculado_terminal;
  Simbolo simbolo_auxiliar;
  for (int iterador = 0; iterador < producciones_.size(); ++iterador) {
    produccion_auxiliar = producciones_[iterador];
    for (int iterador2 = 0; iterador2 < produccion_auxiliar.TamanioDestinoProduccion(); ++iterador2) {
      destino_produccion = produccion_auxiliar[iterador2];
      int iterador_string_auxiliar{0};
      for (int iterador3 = 0; iterador3 < destino_produccion.size(); ++iterador3) {
        if (destino_produccion.size() == 1 && CompruebaSiEsUnSimboloTerminal(destino_produccion[0])) {
          string_auxiliar = destino_produccion[0];
          break;
        }
        string_auxiliar = string_auxiliar + destino_produccion[iterador3];
        iterador_string_auxiliar += 1;
        if (CompruebaSiEsUnSimboloTerminal(destino_produccion[iterador3])) {
          if (destino_produccion.size() > 1 ) {
            if (no_terminal_vinculado_terminal.size() == 0) {
              no_terminal_vinculado_terminal.push_back(std::make_pair(destino_produccion[iterador3], SeleccionaUnNoTerminalAleatorio()));
            }
            bool mismo_simbolo_encontrado{false};
            for (int iterador4 = 0; iterador4 < no_terminal_vinculado_terminal.size(); ++iterador4) {
              if (no_terminal_vinculado_terminal[iterador4].first == destino_produccion[iterador3]) {
                mismo_simbolo_encontrado = true;
              }
            }
            if (mismo_simbolo_encontrado == false) {
              no_terminal_vinculado_terminal.push_back(std::make_pair(destino_produccion[iterador3], SeleccionaUnNoTerminalAleatorio()));
            }
          }
          string_auxiliar.pop_back();
          iterador_string_auxiliar -= 1;
          for (int iterador4 = 0; iterador4 < no_terminal_vinculado_terminal.size(); ++iterador4) {
            if (destino_produccion[iterador3] == no_terminal_vinculado_terminal[iterador4].first) {
              if (iterador_string_auxiliar == 0) {
                string_auxiliar = no_terminal_vinculado_terminal[iterador4].second + string_auxiliar;
                iterador_string_auxiliar += 1;
              } else {
                string_auxiliar.insert(iterador_string_auxiliar, 1, no_terminal_vinculado_terminal[iterador4].second);
                iterador_string_auxiliar += 1;
              }
            }
          }
        }
      }
      produccion_nueva.InsertaDestinoProduccion(string_auxiliar);
      string_auxiliar.clear();
    }
    produccion_nueva.InsertaOrigen(produccion_auxiliar.get_simbolo_origen());
    producciones_[iterador] = produccion_nueva;
    produccion_nueva.LimpiaDestinoProduccion();
  }
  for (int iterador = 0; iterador < no_terminal_vinculado_terminal.size(); ++iterador) {
    produccion_nueva.InsertaOrigen(no_terminal_vinculado_terminal[iterador].second);
    string_auxiliar = no_terminal_vinculado_terminal[iterador].first.get_simbolo();
    produccion_nueva.InsertaDestinoProduccion(string_auxiliar);
    producciones_.push_back(produccion_nueva);
    produccion_nueva.LimpiaDestinoProduccion();
  }
  string_auxiliar.clear();
  std::vector<std::pair<std::string, char>> no_terminal_vinculado_no_terminales;
  for (int iterador = 0; iterador < producciones_.size(); ++iterador) {
    produccion_auxiliar = producciones_[iterador];
    for (int iterador2 = 0; iterador2 < produccion_auxiliar.TamanioDestinoProduccion(); ++iterador2) {
      destino_produccion = produccion_auxiliar[iterador2];
      string_auxiliar = destino_produccion;
      if (destino_produccion.size() > 2) {
        string_auxiliar.clear();
        for (int iterador3 = 0; iterador3 < destino_produccion.size(); ++iterador3) {
          string_auxiliar = string_auxiliar + destino_produccion[iterador3];
          if (string_auxiliar.size() == 3) {
            char terminal_aleatorio = SeleccionaUnNoTerminalAleatorio();
            bool no_terminales_iguales{false};
            int posicion_iguales{0};
            for (int iterador4 = 0; iterador4 < no_terminal_vinculado_no_terminales.size(); ++iterador4) {
              if (no_terminal_vinculado_no_terminales[iterador4].first == string_auxiliar.substr(1)) {
                no_terminales_iguales = true;
                posicion_iguales = iterador4;
              }
            }
            if (no_terminales_iguales == false) {
              no_terminal_vinculado_no_terminales.push_back(std::make_pair(string_auxiliar.substr(1), terminal_aleatorio));
              string_auxiliar.pop_back();
              string_auxiliar.pop_back();
              string_auxiliar = string_auxiliar + terminal_aleatorio;
            } else {
              string_auxiliar = no_terminal_vinculado_no_terminales[posicion_iguales].first;
            }

          }
        }
      }
      produccion_nueva.InsertaDestinoProduccion(string_auxiliar);
    }
    produccion_nueva.InsertaOrigen(produccion_auxiliar.get_simbolo_origen());
    producciones_[iterador] = produccion_nueva;
    produccion_nueva.LimpiaDestinoProduccion();
  }
  for (int iterador = 0; iterador < no_terminal_vinculado_no_terminales.size(); ++iterador) {
    produccion_nueva.InsertaOrigen(no_terminal_vinculado_no_terminales[iterador].second);
    string_auxiliar = no_terminal_vinculado_no_terminales[iterador].first;
    produccion_nueva.InsertaDestinoProduccion(string_auxiliar);
    producciones_.push_back(produccion_nueva);
    produccion_nueva.LimpiaDestinoProduccion();
  }
}

/// @brief Método que comprueba si un simbolo es terminal o no
/// @param simbolo 
/// @return true si es un simbolo terminal, false si no
bool Gramatica::CompruebaSiEsUnSimboloTerminal(const Simbolo& simbolo) const {
  bool es_terminal{false};
  for (int iterador = 0; iterador < terminales_.size(); ++iterador) {
    if (simbolo == terminales_[iterador]) {
      es_terminal = true;
    }
  }
  if (es_terminal == true) {
    return true;
  } else {
    return false;
  }
}

/// @brief Selecciona un no temrinal aleatorio que no está en el conjunto de no terminales y lo retorna
/// @return Retorna el no terminal seleccionado
char Gramatica::SeleccionaUnNoTerminalAleatorio() {
  std::string no_terminales = "ABCDEFGHIJKLMNOPQRTUVXYZ";
  for (int iterador = 0; iterador < no_terminales.size(); ++iterador) {
    bool es_no_terminal{false};
    for (int iterador2 = 0; iterador2 < no_terminales_.size(); ++iterador2) {
      if (no_terminales[iterador] == no_terminales_[iterador2]) {
        es_no_terminal = true;
      }
    }
    if (es_no_terminal == false) {
      no_terminales_.push_back(no_terminales[iterador]);
      return no_terminales[iterador];
    }
  }
  return no_terminales[0];
}

/// @brief Inserta los simbolos terminales en el vector de simbolos terminales
/// @param simbolo_terminal 
void Gramatica::InsertaLosTerminales(const Simbolo& simbolo_terminal) {
  terminales_.push_back(simbolo_terminal);
}

/// @brief Inserta los simbolos no terminales en el vector de simbolos no terminales
/// @param simbolo_no_terminal 
void Gramatica::InsertaLosNoTerminales(const Simbolo& simbolo_no_terminal) {
  no_terminales_.push_back(simbolo_no_terminal);
}

/// @brief Inserta el simbolo de arranque en el atributo simbolo_arranque_
/// @param simbolo_arranque 
void Gramatica::DefineSimboloArranque(const Simbolo& simbolo_arranque) {
  simbolo_arranque_ = simbolo_arranque;
}

/// @brief Inserta las producciones pertenecientes a la gramatica en el vector de producciones
/// @param produccion 
void Gramatica::InsertaProduccion(const Produccion& produccion) {
  producciones_.push_back(produccion);
}

/// @brief Devuelve el tamaño del vector de producciones
/// @return tamaño de el vector producciones_
int Gramatica::TamanioProducciones() const {
  return producciones_.size();
}

/// @brief Devuelve el tamaño del vector de simbolos no terminales
/// @return el tamaño del vector de simbolos no terminales
int Gramatica::TamanioSimbolosNoTerminales() const {
  return no_terminales_.size();
}

/// @brief Devuelve el tamaño del vector de simbolos terminales
/// @return el tamaño del vector terminales_
int Gramatica::TamanioSimbolosTerminales() const {
  return terminales_.size();
}

/// @brief Sobrecarga del operador de salida para imprimir en archivos
/// @param salida 
/// @param gramatica 
/// @return retorna el objeto ofstream salida
std::ofstream& operator<<(std::ofstream& salida, const Gramatica& gramatica) {  
  Produccion produccion_auxiliar;
  std::string destino_produccion;
  salida << gramatica.TamanioSimbolosTerminales() << std::endl;
  for (int iterador = 0; iterador < gramatica.TamanioSimbolosTerminales(); ++iterador) {
    salida << gramatica.terminales_.at(iterador).get_simbolo() << std::endl;
  }
  salida << gramatica.TamanioSimbolosNoTerminales() << std::endl;
  for (int iterador = 0; iterador < gramatica.no_terminales_.size(); ++iterador) {
    salida << gramatica.no_terminales_[iterador].get_simbolo() << std::endl;
  }
  salida << gramatica.TamanioProducciones() << std::endl;
  for (int iterador = 0; iterador < gramatica.producciones_.size(); ++iterador) {
    produccion_auxiliar = gramatica.producciones_[iterador];
    salida << produccion_auxiliar.get_simbolo_origen().get_simbolo() << " -> ";
    for (int iterador2 = 0; iterador2 < produccion_auxiliar.TamanioDestinoProduccion(); ++iterador2) {
      destino_produccion = produccion_auxiliar[iterador2];
      for (int iterador3 = 0; iterador3 < destino_produccion.size(); ++iterador3) {
        salida << destino_produccion[iterador3];
      }
      if (iterador2 != produccion_auxiliar.TamanioDestinoProduccion() - 1) {
        salida << " | ";
      }
    }
    salida << std::endl;
  }
  return salida;
}