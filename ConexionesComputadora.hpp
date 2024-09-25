//
//  ConexionesComputadora.hpp
//  act2.2
//
//  Created by Alberto Limón on 02/10/23.
//

#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp
#include <stdio.h>
#include "Stack.hpp"
#include "Queue.hpp"
#include "archivo.hpp"
#include "Node.hpp"
#include <string>
using std::string;
#include "persona.hpp"
#include <sstream>
#include "HashMap.cpp"
#include "BST.hpp"
#include "BinaryTree.hpp"
#include "TreeNode.hpp"


class ConexionesComputadoras{
    
    private:
        string IP;
        string nombre;
        Archivo archivo;
        Stack<string> *entrantes = new Stack<string>();
        Queue<string> *salientes = new Queue<string>();

    public:
        ConexionesComputadoras(string ip, Archivo arch);
        ~ConexionesComputadoras();
        void llenarEntrantes();
        void llenarSalientes();
        Stack<string> * getEntrantes() const;
        Queue<string> * getSalientes();
        string ultimaConexion();
        int conexionesEntrantes();
        int conexionesSalientes();
        std::vector<int> conexionesSeguidas();
        HashMap<string, int> * conexionesPorDia(string fe);
        BST<std::pair<std::string, int>>* top(int n, string fecha);
        string formatoFecha(const std::string& fecha);
        Stack<string> * obtenerEntrantesPorFecha(string fecha);
        Queue<string> * obtenerSalientesPorFecha(string fecha);
        std::vector <string> dominios(string ip);

    
};




#endif /* ConexionesComputadora_hpp */
