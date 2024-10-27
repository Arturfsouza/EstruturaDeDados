#include "../include/grafo_lista.hpp"
#include <limits>
#include <stdexcept>

const double INF = std::numeric_limits<double>::infinity();

GrafoLista::GrafoLista(int n) {
    this->n = n;
    clareiras = new Coordenada[n];
    adj = new std::pair<int, double>*[n];
    tamanhoLista = new int[n];
    for (int i = 0; i < n; ++i) {
        adj[i] = nullptr;
        tamanhoLista[i] = 0;
    }
}

GrafoLista::~GrafoLista() {
    delete[] clareiras;
    for (int i = 0; i < n; ++i) {
        delete[] adj[i];
    }
    delete[] adj;
    delete[] tamanhoLista;
}

void GrafoLista::adicionarAresta(int u, int v, double peso) {
    std::pair<int, double>* novaLista = new std::pair<int, double>[tamanhoLista[u] + 1];
    for (int i = 0; i < tamanhoLista[u]; ++i) {
        novaLista[i] = adj[u][i];
    }
    novaLista[tamanhoLista[u]] = std::make_pair(v, peso);
    delete[] adj[u];
    adj[u] = novaLista;
    tamanhoLista[u]++;
}

void GrafoLista::setCoordenada(int vertice, double x, double y) {
    clareiras[vertice] = std::make_pair(x, y);
}

Coordenada GrafoLista::getCoordenada(int vertice) const {
    return clareiras[vertice];
}

std::pair<int, double>* GrafoLista::getAdjacencias(int vertice, int& tamanho) const {
    tamanho = tamanhoLista[vertice];
    return adj[vertice];
}
