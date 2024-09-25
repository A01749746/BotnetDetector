//
//  archivo.cpp
//  tarea3
//
//  Created by Aldo Escandon on 18/09/23.
//

#include "archivo.hpp"
#include "persona.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using namespace std;
using std::cout;
using std::endl;
using std::cin;
#include <stdexcept>

Archivo::Archivo(){
    
}

void Archivo::leer_archivo() {
    
    // Función para procesar un archivo CSV
    ifstream catalogo;
    catalogo.open("/Users/betolimon/Downloads/equipo10.csv");
    //("/Users/betolimon/Downloads/equipo10.csv")
    //("/Users/aldoescandon/Downloads/equipo10.csv")
    
    if (!catalogo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    
    string line;
    while (getline(catalogo, line)) {
        stringstream token(line);
        string fecha;
        string hora;
        string ip_origen;
        string puerto_origen;
        string nombre_origen;
        string ip_destino;
        string puerto_destino;
        string nombre_destino;
        
        getline(token, fecha, ',');
        getline(token, hora, ',');
        getline(token, ip_origen, ',');
        getline(token, puerto_origen, ',');
        getline(token, nombre_origen, ',');
        getline(token, ip_destino, ',');
        getline(token, puerto_destino, ',');
        getline(token, nombre_destino, ',');
        
        
        try {
            //existen datos de puerto de origen con "-" por ello hacemos el codigo a prueba de esos erroress
            if(puerto_destino == "-"){
                Persona *p = new Persona(fecha, hora, ip_origen, puerto_origen, nombre_origen, ip_destino, 0, nombre_destino);
            }else{
                Persona *p = new Persona(fecha, hora, ip_origen, puerto_origen, nombre_origen, ip_destino, stoi(puerto_destino), nombre_destino);
                registro.push_back(p);
            }
            
        } catch (...) {
            cout << "Error atrapado  " << endl;
        }
    }
}

int Archivo::get_num(){
    
    return registro.size();
    
}

int Archivo::get_fecha(string fecha){
    
    int count = 0;
    
    for(int i = 0; i < registro.size(); i++){
        
        if(registro[i]->get_fecha() == fecha){
            count = count +1;
        }
        
    }
    
    return count;
    
}

std::vector<Persona*> Archivo::get_registro() {
    
    return registro;
}


string Archivo::get_ip(){
    
    return registro[1]->get_ip();
    
}

vector<string> Archivo::get_emails() {
    vector<string> correos;

    for (int i = 0; i < registro.size(); i++) {
        bool found = false; // Flag to check if the email already exists in correos

        for (int j = 0; j < correos.size(); j++) {
            if (correos[j] == registro[i]->get_correo()) {
                found = true;
                break; // Exit the inner loop if the email already exists
            }
        }

        if (!found) {
            correos.push_back(registro[i]->get_correo());
        }
    }

    return correos;
}

string Archivo::get_cor(){
    
    return registro[1]->get_cor();
    
}

std::vector<string>Archivo::getIpOrigen(){
    
    vector<string> ips;
    string var;
    
    for (int i=0; i<registro.size(); i++){
        var = registro[i]->getIpOrigenCompleto();
        ips.push_back(var);
    }
    return ips;
}

std::vector<string>Archivo::getIpDestino(){
    
    vector<string> ips;
    string var;
    
    for (int i=0; i<registro.size(); i++){
        var = registro[i]->getIpDestinoCompleto();
        ips.push_back(var);
    }
    return ips;
}

std::vector<string> Archivo::sitiosWeb() {
    
    std::set<string> sitiosUnicos;
    std::vector<string> sitios;
    
    for(int i = 0; i < registro.size(); i++) {
        string sitio = registro[i]->getUrl();
        sitiosUnicos.insert(sitio);
    }

    // Convertir el conjunto a un vector
    sitios.assign(sitiosUnicos.begin(), sitiosUnicos.end());
    
    return sitios;
}

std::vector<std::pair<string, string>> Archivo::conexionesOrigenDest(string fecha){
    
    std::vector<std::pair<string, string>> vector;
    
    string redInterna = this->get_ip();
    
    string origen;
    string destino;

        
    for (int i=0; i<registro.size(); i++){
        
        size_t ultimoPunto = registro[i]->getIpOrigenCompleto().rfind('.');
        
        if (ultimoPunto != std::string::npos) {
            std::string prefijo = registro[i]->getIpOrigenCompleto().substr(0, ultimoPunto);
            std::string prefijo2 = registro[i]->getIpDestinoCompleto().substr(0, ultimoPunto);

            if (prefijo == redInterna && prefijo2 == redInterna){
                origen = registro[i]->getIpOrigenCompleto();
                destino = registro[i]->getIpDestinoCompleto();
                
                if(registro[i]->get_fecha() == fecha){
                    vector.push_back(std::make_pair(origen,destino));
                }
            }
            
        }
        
    }
    
    return vector;

}

std::vector<std::pair<string, string>> Archivo::conexionesOrigenSitio(string fecha){
    
    std::vector<std::pair<string, string>> vector;
    
    string redInterna = this->get_ip();
    
    string origen;
    string sitio;
    
    int puerto1 = 80;
    int puerto2 = 443;


    for (int i=0; i<registro.size(); i++){
        
        size_t ultimoPunto = registro[i]->getIpOrigenCompleto().rfind('.');
        
        if (ultimoPunto != std::string::npos) {
            std::string prefijo = registro[i]->getIpOrigenCompleto().substr(0, ultimoPunto);

            if (prefijo == redInterna && (registro[i]->get_pDest() == puerto1 || registro[i]->get_pDest() == puerto2)){
                
                origen = registro[i]->getIpOrigenCompleto();
                sitio = registro[i]->getUrl();
                
                if(registro[i]->get_fecha() == fecha){
                    vector.push_back(std::make_pair(origen,sitio));
                }
            }
            
        }
        
    }
    
    return vector;

}

std::vector<string> Archivo::dominiosSinReto(){
    
    std::vector<string> dominios;
    
    for (int i=0; i<registro.size();i++){
        
        string dominio = registro[i]->getUrl();
        
        if (dominio != "reto.com"){
            dominios.push_back(dominio);
        }
        
    }
    
    return dominios;
        
}

std::vector<string> Archivo::dominiosConReto(){
    
    std::vector<string> dominios;
    
    for (int i=0; i<registro.size();i++){
        
        string dominio = registro[i]->getUrl();
        
        if (dominio == "reto.com"){
            dominios.push_back(dominio);
        }
        
    }
    
    return dominios;
        
}


std::vector<string> Archivo::getIpOrigenSinRepeticiones(){
    
            std::set<string> ipSet;
            std::vector<string> ipsUnicas;

            for (int i = 0; i < registro.size(); i++) {
                string ip = registro[i]->getIpOrigenCompleto();
                if (ip != "-") {
                    ipSet.insert(ip);
                }
            }

            for (const auto& ip : ipSet) {
                ipsUnicas.push_back(ip);
            }

            return ipsUnicas;
        }



