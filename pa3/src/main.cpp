#include "ListaAdjacencia.hpp"
#include "graph.hpp"
#include <iostream>
#include <string>


int main(int argc, char* argv[]){
    if(argc != 2){
        std::cerr << "Uso " << argv[0] <<" <operacao> " << std::endl;
        return 1;
    }

    std::string operacao = argv[1];

    int n;
    std::cin >> n;

    Grafo grafo;

    for (int i = 0; i < n; i++) {
        grafo.InsereVertice();  // Insere todos os vértices
        //std::cout << "Vértice " << i << " inserido." << std::endl;
    }

    for (int i = 0; i < n; i++) {
        int m;
        std::cin >> m;
        //std::cout << "Vértice " << i << " tem " << m << " vizinhos: ";
        for (int j = 0; j < m; j++) {
            int vizinho;
            std::cin >> vizinho;
            grafo.InsereAresta(i, vizinho);  // Insere as arestas após todos os vértices serem inseridos
            //std::cout << vizinho << " ";
        }
    }

    if(operacao == "-d"){
        std::cout<<grafo.QuantidadeVertices() << std::endl;
        std::cout<<grafo.QuantidadeArestas() << std::endl;
        std::cout<<grafo.GrauMinimo() << std::endl;
        std::cout<<grafo.GrauMaximo() << std::endl;
    }
    else if(operacao == "-n"){
        for(int i =0; i<n; i++){
            grafo.ImprimeVizinhos(i);
            std::cout<<std::endl;
        }
    }
    else if(operacao == "-k"){
        std::cout << (grafo.Completo() ? 1 : 0) << std::endl;
    }
    else{
        std::cerr<< "Operacao Invalida!" << std::endl;
        return 1;
    }
    return 0;
}