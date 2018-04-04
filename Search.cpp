/*
 /Search.cpp:
 Clase que realiza la búsqueda principal. Contamos con dos Métodos:
 - Distribuir: Su función principal sera distribuir tantos hilos como sean pasados por parámetros y despues
 	imprimir la solución generada.
 - Search: Realiza la funcion de encontrar la palabra buscada, asi como el tratamiento de la línea para
 	poder mostrarlo de la forma deseada. Una vez realizado el tratamiento de la linea por parte de cada
 	se introduce en una cola, donde una vez terminados todos los hilos, se introducirán en un diccionario
 	que sera asociado a su numero de hilo.
/
/
/  Created by Benjamin Cadiz de Gracia on 3/4/18.
*/

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <fstream>
#include "ObjectSSOOIIGLE.cpp"
#include "Means.cpp"
#include <thread>
#include <string>
#include <stdlib.h>
#include <map>

std::mutex cerrojo;
std::map<int,std::queue<Palabra>> vResultado;

class Search{
public:
    Search(){
         vResultado.clear();
    }

    static void findWord(std::string fichero, std::string palabra, int numhilo, int linesXhilo, int inicio, int fin)
    {
        int linea=0;
        int pos;
        std::string line, result, palabrapunto,palabracoma;
        palabracoma = palabra+',';
        palabrapunto = palabra+'.';
        std::ifstream myfile (fichero);
        std::string tempStr;
        std::vector<std::string> resultado;
        std::queue<Palabra> my_queue;
        
        if (myfile.is_open())
        {
            while ( getline (myfile,line))
            {
                linea++;
                if(line.find(palabra) != std::string::npos  && inicio<=linea && linea<=fin)
                {
                    resultado.clear();
                    std::istringstream isstream(line);
                    while(isstream >> tempStr)
                    {
                        resultado.push_back(tempStr);
                        if (tempStr.compare(palabra) == 0 || tempStr.compare(palabrapunto) == 0 || tempStr.compare(palabracoma) == 0){
                            pos = resultado.size()-1;
                        }
                    }
                    for (unsigned i=0; i<resultado.size(); i++)
                    {
                        if(pos==i)
                        {
                            std::unique_lock<std::mutex> lk(cerrojo);
                            if(pos == 0)
                            {
                                result = resultado[i]+' '+resultado[i+1];
                                Palabra object(numhilo,linea,linesXhilo,result);
                                my_queue.push(object);
                            }else {
                                result = resultado[i-1]+' '+resultado[i]+' '+resultado[i+1];
                                Palabra object(numhilo,linea,linesXhilo,result);
                                my_queue.push(object);
                            }
                            lk.unlock();
                        }
                    }
                }
            }
            myfile.close();
            vResultado.insert(std::pair<int,std::queue<Palabra>>(numhilo,my_queue));
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
        
        for(unsigned i = 0;i<hilos;i++)
        {
            inicio = i*linesXhilo+1;
            fin = inicio+linesXhilo;
            vhilos.push_back(std::thread(findWord,fichero,palabra,i,linesXhilo,inicio, fin));
        }
        std::for_each(vhilos.begin(),vhilos.end(),std::mem_fn(&std::thread::join));
        means.printear(vResultado);
    }
};
