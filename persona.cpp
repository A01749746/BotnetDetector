//
//  persona.cpp
//  tarea3
//
//  Created by Aldo Escandon on 18/09/23.
//

#include "persona.hpp"

Persona::Persona(){
    
}

Persona::~Persona(){
    
}


Persona::Persona(string f, string h, string ip_O, string pu_Or, string nom_Ori, string ip_dest, int pu_dest, string nom_dest){
    
    fecha = f;
    hora = h;
    ip_origen = ip_O;
    puerto_origen = pu_Or;
    nombre_origen = nom_Ori;
    ip_destino = ip_dest;
    puerto_destino = pu_dest;
    nombre_destino = nom_dest;
}

string Persona::get_fecha(){
    
    return fecha;
    
}

string Persona::get_nom(){
    
    size_t puntoPos = nombre_origen.find('.');
    if (puntoPos != string::npos){
        return nombre_origen.substr(0,puntoPos);
    }else{
        return "";
    }
    
}

string Persona::get_ip(){
    size_t ultimoPunto = ip_origen.rfind('.');
    
    if (ultimoPunto != std::string::npos) {
        std::string prefijo = ip_origen.substr(0, ultimoPunto);
        return prefijo;
    } else {
        return ip_origen;
    }

}

string Persona::get_email(){
    
    return nombre_origen;
    
}

string Persona::get_correo(){
    
    return nombre_destino;
    
}

std::string Persona::get_cor(){
    int longitud = nombre_origen.length();

    std::string dominio = nombre_origen.substr(longitud - 8);
        
    return dominio;
}

int Persona::get_pDest(){
    return puerto_destino;
}


string Persona::getIpOrigenCompleto(){
    return ip_origen;
}

string Persona::getIpDestinoCompleto(){
    return ip_destino;
}

string Persona::getHora(){
    
    return hora;
}

string Persona::getUrl(){
    return nombre_destino;
}


string Persona::obtenerMailSinNombre(){
    
    size_t atPos = nombre_origen.find('.');
        if (atPos != std::string::npos) {
            return nombre_origen.substr(atPos + 1);
        } else {
            return "";
        }
}

