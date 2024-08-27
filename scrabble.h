#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class InicializacionDiccionario {
public:
    int inicializar(const std::string& archivoDiccionario);
    int iniciarInverso(const std::string& archivoDiccionario);
    int iniciarArbol(const std::string& archivoDiccionario);
    int iniciarArbolInverso(const std::string& archivoDiccionario);
};

class BusquedaPalabras {
public:
   int BusquedaPalabra(const std::string& archivoDiccionario);
   int puntajePalabra(const std::string& palabra);
   bool esPalabraValida(const std::string& palabra);
};

class GeneracionCombinaciones {
public:
    void construirGrafoDePalabras();
};

class ConsolaInteractiva {
public:
    void ejecutar();
};

#endif // SCRABBLE_H
