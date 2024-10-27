#ifndef GRAFO_MATRIZ_HPP
#define GRAFO_MATRIZ_HPP

#include <utility>

typedef std::pair<double, double> Coordenada;

class GrafoMatriz {
public:
    GrafoMatriz(int n);
    ~GrafoMatriz();

    void adicionarAresta(int u, int v, double peso);
    void setCoordenada(int vertice, double x, double y);
    Coordenada getCoordenada(int vertice) const;

    double** getAdjacencias() const;

private:
    int n;
    double** adj;
    Coordenada* clareiras;
};

#endif
