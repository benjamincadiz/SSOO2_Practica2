//
//  manager.cpp
//  
//
//  Created by Benjamin Cadiz de Gracia on 8/3/18.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "ObjectSSOOIIGLE.cpp"
#include <thread>
#include <string>
#include <string.h>
#include <exception>
#include <stdlib.h>

std::mutex cerrojo;
std::vector<Palabra> vResultado;

void printear(){
    for(auto it = vResultado.cbegin();it != vResultado.cend();it++){
        Palabra p =  *it;
        std::cout << p.toString() << std::endl;
    }
}
void openFile(std::string fichero, std::string palabra, int numhilo, int linesXhilo, int inicio, int fin){
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

void distribuir(int hilos, std::string fichero,std::string palabra){
    int linesXhilo, inicio, fin;
    inicio = fin = 0;
    std::string nombre;
    linesXhilo = num_lineas(fichero) / hilos;
    std::vector<std::thread> vhilos;
   
    for(unsigned i = 0;i<hilos;i++){
        inicio = i*linesXhilo+1;
        fin = inicio+linesXhilo;
        vhilos.push_back(std::thread(openFile,fichero,palabra,i,linesXhilo,inicio, fin));
    }
    std::for_each(vhilos.begin(),vhilos.end(),std::mem_fn(&std::thread::join));
    printear();
}

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
        //std::cout << "El numero de lineas son: " <<num_lineas(fichero) << std::endl;
        vResultado.clear();
        distribuir(hilos, fichero,word);
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    return 0;
    
}
