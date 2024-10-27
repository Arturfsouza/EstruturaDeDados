#include "grafo_matriz.hpp"
#include <limits>
#include <stdexcept>

const double INF = std::numeric_limits<double>::infinity();

GrafoMatriz::GrafoMatriz(int n) {
    this->n = n;
    clareiras = new Coordenada[n];
    adj = new double*[n];
    for (int i = 0; i < n; ++i) {
        adj[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            adj[i][j] = (i == j) ? 0 : INF;
        }
    }
}

GrafoMatriz::~GrafoMatriz() {
    delete[] clareiras;
    for (int i = 0; i < n; ++i) {
        delete[] adj[i];
    }
    delete[] adj;
}

void GrafoMatriz::adicionarAresta(int u, int v, double peso) {
    adj[u][v] = peso;
}

void GrafoMatriz::setCoordenada(int vertice, double x, double y) {
    clareiras[vertice] = std::make_pair(x, y);
}

Coordenada GrafoMatriz::getCoordenada(int vertice) const {
    return clareiras[vertice];
}

double** GrafoMatriz::getAdjacencias() const {
    return adj;
}
