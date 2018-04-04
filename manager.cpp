/*
 /  manager.cpp:
 	Clase principal donde realizaremos un control de errores y realizaremos la llamada a otra clase que
 	es la que realizará la busqueda de las ocurrencias.
/
/  Created by Benjamin Cadiz de Gracia on 8/3/18.
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "Search.cpp"
#include <thread>
#include <string>
#include <string.h>
#include <exception>
#include <stdlib.h>

int main(int argc, char **argv){
    std::string fichero, word,hil,prueba;
    int hilos,lines,linesXhilo;
    if(argc != 4){
        fprintf(stderr,"[ERROR] El número de argumentos no es válido.\nSintásis: ./SSOOIIGLE <ficheroDeTexto> <PalabraABuscar> <NºdeHilos> \n");
        exit(EXIT_FAILURE);
    }else if ( strcmp ("0", argv[3]) == 0){
        fprintf(stderr, "[ERROR] El número de hilos debe ser mayor que 0.\n");
        exit(EXIT_FAILURE);
    }
    try {
        fichero = argv[1];
        word = argv[2];
        hil =  argv[3];
        std::istringstream ( hil ) >> hilos;
        Search search;
        search.distribuir(hilos, fichero,word);
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    return 0;
    
}
