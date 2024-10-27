#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include "heap.hpp"

using namespace std;

typedef pair<double, double> Coordenada;

const double INF = numeric_limits<double>::infinity();

struct Grafo {
    Coordenada* clareiras;
    pair<int, double>** adj;
    int n, m;

    Grafo(int n) {
        this->n = n;
        clareiras = new Coordenada[n];
        adj = new pair<int, double>*[n];
        for (int i = 0; i < n; ++i) {
            adj[i] = new pair<int, double>[n]; // Na prática, você precisaria controlar o tamanho desta lista para cada vértice
            for (int j = 0; j < n; ++j) {
                adj[i][j] = make_pair(-1, INF);
            }
        }
    }

    ~Grafo() {
        delete[] clareiras;
        for (int i = 0; i < n; ++i) {
            delete[] adj[i];
        }
        delete[] adj;
    }

    void adicionarAresta(int u, int v, double peso) {
        adj[u][v] = make_pair(v, peso);
    }
};

double distanciaEuclidiana(Coordenada a, Coordenada b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

bool dijkstra(Grafo &grafo, int n, double s, int q) {
    double** dist = new double*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new double[q + 1];
        fill(dist[i], dist[i] + q + 1, INF);
    }
    Heap pq(n * (q + 1)); // Heap personalizado
    
    dist[0][0] = 0;
    pq.Inserir({0, 0, 0}); // (vértice, custo, portais usados)

    while (!pq.Vazio()) {
        Estado atual = pq.Remover();
        int u = atual.vertice;
        double custo = atual.custo;
        int portais_usados = atual.portais_usados;

        if (u == n - 1 && custo <= s && portais_usados <= q) return true;

        for (int i = 0; i < n; ++i) {
            if (grafo.adj[u][i].first != -1) {
                int v = grafo.adj[u][i].first;
                double peso = grafo.adj[u][i].second;
                int novos_portais_usados = portais_usados + (peso == 0);
                double novo_custo = custo + peso;

                if (novos_portais_usados <= q && novo_custo < dist[v][novos_portais_usados]) {
                    dist[v][novos_portais_usados] = novo_custo;
                    pq.Inserir({v, novo_custo, novos_portais_usados});
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete[] dist[i];
    }
    delete[] dist;

    return false;
}

bool aStar(Grafo &grafo, int n, double s, int q) {
    double** dist = new double*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new double[q + 1];
        fill(dist[i], dist[i] + q + 1, INF);
    }
    Heap pq(n * (q + 1)); // Heap personalizado

    dist[0][0] = 0;
    pq.Inserir({0, 0, 0}); // (vértice, custo, portais usados)

    while (!pq.Vazio()) {
        Estado atual = pq.Remover();
        int u = atual.vertice;
        double custo = atual.custo;
        int portais_usados = atual.portais_usados;

        if (u == n - 1 && custo <= s && portais_usados <= q) return true;

        for (int i = 0; i < n; ++i) {
            if (grafo.adj[u][i].first != -1) {
                int v = grafo.adj[u][i].first;
                double peso = grafo.adj[u][i].second;
                int novos_portais_usados = portais_usados + (peso == 0);
                double novo_custo = custo + peso;

                if (novos_portais_usados <= q && novo_custo < dist[v][novos_portais_usados]) {
                    dist[v][novos_portais_usados] = novo_custo;
                    double heuristica = distanciaEuclidiana(grafo.clareiras[v], grafo.clareiras[n - 1]);
                    pq.Inserir({v, novo_custo + heuristica, novos_portais_usados});
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete[] dist[i];
    }
    delete[] dist;

    return false;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    Grafo grafo(n);

    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        grafo.clareiras[i] = {x, y};
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        double peso = distanciaEuclidiana(grafo.clareiras[u], grafo.clareiras[v]);
        grafo.adicionarAresta(u, v, peso);
    }

    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        grafo.adicionarAresta(u, v, 0);
    }

    double s;
    int q;
    cin >> s >> q;

    bool resultado_dijkstra = dijkstra(grafo, n, s, q);
    bool resultado_astar = aStar(grafo, n, s, q);

    cout << (resultado_dijkstra ? 1 : 0) << " " << (resultado_astar ? 1 : 0) << endl;

    return 0;
}
