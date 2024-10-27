#ifndef GRAFO_LISTA_HPP
#define GRAFO_LISTA_HPP

#include <utility>

typedef std::pair<double, double> Coordenada;

class GrafoLista {
public:
    GrafoLista(int n);
    ~GrafoLista();

    void adicionarAresta(int u, int v, double peso);
    void setCoordenada(int vertice, double x, double y);
    Coordenada getCoordenada(int vertice) const;

    std::pair<int, double>* getAdjacencias(int vertice, int& tamanho) const;

private:
    int n;
    std::pair<int, double>** adj;
    int* tamanhoLista;
    Coordenada* clareiras;
};

#endif
