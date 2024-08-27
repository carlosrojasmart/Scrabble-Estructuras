#include "scrabble.h"
#include "heap.hxx"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <iterator>

std::vector<std::string> vector_diccionario;
Heap<string> heap_f;

std::string caracteres_aceptados = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ";

int InicializacionDiccionario::inicializar(const std::string& archivoDiccionario) {
    // Implementación para inicializar el diccionario desde el archivo
    std::ifstream archivo(archivoDiccionario);
    std::string linea;
    bool foundMatch = false;
    int i = 0;
    int palabras_cargadas = 0;
    BusquedaPalabras palabras;

    if (archivo.fail()) {
        std::cout << "archivo no existente o no se pudo leer" << std::endl;
        i = 1;

        return 1;
    }
    if (i != 1) {

        
        while (std::getline(archivo, linea)) {
            std::transform(linea.begin(), linea.end(), linea.begin(), [](unsigned char c) { return std::tolower(c); });

            foundMatch = palabras.esPalabraValida(linea);

            if (foundMatch == true) {
                vector_diccionario.push_back(linea);
                palabras_cargadas++;
            }
            
        }

        std::cout << "el diccionario se inicializo correctamente" << std::endl;
        std::cout << "se cargarón " << palabras_cargadas << " palabras" << std::endl;

        return 0;
    }

    archivo.close();
}

int InicializacionDiccionario::iniciarInverso(const std::string& archivoDiccionario) {
    // Implementación para inicializar el diccionario inverso desde el archivo
    
    std::ifstream archivo(archivoDiccionario);
    std::string linea;
    bool foundMatch = false;
    int i = 0;
    long double palabras_cargadas = 0;
    BusquedaPalabras palabras;

    if (archivo.fail()) {
        std::cout << "archivo no existente o no se pudo leer" << std::endl;
        i = 1;
    
        return 1;
    }
    
    if (i != 1) {
        while (std::getline(archivo, linea)) {
            std::transform(linea.begin(), linea.end(), linea.begin(), [](unsigned char c) { return std::tolower(c); });
            std::reverse(linea.begin(), linea.end());

            foundMatch = palabras.esPalabraValida(linea);
            
            if (foundMatch == true) {
                vector_diccionario.push_back(linea);
                palabras_cargadas++;
            }
        }

        std::sort(vector_diccionario.begin(), vector_diccionario.end());

        std::cout << "el diccionario se inicializo correctamente " << palabras_cargadas << std::endl;

        return 0;
    }
    archivo.close();
}

int InicializacionDiccionario::iniciarArbol(const std::string& archivoDiccionario) {
    // Implementación para inicializar el árbol de palabras desde el archivo
    Heap<std::string> heap;
    std::ifstream archivo(archivoDiccionario);
    std::string linea;
    bool foundMatch = false;
    int palabras_cargadas = 0;
    BusquedaPalabras palabras;

    if (archivo.fail()) {
        std::cout << "archivo no existente o no se pudo leer" << std::endl;
        return 1;
    }

    while (std::getline(archivo, linea)) {
        std::transform(linea.begin(), linea.end(), linea.begin(), [](unsigned char c) { return std::tolower(c); });
        foundMatch = palabras.esPalabraValida(linea);

        if (foundMatch == true) {
            heap.insert(linea);
            palabras_cargadas++;
        }
    }

    heap.sortHeap(heap_f);

    std::cout << "el diccionario se inicializo correctamente" << std::endl;
    std::cout << "se cargarón " << palabras_cargadas << " palabras" << std::endl;

    archivo.close();
    return 0;
}

int InicializacionDiccionario::iniciarArbolInverso(const std::string& archivoDiccionario) {
    // Implementación para inicializar el árbol de palabras desde el archivo
    Heap<std::string> heap;
    std::ifstream archivo(archivoDiccionario);
    std::string linea;
    bool foundMatch = false;
    int palabras_cargadas = 0;
    BusquedaPalabras palabras;

    if (archivo.fail()) {
        std::cout << "archivo no existente o no se pudo leer" << std::endl;
        return 1;
    }

    while (std::getline(archivo, linea)) {
        std::transform(linea.begin(), linea.end(), linea.begin(), [](unsigned char c) { return std::tolower(c); });
        std::reverse(linea.begin(), linea.end());
        foundMatch = palabras.esPalabraValida(linea);

        if (foundMatch == true) {
            heap.insert(linea);
            palabras_cargadas++;
        }
    }

    heap.sortHeap(heap_f);

    std::cout << "el diccionario se inicializo correctamente" << std::endl;
    std::cout << "se cargarón " << palabras_cargadas << " palabras" << std::endl;

    archivo.close();
    return 0;
}

int BusquedaPalabras::BusquedaPalabra(const std::string& archivoDiccionario) {
    int izquierda = 0;
    int derecha = vector_diccionario.size() - 1;
    int result = -1;

    while (izquierda <= derecha) {
        int centro = (izquierda + derecha) / 2;

        int comparacion = strcmp(vector_diccionario[centro].c_str(), archivoDiccionario.c_str());

        if (comparacion == 0) {
            return centro; // Encontramos la palabra
        } else if (comparacion < 0) {
            izquierda = centro + 1;
        } else {
            derecha = centro - 1;
            if (vector_diccionario[centro].size() > archivoDiccionario.size() &&
                strncmp(vector_diccionario[centro].c_str(), archivoDiccionario.c_str(), vector_diccionario.size()) == 0) {
                return -1; // Definitivamente no está en la lista
            }
        }
    }

    // No se encontró la palabra y no hay prefijos coincidentes, 
    // definitivamente no está en la lista
    return result;
}

int BusquedaPalabras::puntajePalabra(const std::string& palabra) {

                    int j = 0;
                    int azul = 0; 
                    int cian = 0; 
                    int total = 0; 
                    int contador_azul = 0; 
                    int contador_cian = 0;
                    
                    int suma_elemento = 0;

                    std::vector<std::string> color_casillas;
                    std::string aux_color_casillas;
                    int aux_indice_cian = 16;
                    std::vector<int> indice_cian;
                    int aux_indice_azul = 16;
                    std::vector<int> indice_azul;

                    std::cout << "la palabra se encuentra sobre alguna casilla de color rojo, violeta, azul o cian" << std::endl; 
                    std::cout << "escribe solamente un elemento por iteracion" << std::endl;
                    std::cout << "escribe 'salir' para terminar" << std::endl;
                    while (true) {
                        std::cin >> aux_color_casillas;
                        if (aux_color_casillas == "cian"){
                            std::cout<<"ingrese el numero de indice de la letra que corresponde a la casilla cian"<<std::endl;
                            std::cin>>aux_indice_cian;
                            aux_indice_cian -= 1;
                            indice_cian.push_back(aux_indice_cian);
                        }
                        if (aux_color_casillas == "azul"){
                            std::cout<<"ingrese el numero de indice de la letra que corresponde a la casilla azul"<<std::endl;
                            std::cin>>aux_indice_azul;
                            aux_indice_azul -= 1;
                            indice_azul.push_back(aux_indice_azul);
                        }
                        if (aux_color_casillas == "salir") {
                            break;
                        }
                        color_casillas.push_back(aux_color_casillas);
                    }
                    total = 0;
                    suma_elemento = 0;
                    std::cout<<" prueba aux azul"<<aux_indice_azul<<std::endl; 
                    std::vector<char> letrasSeparadas;
                            for (char caracter : palabra) {
                                if (isalpha(caracter)) {
                                letrasSeparadas.push_back(caracter);
                                }
                                if (aux_indice_azul != 16 && j == indice_azul[contador_azul]){
                                    azul = 1;
                                    contador_azul++;
                                }
                                if (aux_indice_cian != 16 && j == indice_cian[contador_cian]){
                                    cian = 1;
                                    contador_cian++;
                                }
                                if (caracter == 'e' || caracter == 'a' || caracter == 'i' || caracter == 'o' || caracter == 'n' || caracter == 'r' || caracter == 't' || caracter == 'l' || caracter == 's' || caracter == 'u') {
                                suma_elemento = 1;}
                                if (caracter == 'd' || caracter == 'g' ) {
                                suma_elemento = 2;}
                                if (caracter == 'b' || caracter == 'c' || caracter == 'm' || caracter == 'p') {
                                suma_elemento = 3;}
                                if (caracter == 'f' || caracter == 'h' || caracter == 'v' || caracter == 'w' || caracter == 'y') {
                                suma_elemento = 4;}
                                if (caracter == 'k') {
                                suma_elemento = 5;}
                                if (caracter == 'j' || caracter == 'x') {
                                suma_elemento = 8;}
                                if (caracter == 'q' || caracter == 'z') {
                                suma_elemento = 10;}
                                if (azul == 1){
                                    total += suma_elemento + suma_elemento + suma_elemento;
                                }else if (cian == 1){
                                    total += suma_elemento + suma_elemento;
                                }else if (azul == 0 && cian == 0){
                                    total += suma_elemento;
                                }
                                cian = 0;
                                suma_elemento = 0;
                                azul = 0;
                                j++;
                                std::cout << "prueba contenido  " << total << std::endl << "indice azul" << caracter << std::endl;
                            }
                    for(std::vector<std::string>::iterator it = color_casillas.begin(); it != color_casillas.end(); it++){
                        std::cout << "prueba contenido  " << *it << std::endl;
                        if (*it == "rojo") {
                            total = total * 3;
                        }
                        if (*it == "violeta") {
                            total = total * 2;
                        }
                    }
                    return total;
}

bool BusquedaPalabras::esPalabraValida(const std::string& palabra) {
    // Implementación para verificar si la palabra es válida
    bool foundMatch = false;
                for (int cont = 0; palabra[cont] != '\0'; cont++) {
                foundMatch = false;
                for (int i = 0; i < caracteres_aceptados.size() - 1; i++) {
                    if (palabra[cont] == caracteres_aceptados[i]) {
                        foundMatch = true;
                        break;
                    }
                }

                if (foundMatch != true) {
                    break;
                }
            }
            if (foundMatch == true) {
                return true;
            } else {
                return false;
            }
}

void ConsolaInteractiva::ejecutar() {
    std::string comando;
    std::string nombre_archivo;
    std::string palabra;
    InicializacionDiccionario inicializar;
    BusquedaPalabras palabras;
    std::vector<std::string> arch_inicializados, arch_inv_inicializados;
    bool foundMatch = false;
    int indice_palabra = 0;
    int cont = 0;
    int ini_dic = 0;
    int error_ini = 0;
    while (true) {

    std::cout << "$ ";
    std::string comando;
    std::getline(std::cin, comando);

    std::vector<std::string> comandos;

    std::string palabra;
    for (char c : comando) {
        // Si el carácter actual no es un espacio en blanco, añádelo a la palabra
        if (c != ' ') {
            palabra += c;
        } else { // Si es un espacio en blanco, añade la palabra al vector y reinicia la palabra
            if (!palabra.empty()) { // Asegúrate de que la palabra no esté vacía
                comandos.push_back(palabra);
                palabra.clear(); 
            }
        }
    }

    if (!palabra.empty()) {
        comandos.push_back(palabra);
    }

        if (!comandos.empty() && comandos.size() <= 2 && comandos[0] == "inicializar" && comandos[1] != "inverso") {
            // Lógica para manejar el comando "inicializar"
            ini_dic = 0;
            for (std::vector<std::string>::iterator it = arch_inicializados.begin(); it != arch_inicializados.end(); it++) {
                if (*it == comandos[1]) {
                    ini_dic = 1;
                    break;
                }
            }
            if (ini_dic != 1) {
                error_ini = inicializar.inicializar(comandos[1]);
                if (error_ini == 0) {
                    arch_inicializados.push_back(comandos[1]);
                }
            } else {
                std::cout << "el diccionario ya ha sido inicializado" << std::endl;
            }
        } else if (!comandos.empty() && comandos.size() <= 3 && comandos[0] == "inicializar" && comandos[1] == "inverso") {
            // Lógica para manejar el comando "iniciar_inverso"
            ini_dic = 0;
            for (std::vector<std::string>::iterator it = arch_inv_inicializados.begin(); it != arch_inv_inicializados.end(); it++) {
                if (*it == comandos[2]) {
                    ini_dic = 1;
                    break;
                }
            }
            if (ini_dic != 1) {
                inicializar.iniciarInverso(comandos[2]);
                if (error_ini == 0) {
                    arch_inv_inicializados.push_back(comandos[2]);
                }
            } else {
                std::cout << "el diccionario ya ha sido inicializado" << std::endl;
            }
        } else if (!comandos.empty() && comandos.size() <= 3 && comandos[0] == "puntaje" && comandos[1] == "palabra") {
            // Lógica para manejar el comando "puntaje"
            palabra = comandos[2];
            foundMatch = palabras.esPalabraValida(palabra);
            if (foundMatch == true) {
                std::transform(palabra.begin(), palabra.end(), palabra.begin(), [](unsigned char c) { return std::tolower(c); });
                int indice_palabra = palabras.BusquedaPalabra(palabra);
                if (indice_palabra == -1) {
                    std::cout << "palabra no encontrada" << std::endl;
                } else {
                    int puntaje;
                    // 1 puntos: E, A, I, O, N, R, T, L, S, U.
                    // 2 puntos: D, G.
                    // 3 puntos: B, C, M, P.
                    // 4 puntos: F, H, V, W, Y.
                    // 5 puntos: K.
                    // 8 puntos: J, X.
                    // 10 puntos: Q, Z
                    // Rojo * 3
                    // Violeta * 2
                    // Azul + 3 (letra)
                    // Cian + 2 (letra) 
                    puntaje = palabras.puntajePalabra(palabra);
                    std::cout << "la palabra tiene un puntaje de " << puntaje << std::endl;
                }
                
            } else {
                std::cout << "la palabra contiene simbolos inaceptados" << std::endl;
            }

        } else if (!comandos.empty() && comandos.size() == 3 && comandos[0] == "iniciar" && comandos[1] == "arbol") {
            // Lógica para manejar el comando "iniciar_arbol"
        if (inicializar.iniciarArbol(comandos[2]) == 0) {
            heap_f.imprimir(heap_f);
        } else {
            cout << "Error al inicializar el diccionario." << endl;
        }
        } else if (!comandos.empty() && comandos.size() == 4 && comandos[0] == "iniciar" && comandos[1] == "arbol" && comandos[2] == "inverso") {
            // Lógica para manejar el comando "iniciar_arbol_inverso"
        if (inicializar.iniciarArbolInverso(comandos[3]) == 0) {
            heap_f.imprimir(heap_f);
        } else {
            cout << "Error al inicializar el diccionario." << endl;
        }

        } else if (!comandos.empty() && comandos.size() <= 4 && comandos[0] == "palabras" && comandos[1] == "por" && comandos[2] == "prefijo") {
            // Lógica para manejar el comando "palabras_por_prefijo"

            heap_f.prefijo(comandos[3]);

        } else if (!comandos.empty() && comandos.size() <= 4 && comandos[0] == "palabras" && comandos[1] == "por" && comandos[2] == "sufijo") {
            // Lógica para manejar el comando "palabras_por_sufijo"

            heap_f.subfijo(comandos[3]);

        } else if (!comandos.empty() && comandos.size() <= 3 && comandos[0] == "grafo" && comandos[1] == "de" && comandos[2] == "palabras") {
            std::cout << "no se pudo construir el grafo de palabras" << std::endl;

        } else if (!comandos.empty() && comandos.size() <= 1 && comandos[0] == "ayuda") {

            std::cout << "Comando" << " || " << "Uso del comando" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "inicializar nombre del diccionario.txt" << " || " << "permite inicializar el diccionario" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "inicializar inverso nombre del diccionario.txt" << " || " << "permite inicializar el diccionario de manera inversa" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "puntaje palabras" << " || " << "permite verificar el puntaje obtenido al seleccionar una palabra" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "iniciar arbol" << " || " << "permite inicializar el arbol del diccionario" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "iniciar arbol inverso" << " || " << "permite inicializar el arbol del diccionario inverso" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "palabras por prefijo" << " || " << "permite ubicar todas las palabras que inicien con un prefijo en particular" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "palabras por sufijo" << " || " << "permite ubicar todas las palabras que inicien con un sufijo en particular" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "salir" << " || " << "permite finalizar el programa" << std::endl;
            std::cout << "--------------------------------------------------------------------------------" << std::endl;

        } else if (!comandos.empty() && comandos.size() <= 1 && comandos[0] == "salir") {
            break;
        }
        comandos.clear();
    }
}

