//
//  main.cpp
//  tarea3
//
//  Created by Aldo Escandon on 18/09/23.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "persona.hpp"
#include <algorithm>
#include "archivo.hpp"
#include <map>
#include <utility>
#include <string>
#include "ConexionesComputadora.hpp"
#include "TreeNode.hpp"
#include "BinaryTree.hpp"
#include "BST.hpp"
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

using std::ifstream;
using namespace std;

template <class T>
void ordenarPorInsercion(std::vector<T*>& vect) {
    int n = vect.size();
    for (int i = 1; i < n; i++) {
        T* key = vect[i];
        int j = i - 1;

        while (j >= 0 && vect[j]->get_pDest() > key->get_pDest()) {
            vect[j + 1] = vect[j];
            j = j - 1;
        }
        vect[j + 1] = key;
    }
}




template <class T>
int busquedaSecuencial(const std::vector<T*>& e, const std::string& valor) {
    int i = 0;
    int encontrado = 0;

    long int size = e.size();

    while (i < size) {
        if (compararNom(e[i], valor) || compararFech(e[i], valor) || compararMail(e[i], valor)) {
            encontrado = encontrado +1;
        }
        ++i;
    }

    return encontrado;
}

template <class T>
bool compararNom(const T& vector, const std::string& valor) {
    // Implementa la comparación para buscar por nombre en Registro
    return vector->get_nom() == valor;
}

template <class T>
bool compararFech(const T& vector, const std::string& valor) {
    // Implementa la comparación para buscar por nombre en Registro
    return vector->get_fecha() == valor;
}

template <class T>
bool compararMail(const T& vector, const std::string& valor) {
    // Implementa la comparación para buscar por nombre en Registro
    return vector->get_email() == valor;
}




int main(int argc, const char * argv[])
{
    Archivo archivo;
    
    archivo.leer_archivo();
    
    //obtenemos el vector sacado de la lectura del archivo
    vector <Persona*> registro = archivo.get_registro();
    
    //ordenamos el vector por numero de puerto destino para resolver el ejercicio 7
    ordenarPorInsercion(registro);

    //RESPUESTA PREGUNTA 1
    cout << "El numero de registros son: " << archivo.get_num() << endl;
    cout << endl;
    
    //RESPUESTA PREGUNTA 2
    cout << "Ingresa una fecha para ver el número de registros de ese día" << endl;
    string prueba = "11-8-2020";
    
    cout << "El número de registros para el día es: " << busquedaSecuencial(registro, prueba) << endl;
    cout << endl;

    
    //RESPUESTA PREGUNTA 3
    std::vector<std::string> personas = {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
                
        for (const std::string& persona : personas) {
            int cantidad = busquedaSecuencial(registro, persona);
            std::cout << "Le pertenecen " << cantidad << " computadoras a " << persona << std::endl;
        }
    cout << endl;


        
    //RESPUESTA PREGUNTA 4
    string redInterna = archivo.get_ip();
    cout << "La dirección de red interna de la compañía es: " << redInterna << endl;
    cout << endl;


    //REPUESTA PREGUNTA 5
    string email = "server.reto.com";
    int z = busquedaSecuencial(registro, email);
    if (z == 0){
        cout << "No existe ninguna computadora llamada " << email << endl;
    }else if (z == 1){
        cout << "Si existen computadoras llamadas " << email << endl;
    }
    cout << endl;

    
    //RESPUESTA PREGUNTA 6
    //RESPUESTA 6 CON PUERTO DE DESTINO
    
    cout << "Servidores de correo electronico: " << endl;

    vector <string> hola = archivo.get_emails();
    
    for (int i=0;i<hola.size();i++){
        
        if((hola[i] == "outlook.com")||(hola[i] == "gmail.com")||(hola[i] == "mail.yahoo.com")||(hola[i] == "yahoo.com")){
            cout << hola[i] << ", ";
        }
    }
    
    cout << endl;
    cout << endl;
    
    //RESPUESTA 6 CON PUERTO DE ORIGEN
    //Nombre de origen
    cout << "Utilizan el servicio de correo electronico: " << archivo.get_cor() << endl;
    cout << endl;


    
    //RESPUESTA PREGUNTA 7
    vector<int> puertos;
    for(int i=0; i < registro.size();i++){
            if(registro[i]->get_pDest() < 1000){
                puertos.push_back(registro[i]->get_pDest());
            }
        }
    
    std::sort(puertos.begin(), puertos.end());
    auto unique_end = std::unique(puertos.begin(), puertos.end());
        puertos.erase(unique_end, puertos.end());
    
    cout << "Los puertos que se utilizan son: " << endl;
    
        for (const int& num : puertos) {
                cout << num << " ";
            }
    cout << endl;
    
    // -----------------2a Parte Act2.2------------------------------------------------------
    
    /*Tu programa debe de recibir (ya sea al llamar el programa o como petición al usuario) un número entre 1 y 150. Debes de generar la IP interna correspondiente según tu dirección de red (Por ejemplo, si la red interna ubicada en la primera parte del reto es 10.0.15.0, y recibieras el número 28, la IP sería 10.0.15.28).
*/
    
    //Numero que se va a probar es el 143
    
    cout << endl;
    cout << "Parte 2" << endl;
    cout << endl;

    
    bool x = true;
    int ip_ingresada;

    while (x) {

        cout << "Ingresa un número entre el 1 y 150 : ";
        cin >>ip_ingresada;
        
        if ((ip_ingresada >= 1)&&(ip_ingresada <= 150)){
            x = false;
        }else{
            cout << "Error numero fuera de rangos" << endl;
        }
    }
    
    //Respuesta pregunta 1
    string newIp = redInterna + "." + std::to_string(ip_ingresada);
    cout << "direccion de ip que se está usando " << newIp   << endl;
    
    ConexionesComputadoras conexiones(newIp, archivo);
    conexiones.llenarEntrantes();
    conexiones.llenarSalientes();
    
    //Respuesta pregunta 2
    string ultimaConexion = conexiones.ultimaConexion();
    cout << "La ultima conexión fue de " << ultimaConexion << endl;
    
    //Respuesta pregunta 3
    cout << "Esta computadora tiene " << conexiones.conexionesEntrantes() << " conexiones entrantes" << endl;
    
    //Respuesta pregunta 4
    cout << "Esta computadora tiene " << conexiones.conexionesSalientes() << " conexiones salientes" << endl;
    
    //Respuesta pregunta 5
    //Si se corre con puerto destino no existen conexiones seguidas
    //Si se corre con el url si existen conexiones seguidas
    bool encontrado = false;
    vector<int> conexion = conexiones.conexionesSeguidas();
    for(int i=0;i<conexion.size();i++){
        cout << "Existen 3 conexiones seguidas a: " << registro[conexion[i]]->getUrl() << endl;
        encontrado = true;
    }
    
    if (encontrado==false){
        cout << "No se encontraron 3 conexiones seguidas a un mismo sitio web" << endl;
    }
    
    //Entrega 3
    //pregunta 1
    
    cout << endl;
    cout << "Parte 3" << endl;
    cout << endl;
    
    HashMap<string, int> * tabla10agosto = conexiones.conexionesPorDia("10-8-2020");
        
    //Pregunta 2
    conexiones.top(5,"12-8-2020");
    cout << endl;
    
    /*Pregunta 3 10,11,12,13,14,17,18,19,20,21
    HashMap<string, int> * tabla11agosto = conexiones.conexionesPorDia("11-8-2020");
    HashMap<string, int> * tabla12agosto = conexiones.conexionesPorDia("12-8-2020");
    HashMap<string, int> * tabla13agosto = conexiones.conexionesPorDia("13-8-2020");
    HashMap<string, int> * tabla14agosto = conexiones.conexionesPorDia("14-8-2020");
    HashMap<string, int> * tabla17agosto = conexiones.conexionesPorDia("17-8-2020");
    HashMap<string, int> * tabla18agosto = conexiones.conexionesPorDia("18-8-2020");
    HashMap<string, int> * tabla19agosto = conexiones.conexionesPorDia("19-8-2020");
    HashMap<string, int> * tabla20agosto = conexiones.conexionesPorDia("20-8-2020");
    HashMap<string, int> * tabla21agosto = conexiones.conexionesPorDia("21-8-2020");
    
    cout << "Top 5 dia por dia" << endl;
    
    conexiones.top(5,"11-8-2020");
    cout << endl;
    conexiones.top(5,"12-8-2020");
    cout << endl;
    conexiones.top(5,"13-8-2020");
    cout << endl;
    conexiones.top(5,"14-8-2020");
    cout << endl;
    conexiones.top(5,"17-8-2020");
    cout << endl;
    conexiones.top(5,"18-8-2020");
    cout << endl;
    conexiones.top(5,"19-8-2020");
    cout << endl;
    conexiones.top(5,"20-8-2020");
    cout << endl;
    conexiones.top(5,"21-8-2020");*/
    
    ////////////////Respuesta a las preguntas //////////////////

    std::vector<std::string> fechas = {"11-8-2020", "12-8-2020", "13-8-2020", "14-8-2020", 
        "17-8-2020", "18-8-2020", "19-8-2020", "20-8-2020", "21-8-2020"};
    std::map<std::string, int> conteo;
    std::map<std::string, int> primeraAparicion;
    std::string ultimaFecha = fechas.back();
    double trafico = 0;
    int sum = 0;
    vector<std::pair<string, int>> traficoAlto;


    for (size_t i = 0; i < fechas.size(); ++i) {
        auto fecha = fechas[i];
        BST<std::pair<std::string, int>>* bst = conexiones.top(5, fecha);
        cout << endl;
        std::vector<std::string> top5Hoy;
        std::vector<std::pair<std::string, int>> top5Data;
        trafico = 0;
        sum = 0;

        bst->visit(1, [&](const std::pair<std::string, int>& info) {
            top5Hoy.push_back(info.first);
            conteo[info.first]++;
            trafico += info.second;
            sum += 1;
            if (primeraAparicion.find(info.first) == primeraAparicion.end()) {
                primeraAparicion[info.first] = i;
            }
            top5Data.push_back(info);
        });

        if (sum > 0) {
            trafico = trafico / sum;
        }

        for (const auto& info : top5Data) {
            if (info.second > trafico) {
                traficoAlto.push_back(info);
            }
        }

        delete bst;
    }

    
    for (const auto& info : conteo) {
        if (info.second == fechas.size()) {
            std::cout << "El sitio " << info.first << " aparece en todas las fechas." << std::endl;
        }
    }

    for (const auto& info : primeraAparicion) {
        if (conteo[info.first] == fechas.size() - info.second && fechas[info.second] != ultimaFecha) {
            std::cout << "El sitio " << info.first << " Ha estado en todas las fechas desde:  " << fechas[info.second] << std::endl;
        }
    }
    
    for (int i =0; i < traficoAlto.size() -1 ; i++) {
        
        cout << "El sitio " << traficoAlto[i].first << " tuvo un trafico alto de: " << traficoAlto[i].second << " en " << fechas[i] << endl;
    }
    
    
    // Entrega 4.2 Actividad Integral de Grafos
    
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "Entrega 4.2" << endl;
    cout << endl;
    
    string ipA = "10.217.177.143";
    
    string nombreRaro = "6j9xlatbxjcjk9zuuewi.org";
    
    //sitio con volumen alto un dia: El sitio target.com tuvo un trafico alto de: 511 en 18-8-2020

    string traficoAltoUnDia = "target.com";
    
    /*std::vector<std::string> fechas = {"11-8-2020", "12-8-2020", "13-8-2020", "14-8-2020", vector previo
        "17-8-2020", "18-8-2020", "19-8-2020", "20-8-2020", "21-8-2020"};*/
    
    Graph<string,string> * graph = new Graph<string,string>();
    map<string, Vertex<string, string> *> vertices;

    
        for (const auto& fecha : fechas) {
            std::vector<std::pair<string, string>> origenADestino = archivo.conexionesOrigenDest(fecha);

            for (const auto &ver : origenADestino) {
                // Verificar y crear el vértice para la IP de origen si aún no existe
                if (vertices.find(ver.first) == vertices.end()) {
                    vertices[ver.first] = new Vertex<string, string>(ver.first);
                    graph->addVertex(vertices[ver.first]);
                }

                // Verificar y crear el vértice para la IP de destino si aún no existe
                if (vertices.find(ver.second) == vertices.end()) {
                    vertices[ver.second] = new Vertex<string, string>(ver.second);
                    graph->addVertex(vertices[ver.second]);
                }

                // Añadir la arista del origen al destino
                graph->addEdge(vertices[ver.first], vertices[ver.second], fecha);

                // Añadir la arista del destino al origen
                graph->addEdge(vertices[ver.second], vertices[ver.first], fecha);
            }
        }

    //Se imprime el grafo si se desea
    //std::cout << *graph << std::endl;
    
    //RESPUESTA PREGUNTA 1
    
    graph->getIncidentePorVertex();
    std::vector<std::pair<string,int>> incidentesCount = graph->getIncidentesCount();
    
    int conexionesConA = 0;
    
    for(int i =0; i< incidentesCount.size();i++){
        if(incidentesCount[i].first == ipA){
            conexionesConA = incidentesCount[i].second;
        }
    }
    cout << "A se ha conectado con: " << conexionesConA << " computadoras" << endl;
    
    std::string ipMasConexiones;
    int max = std::numeric_limits<int>::min();
    
    for (const auto& incidente : incidentesCount) {
        if (incidente.second > max) {
            max = incidente.second;
            ipMasConexiones = incidente.first;
        }
    }
    
    std::cout << "La IP con mas conexiones es: " << ipMasConexiones << " con " << max << std::endl;
    
    //Se queremos resolver la pregunta direccta
    
    if(conexionesConA > max){
        cout << "A no es el vertice con más conexiones salientes" << endl;
    }

    //RESPUESTA PREGUNTA 2
    
    map<string, int> conexionesPorDia;

       for (auto& vertex : graph->getVertices()) {
           for (auto& edge : *vertex->getEdges()) {
               if (edge->getTarget()->getInfo() == ipA) {
                   conexionesPorDia[edge->getInfo()]++;
               }
           }
       }

       // Imprimir los resultados
       for (const auto& par : conexionesPorDia) {
           cout << "Sí existen conexiones hacia A" << endl;
           cout << "Fecha: " << par.first << ", Conexiones a " << ipA << ": " << par.second << endl;
       }
    
    
    //RESPUESTA PREGUNTA 3
    
    cout << endl;
    cout << endl;

        
    Graph<string,string> * graph2 = new Graph<string,string>();
    map<string, Vertex<string, string> *> vert;

    
        for (const auto& fecha : fechas) {
            std::vector<std::pair<string, string>> origenASitio = archivo.conexionesOrigenSitio(fecha);

            for (const auto &ver : origenASitio) {
                
                if (vert.find(ver.first) == vert.end()) {
                    vert[ver.first] = new Vertex<string, string>(ver.first);
                    graph2->addVertex(vert[ver.first]);
                }

                if (vert.find(ver.second) == vert.end()) {
                    vert[ver.second] = new Vertex<string, string>(ver.second);
                    graph2->addVertex(vert[ver.second]);
                }
                
                // Añadir la arista del origen al sitioWeb
                graph2->addEdge(vert[ver.first], vert[ver.second], fecha);
            }
        }
    
    //Se imprime el grafo si se desea
    //std::cout << *graph2 << std::endl;

        map<string, int> conexionesPorDia2;

        for (auto& vertex : graph2->getVertices()) {
            for (auto& edge : *vertex->getEdges()) {
                if (edge->getTarget()->getInfo() == nombreRaro) {
                    conexionesPorDia2[edge->getInfo()]++;
                }
            }
        }
        for (const auto& par : conexionesPorDia2) {
            cout << "Fecha: " << par.first << ", Conexiones a " << nombreRaro << ": " << par.second << endl;
        }
    
    //RESPUESTA PREGUNTA 4
    
    cout << endl;
    
    map<string, int> conexionesPorDia3;

    for (auto& vertex : graph2->getVertices()) {
        for (auto& edge : *vertex->getEdges()) {
            if (edge->getTarget()->getInfo() == traficoAltoUnDia) {
                conexionesPorDia3[edge->getInfo()]++;
            }
        }
    }

    // Imprimir los resultados
    for (const auto& par : conexionesPorDia3) {
        cout << "Fecha: " << par.first << ", Conexiones a " << traficoAltoUnDia << ": " << par.second << endl;
    }
    
    
    // Entrega 5.2 Actividad Integral sobre el uso de diccionarios y conjuntos
    
    // conjunto de strings sin dominio "reto.com"
    
    std::vector <string> dominiosSinReto = archivo.dominiosSinReto();
    
    //diccionario de pares
    
    std::vector<std::pair<string, ConexionesComputadoras>> diccionario;
    
    std::vector <string> ipOrigenTodos = archivo.getIpOrigenSinRepeticiones();
    
    cout << ipOrigenTodos.size() << endl;
        
    
    for (int i=0; i<ipOrigenTodos.size();i++){
        
        ConexionesComputadoras IP(ipOrigenTodos[i], archivo);
        IP.llenarEntrantes();
        IP.llenarSalientes();
        diccionario.push_back(std::make_pair(ipOrigenTodos[i], IP));
    }
    
    
    //RESPUESTA PREGUNTA 1 y 2
     //AL IMPRIMIR SE PUEDE VER UN NOMBRE EN EL CONJUNTO ANÓMALO,  IP = 10.217.177.33, ANOMALÍA = 6j9xlatbxjcjk9zuuewi.org
    
    string anomalia = "6j9xlatbxjcjk9zuuewi.org";
    string anomalia2 = "xmi1bu39gtxzk6eo23vo.net";
    int count;
    std::vector<std::pair<string, string>> lugar;


     for (auto& par : diccionario) {
         
         count = 0;
        
        std::vector dominiosss = par.second.dominios(par.first);
        
        cout << "IP: " << par.first << endl;
        cout << " Dominios: " << endl;
        
        for(int i =0; i<dominiosss.size();i++){
            
            if(dominiosss[i] == anomalia){
                lugar.push_back(std::make_pair(par.first, anomalia));

            }else if(dominiosss[i] == anomalia2){
                lugar.push_back(std::make_pair(par.first, anomalia2));
            }
            
            count = count +1;
            
            cout << dominiosss[i] << endl;
        }
        cout << endl;

    }
    
    
    for (int i = 0 ; i< lugar.size();i++){
        
        cout << "Anomalia detectada en: " << lugar[i].first << " conexión a: " << lugar[i].second << endl;
    }
    
    
    //PREGUNTA 3
    
    
    std::set<std::string> ipsUnicas;
    int cantidad = 0;

    for (int i = 0; i < registro.size(); i++) {
        std::string ipDestino = registro[i]->getIpDestinoCompleto();
        if (ipsUnicas.find(ipDestino) == ipsUnicas.end() && registro[i]->obtenerMailSinNombre() == "reto.com" && ipDestino != "-") {
            cantidad++;
            ipsUnicas.insert(ipDestino);
        }
    }

    std::cout << "La cantidad de computadoras con al menos una conexión entrante del dominio reto.com son: " << cantidad << std::endl;
    
    
    //RESPUESTA PREGUNTA 4
    
    unordered_map<string, pair<int, string>> contadorIP;
    vector<pair<string, string>> ipUnica;

    // Contar la frecuencia de cada IP y almacenar la URL correspondiente
    for (int i = 0; i < registro.size(); i++) {
        if (registro[i]->get_email() != "server.reto.com") {
            string ip = registro[i]->getIpDestinoCompleto();
            contadorIP[ip].first++;
            contadorIP[ip].second = registro[i]->getUrl();
        }
    }

    // Agregar solo las IPs únicas al vector ipUnica hasta un máximo de 10
    for (const auto& par : contadorIP) {
        if (par.second.first == 1) { // Si la IP es única
            ipUnica.push_back(make_pair(par.first, par.second.second));
            if (ipUnica.size() == 10) {
                break;
            }
        }
    }

    // Imprimir las IPs únicas
    
    cout << "Las IPs unicas son: " << endl;
    
    for (int i = 0; i < ipUnica.size(); i++) {
        cout << ipUnica[i].first << endl;
    }
    
    //RESPUESTA PREGUNTA 6
    
    for(int i =0;i<ipUnica.size();i++){
        
        if(lugar[0].second == ipUnica[i].second){
            cout << "Se conectaron los datos. "<< endl;
            cout << "IP origen " << lugar[0].first << " ,IP destino " << ipUnica[i].first << " ,Sitio " << ipUnica[i].second << endl;
        }else if(lugar[1].second ==  ipUnica[i].second){
            cout << "Se conectaron los datos. "<< endl;
            cout << "IP origen " << lugar[1].first << " ,IP destino " << ipUnica[i].first << " ,Sitio " << ipUnica[i].second << endl;
        }
        
    }
    
    //RESPUESTA PREGUNTA 7
    
    vector<pair<string, string>> fechaAnomalia;
    
    for(int i=0;i<registro.size();i++){
        
        for(int k=0;k<ipUnica.size();k++){
            
            if(lugar[k].second == registro[i]->getUrl()){
                fechaAnomalia.push_back(std::make_pair(registro[i]->get_fecha(), lugar[k].second));
            }
            
            
        }
        
    }
    
    for(int i=0;i<fechaAnomalia.size();i++){
        cout << "La primera conexión a : " << fechaAnomalia[i].second << " el día " << fechaAnomalia[i].first <<endl;
    }
    

    
    //LIMPIANDO MEMORIA
    for (auto personaPtr : registro) {
            delete personaPtr;
        }
    
    registro.clear();
    
    
    return 0;
}
    

//("/Users/betolimon/Downloads/equipo10.csv")
//("/Users/aldoescandon/Downloads/equipo10.csv")
