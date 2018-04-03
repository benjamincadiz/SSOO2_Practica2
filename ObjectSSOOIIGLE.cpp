//
//  ObjectSSOOIIGLE.cpp
//  
//
//  Created by Benjamin Cadiz de Gracia on 8/3/18.
//

#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>

class Palabra{
private:
    int linesXhilo;
    int hilo;
    int line;
    std::string word;
public:
    Palabra (int hil, int linea,int linesxhilo, std::string pal){
            hilo = hil;
            line = linea;
        	linesXhilo = linesxhilo;
            word = pal;
        }
  
	int getLine(){
    return line;
	}
	int getHilo(){
	return hilo;
	}
	std::string getWord(){
	return word;
	}
    int getInicio(){
        return getHilo()*linesXhilo+1;
    }
    int getFinal(){
        return getInicio()+linesXhilo;
    }
    std::string toString(){
        return  "[Hilo "+std::to_string(getHilo())+" inicio:"+std::to_string(getInicio())+" - final: "+std::to_string(getFinal())+"] :: línea "+std::to_string(getLine())+" :: ... "+getWord()+" ... ";
    }
};

