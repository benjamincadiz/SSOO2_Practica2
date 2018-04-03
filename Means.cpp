//
//  Means.cpp
//  
//
//  Created by Benjamin Cadiz de Gracia on 3/4/18.
//

#
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

class Means{
public:
    Means(){
        
    }
    void printear(std::vector<Palabra> vResultado){
        for(auto it = vResultado.cbegin();it != vResultado.cend();it++){
            Palabra p =  *it;
            std::cout << p.toString() << std::endl;
        }
        std::cout << "Numero de ocurrencias : " << vResultado.size() << std::endl;
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
