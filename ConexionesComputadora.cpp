//
//  ConexionesComputadora.cpp
//  act2.2
//
//  Created by Alberto Limón on 02/10/23.
//

#include "ConexionesComputadora.hpp"

ConexionesComputadoras::ConexionesComputadoras(string ip, Archivo arch){
    
    IP = ip;
    archivo = arch;
}

ConexionesComputadoras::~ConexionesComputadoras() {

}

void ConexionesComputadoras::llenarSalientes(){
    
    std::vector <string> origenIp = archivo.getIpOrigen();
    
    for (int i=0; i<origenIp.size();i++){
        if (IP == origenIp[i]){
            salientes->enqueue(origenIp[i]);
        }
    }
    
}

void ConexionesComputadoras::llenarEntrantes(){
    
    std::vector <string> origenDest = archivo.getIpDestino();
    
    for (int i=0; i<origenDest.size();i++){
        if (IP == origenDest[i]){
            entrantes->push(origenDest[i]);
        }
    }
    
}

Stack<string> * ConexionesComputadoras::getEntrantes() const{
    
    return entrantes;
    
}

Queue<string> * ConexionesComputadoras::getSalientes(){
    
    return salientes;
    
}

string ConexionesComputadoras::ultimaConexion(){
    
    std::vector <Persona*> registro = archivo.get_registro();
        
    string horaRecienteO = "0:0:0";
    string horaRecienteD = "0:0:0";
    
    for (int i=0; i<registro.size(); i++){
                
        if ((registro[i]->getIpOrigenCompleto() == IP)&&(registro[i]->getHora() > horaRecienteO)){
            horaRecienteO = registro[i]->getHora();
            
        }
        
        if ((registro[i]->getIpDestinoCompleto() == IP)&&(registro[i]->getHora() > horaRecienteD)){
            horaRecienteD = registro[i]->getHora();
        }
        
    }
    
    
    if(horaRecienteD > horaRecienteO){
        
        horaRecienteD = "Destino a las " + horaRecienteD;
        
        return horaRecienteD;
    }else{
        
        horaRecienteO = "Origen a las " + horaRecienteD;

        return horaRecienteO;

    }
}

int ConexionesComputadoras::conexionesEntrantes(){
    
    return entrantes->size();
}

int ConexionesComputadoras::conexionesSalientes(){
    
    return salientes->size();

}

std::vector <int> ConexionesComputadoras::conexionesSeguidas(){
    
    std::vector <Persona*> registro = archivo.get_registro();
    std::vector<int> conexiones;
    
    int puertoInternet = 80;
    int puertoInternetDos = 443;

    //ciclo for es del tamaño del registro -2 para evitar errores al llegar a los ultimos sitios
    
    for (int i=0; i<registro.size() - 2;i++){
        
        //Se puede editar el if para cambiarlo a buscar por URL en lugar de puerto.
        //Se cambia en el segundo if por getUrl() en lugar de get_pDest().
        
        if((registro[i]->getIpOrigenCompleto() == IP)&&(registro[i+1]->getIpOrigenCompleto() == IP)&&(registro[i+2]->getIpOrigenCompleto() == IP)){
            if((registro[i]->get_pDest()== puertoInternet || puertoInternetDos)&&(registro[i+1]->get_pDest() == puertoInternet || puertoInternetDos)&&(registro[i+2]->get_pDest() == puertoInternet || puertoInternetDos)){
                
                if((registro[i]->getIpDestinoCompleto()== registro[i+1]->getIpDestinoCompleto())&&(registro[i+1]->getIpDestinoCompleto()== registro[i+2]->getIpDestinoCompleto())){
                    
                    conexiones.push_back(i);
                    
                }
                
            }
        }
    }
    
    return conexiones;
    
}


HashMap<string, int> * ConexionesComputadoras::conexionesPorDia(string fe) {
    
    std::vector <Persona*> registro = archivo.get_registro();
    
    //vector con la lista de paginas sin repeticiones
    std::vector <string> sitios = archivo.sitiosWeb();
    
    HashMap<string, int> * tabla = new HashMap<string, int>(sitios.size());
    
    string fecha = formatoFecha(fe);
    
    for (int p=0; p<sitios.size();p++){
        int contador =0;
        for (int i = 0; i < registro.size(); i++) {
            if ((registro[i]->get_fecha() == fecha)&&(sitios[p] == registro[i]->getUrl())){
                contador = contador +1;
            }
        }
        if((sitios[p] != "-")&&(sitios[p] != "reto.com")){
            tabla->put(sitios[p], contador);
        }
    }
    
    return tabla;
}


BST<std::pair<std::string, int>>*  ConexionesComputadoras::top(int n, string fecha) {

    BST<std::pair<std::string, int>> * bst = new BST<std::pair<std::string, int>>();
    

    HashMap<std::string, int>* conexiones = conexionesPorDia(fecha);
    
    // Convertir el HashMap a un vector para facilitar la ordenación
    std::vector<std::pair<string, int>> sitiosConAccesos;

    const std::vector<std::string>& status = conexiones->getStatus();
    const std::vector<string>& keys = conexiones->getKeys();
    const std::vector<int>& values = conexiones->getValues();

    for (int i = 0; i < conexiones->capacity(); ++i) {
        if (status[i] == "ocupado") {
            sitiosConAccesos.push_back({keys[i], values[i]});
        }
    }

    // Ordenar el vector por el número de accesos (de mayor a menor)
    std::sort(sitiosConAccesos.begin(), sitiosConAccesos.end(),
              [](const std::pair<string, int>& a, const std::pair<string, int>& b) {
                  return a.second > b.second;
              });
    
    for (int i = 0; i < n && i < sitiosConAccesos.size(); ++i) {
        bst->insertPair(std::make_pair(sitiosConAccesos[i].first, sitiosConAccesos[i].second));
    }
    
    std::cout << "Top " << n << " registros en " << fecha << std::endl;

    bst->imp(n);
        
    delete conexiones;
    
    return bst;

}

std::string ConexionesComputadoras::formatoFecha(const std::string& fecha) {
    std::istringstream fechasss(fecha);
    std::string token;
    std::vector<std::string> partes;

    while (getline(fechasss, token, '-')) {
        if (token.size() == 2 && token[0] == '0') {
            token.erase(0, 1);
        }
        partes.push_back(token);
    }

    std::ostringstream nuevaFecha;
    if (!partes.empty()) {
        nuevaFecha << partes[0];

        for (size_t i = 1; i < partes.size(); ++i) {
            nuevaFecha << '-' << partes[i];
        }
    }

    return nuevaFecha.str();
}

std::vector <string> ConexionesComputadoras::dominios(string ip){
    
    std::vector <Persona*> registro = archivo.get_registro();
    std::vector <string> dominios;
    int puerto1 = 80;
    int puerto2 = 443;


    for (int i=0; i<registro.size(); i++){
        
        if(registro[i]->getIpOrigenCompleto() == ip){
            
            if ((registro[i]->get_pDest() == puerto1 || registro[i]->get_pDest() == puerto2)){
                
                dominios.push_back(registro[i]->getUrl());
                
            }
        }
    }
    
    return dominios;
}









