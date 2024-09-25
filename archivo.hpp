//
//  archivo.hpp
//  tarea3
//
//  Created by Aldo Escandon on 18/09/23.
//

#ifndef archivo_hpp
#define archivo_hpp
#include "persona.hpp"
#include <vector>
#include <string>
#include <set>


using std::string;


#include <stdio.h>

class Archivo
{
    private:

        std::vector<Persona*> registro;


    public:

        Archivo();
        std::vector<Persona*> get_registro();
        void leer_archivo();
        int get_num();
        int get_fecha(string fecha);
        string get_ip();
        std::vector <string> get_emails();
        string get_cor();
        std::vector<string> getIpOrigen();
        std::vector<string> getIpDestino();
        std::vector<string> sitiosWeb();
        std::vector<std::pair<string, string>> conexionesOrigenDest(string fecha);
        std::vector<std::pair<string, string>> conexionesOrigenSitio(string fecha);
        std::vector<string> dominiosSinReto();
        std::vector<string> getIpOrigenSinRepeticiones();
        std::vector<string> dominiosConReto();








};

#endif /* archivo_hpp */
