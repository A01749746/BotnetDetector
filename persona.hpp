//
//  persona.hpp
//  tarea3
//
//  Created by Aldo Escandon on 18/09/23.
//

#ifndef persona_hpp
#define persona_hpp

#include <iostream>
#include <string>
using std::string;

class Persona {
private:
    string fecha;
    string hora;
    string ip_origen;
    string puerto_origen;
    string nombre_origen;
    string ip_destino;
    int puerto_destino;
    string nombre_destino;
    
public:
    Persona();
    ~Persona();
    Persona(string f, string h, string ip_O, string pu_Or, string nom_Ori, string ip_dest, int pu_dest, string nom_dest);
    string get_fecha();
    string get_nom();
    string get_ip();
    string get_email();
    string get_correo();
    string get_cor();
    int get_pDest();
    string getIpOrigenCompleto();
    string getIpDestinoCompleto();
    string getHora();
    string getUrl();
    string obtenerMailSinNombre();


    
};
#endif /* Persona_hpp */
