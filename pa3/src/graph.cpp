#include "graph.hpp"
#include "ListaAdjacencia.hpp"
#include <iostream>

// Construtor
Grafo::Grafo() : vertices() {}

// Destrutor
Grafo::~Grafo() {}

// Insere um novo vértice (cria uma nova lista encadeada para os vizinhos)
void Grafo::InsereVertice() {
    ListaAdjacencia* novaLista = new ListaAdjacencia();
    vertices.InsereFinal(TipoItem(novaLista));  // Adiciona a nova lista de adjacência
}

// Insere uma aresta entre os vértices v e w
void Grafo::InsereAresta(int v, int w) {
    if (v >= 0 && v < QuantidadeVertices() && w >= 0 && w < QuantidadeVertices()) {
        ListaAdjacencia* listaV = vertices.GetItem(v).GetListaAdjacencia();
        ListaAdjacencia* listaW = vertices.GetItem(w).GetListaAdjacencia();

        if (listaV->Pesquisa(w).GetChave() == -1) {
            listaV->InsereFinal(TipoItem(w));  
            std::cout << "Aresta inserida entre " << v << " e " << w << std::endl;
        }

        if (listaW->Pesquisa(v).GetChave() == -1) {
            listaW->InsereFinal(TipoItem(v));  
            std::cout << "Aresta inserida entre " << w << " e " << v << std::endl;
        }
    } else {
        std::cerr << "Erro: Vértices inválidos!" << std::endl;
    }
}



// Retorna a quantidade de vértices no grafo
int Grafo::QuantidadeVertices() {
    return vertices.GetTamanho();
}

// Retorna a quantidade de arestas no grafo
int Grafo::QuantidadeArestas() {
    int totalArestas = 0;

    for (int i = 0; i < QuantidadeVertices(); i++) {
        ListaAdjacencia* listaV = vertices.GetItem(i).GetListaAdjacencia();
        totalArestas += listaV->GetTamanho();
    }

    return totalArestas / 2;  // Dividido por 2 porque cada aresta é contada duas vezes em um grafo não-direcionado
}

// Retorna o grau mínimo do grafo
int Grafo::GrauMinimo() {
    if (QuantidadeVertices() == 0) return 0;

    int minGrau = vertices.GetItem(0).GetListaAdjacencia()->GetTamanho();
    std::cout << "Grau do vértice 0: " << minGrau << std::endl;
    for (int i = 1; i < QuantidadeVertices(); i++) {
        int grau = vertices.GetItem(i).GetListaAdjacencia()->GetTamanho();
        std::cout << "Grau do vértice " << i << ": " << grau << std::endl;
        if (grau < minGrau) {
            minGrau = grau;
        }
    }
    return minGrau;
}

// Retorna o grau máximo do grafo
int Grafo::GrauMaximo() {
    if (QuantidadeVertices() == 0) return 0;

    int maxGrau = vertices.GetItem(0).GetListaAdjacencia()->GetTamanho();
    std::cout << "Grau do vértice 0: " << maxGrau << std::endl;
    for (int i = 1; i < QuantidadeVertices(); i++) {
        int grau = vertices.GetItem(i).GetListaAdjacencia()->GetTamanho();
        std::cout << "Grau do vértice " << i << ": " << grau << std::endl;
        if (grau > maxGrau) {
            maxGrau = grau;
        }
    }
    return maxGrau;
}

// Imprime os vizinhos de um vértice
void Grafo::ImprimeVizinhos(int v) {
    if (v < QuantidadeVertices()) {
        vertices.GetItem(v).GetListaAdjacencia()->Imprime();  // Imprime todos os vizinhos do vértice v
    } else {
        std::cerr << "Erro: Vértice inválido!" << std::endl;
    }
}

bool Grafo::Completo(){
    int numVertices = QuantidadeVertices();

    // Verifica se cada vértice tem exatamente (n-1) vizinhos
    for(int i = 0; i<numVertices;i++){
        ListaAdjacencia* listaV = vertices.GetItem(i).GetListaAdjacencia();
        if(listaV->GetTamanho() != numVertices -1){
            return false;  // Se algum vértice não tem n-1 vizinhos, o grafo não é completo
        }
    }
    return true;  // Todos os vértices têm n-1 vizinhos, o grafo é completo
}
