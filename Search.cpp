//
//Search.cpp
//  
//
//  Created by Benjamin Cadiz de Gracia on 3/4/18.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "ObjectSSOOIIGLE.cpp"
#include "Means.cpp"
#include <thread>
#include <string>
#include <stdlib.h>

std::mutex cerrojo;
std::vector<Palabra> vResultado;

class Search{
public:
    Search(){
         vResultado.clear();
    }

    static void openFile(std::string fichero, std::string palabra, int numhilo, int linesXhilo, int inicio, int fin){
        int linea=0;
        int pos;
        std::string line, result, palabrapunto,palabracoma;
        palabracoma = palabra+',';
        palabrapunto = palabra+'.';
        std::ifstream myfile (fichero);
        std::string tempStr;
        std::vector<std::string> resultado;
        
        if (myfile.is_open())
        {
            while ( getline (myfile,line))
            {
                linea++;
                if(line.find(palabra) != std::string::npos  && inicio<=linea && linea<=fin){
                    resultado.clear();
                    std::istringstream isstream(line);
                    while(isstream >> tempStr) {
                        /*115 SEAMOS... influencia */
                        //std::cout << "[ANTES ] " << tempStr;
                        std::transform(tempStr.begin(),tempStr.end(),tempStr.begin(),::tolower);
                        //std::cout << " [DESPUES] " <<tempStr << std::endl;
                        resultado.push_back(tempStr);
                        if (tempStr.compare(palabra) == 0 || tempStr.compare(palabrapunto) == 0 || tempStr.compare(palabracoma) == 0){
                            pos = resultado.size()-1;
                        }
                    }
                    for (unsigned i=0; i<resultado.size(); i++){
                        if(pos==i){
                            cerrojo.lock();
                            if(pos == 0){
                                result = resultado[i]+' '+resultado[i+1];
                                Palabra object(numhilo,linea,linesXhilo,result);
                                vResultado.push_back(object);
                            }else {
                                result = resultado[i-1]+' '+resultado[i]+' '+resultado[i+1];
                                Palabra object(numhilo,linea,linesXhilo,result);
                                vResultado.push_back(object);
                            }
                            cerrojo.unlock();
                            //std::cout <<"ATENCION: [Hilo "<<numhilo<<" inicio:"<<inicio<<" - final: "<<fin<<"] :: línea "<<linea<<" :: ... "<<result<<" ... "<< std::endl;
                        }
                    }
                }
            }
            myfile.close();
        }else{
            fprintf(stderr, "[ERROR] No se ha podido encontrar el fichero de texto, introduzca una ruta váldia\n");
            exit(EXIT_FAILURE);
        }
    }
    
    void distribuir(int hilos, std::string fichero,std::string palabra){
        int linesXhilo, inicio, fin;
        inicio = fin = 0;
        std::string nombre;
        std::vector<std::thread> vhilos;
        Means means;
        linesXhilo = means.num_lineas(fichero) / hilos;
        
        for(unsigned i = 0;i<hilos;i++){
            inicio = i*linesXhilo+1;
            fin = inicio+linesXhilo;
            vhilos.push_back(std::thread(openFile,fichero,palabra,i,linesXhilo,inicio, fin));
        }
        std::for_each(vhilos.begin(),vhilos.end(),std::mem_fn(&std::thread::join));
        means.printear(vResultado);
    }
};
