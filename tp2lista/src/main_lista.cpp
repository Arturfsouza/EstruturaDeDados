#include <iostream>
#include <cmath>
#include <limits>
#include <chrono>
#include "../include/grafo_lista.hpp"
#include "heap.hpp"

using namespace std;
using namespace chrono;

const double INF = numeric_limits<double>::infinity();

double distanciaEuclidiana(Coordenada a, Coordenada b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

bool dijkstra(GrafoLista &grafo, int n, double s, int q) {
    double** dist = new double*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new double[q + 1];
        fill(dist[i], dist[i] + q + 1, INF);
    }
    Heap pq((n * (n - 1)) +1); // Heap personalizado
    
    dist[0][0] = 0;
    pq.Inserir({0, 0, 0}); // (vértice, custo, portais usados)

    while (!pq.Vazio()) {
        Estado atual = pq.Remover();
        int u = atual.vertice;
        double custo = atual.custo;
        int portais_usados = atual.portais_usados;

        if (u == n - 1 && custo <= s && portais_usados <= q) {
            for (int i = 0; i < n; ++i) {
                delete[] dist[i];
            }
            delete[] dist;
            return true;
        }

        int tamanho;
        auto adj = grafo.getAdjacencias(u, tamanho);
        for (int i = 0; i < tamanho; ++i) {
            int v = adj[i].first;
            double peso = adj[i].second;
            int novos_portais_usados = portais_usados + (peso == 0);
            double novo_custo = custo + peso;

            if (novos_portais_usados <= q && novo_custo < dist[v][novos_portais_usados]) {
                dist[v][novos_portais_usados] = novo_custo;
                pq.Inserir({v, novo_custo, novos_portais_usados});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete[] dist[i];
    }
    delete[] dist;

    return false;
}

bool aStar(GrafoLista &grafo, int n, double s, int q) {
    double** dist = new double*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new double[q + 1];
        fill(dist[i], dist[i] + q + 1, INF);
    }
    Heap pq((n * (n - 1)) +1); // Heap personalizado

    dist[0][0] = 0;
    pq.Inserir({0, 0, 0}); // (vértice, custo, portais usados)

    while (!pq.Vazio()) {
        Estado atual = pq.Remover();
        int u = atual.vertice;
        double custo = atual.custo;
        int portais_usados = atual.portais_usados;

        if (u == n - 1 && custo <= s && portais_usados <= q) {
            for (int i = 0; i < n; ++i) {
                delete[] dist[i];
            }
            delete[] dist;
            return true;
        }

        int tamanho;
        auto adj = grafo.getAdjacencias(u, tamanho);
        for (int i = 0; i < tamanho; ++i) {
            int v = adj[i].first;
            double peso = adj[i].second;
            int novos_portais_usados = portais_usados + (peso == 0);
            double novo_custo = custo + peso;

            if (novos_portais_usados <= q && novo_custo < dist[v][novos_portais_usados]) {
                dist[v][novos_portais_usados] = novo_custo;
                double heuristica = distanciaEuclidiana(grafo.getCoordenada(v), grafo.getCoordenada(n - 1));
                pq.Inserir({v, novo_custo + heuristica, novos_portais_usados});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete[] dist[i];
    }
    delete[] dist;

    return false;
}

void executarAnaliseExperimental(int n, int m, int k, double s, int q) {
    GrafoLista grafo(n);

    // Inicialização de coordenadas
    for (int i = 0; i < n; ++i) {
        double x = rand() % 100;
        double y = rand() % 100;
        grafo.setCoordenada(i, x, y);
    }

    // Inicialização de arestas
    for (int i = 0; i < m; ++i) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) {
            double peso = distanciaEuclidiana(grafo.getCoordenada(u), grafo.getCoordenada(v));
            grafo.adicionarAresta(u, v, peso);
        }
    }

    // Inicialização de portais
    for (int i = 0; i < k; ++i) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) {
            grafo.adicionarAresta(u, v, 0);
        }
    }

    // Medição do tempo para Dijkstra
    auto inicio = high_resolution_clock::now();
    bool resultado_dijkstra = dijkstra(grafo, n, s, q);
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>(fim - inicio).count();
    cout << "Tempo de execução Dijkstra (Lista de Adjacência): " << duracao << " ms" << endl;

    // Medição do tempo para A*
    inicio = high_resolution_clock::now();
    bool resultado_astar = aStar(grafo, n, s, q);
    fim = high_resolution_clock::now();
    duracao = duration_cast<milliseconds>(fim - inicio).count();
    cout << "Tempo de execução A* (Lista de Adjacência): " << duracao << " ms" << endl;
}

int main() {
    srand(time(NULL));

 // Parâmetros do grafo
 // Parâmetros do grafo
    int n = 2000; // Número de vértices
    int m = 1999000; // Número de arestas
    int k = 2000; // Número de portais
    double s = 2000.0; // Energia máxima
    int q = 200; // Número máximo de portais que podem ser usados

    // Executar análise experimental
    executarAnaliseExperimental(n, m, k, s, q);

    return 0;
}
