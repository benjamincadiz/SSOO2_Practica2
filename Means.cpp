/*
/  Means.cpp:
 Clase Orientada a los recursos necesarios que puede necesitar el programa como puede ser
 - Contar el numero de lineas que tiene el fichero para así dividirlo en hilos.
 - Imprimir por pantalla el resultado almacenado en un diccionario compuesto por el Nº de hilo y una cola con cada ocurrencia.
/
/  Created by Benjamin Cadiz de Gracia on 3/4/18.
*/

#
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <map>

class Means{
public:
    Means(){
        
    }
    void printear(std::map<int,std::queue<Palabra>> vResultado)
    {
       	for(auto it = vResultado.begin();it != vResultado.end();it++)
        {
            std::queue<Palabra> my_queue =  it->second;
            while(!my_queue.empty())
            {
                Palabra p =  my_queue.front();
            	std::cout << p.toString() << std::endl;
                my_queue.pop();
            }
        }
    }
    int num_lineas(std::string fichero){
        int lineas=0;
        std::string line;
        std::ifstream myfile(fichero);
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                lineas++;
            }
        }
        return lineas;
    }
    

};
