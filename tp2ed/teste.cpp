#include <iostream>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include "include/heap.hpp"

#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int n,m,q;

typedef pair<int,int> Edge;
typedef vector<vector<Edge>> Graph;

vector<int> dijkstra(Graph &g, vector<int> hosp){
    priority_queue<Edge> pq;
    for(int amb : hosp)
        pq.push({-0,amb});
    vector<int> dist(n, INF);

    while(!pq.empty()){
        int w = -pq.top().f;
        int u = pq.top().s;
        pq.pop();
        if(dist[u] <= w){
            continue;}
        dist[u] = w;
        for(auto [v,n_w]: g[u]){
            if (dist[v] > w+n_w){
                pq.push({-(w+n_w), v});
            }
        }
    }
    return dist;
}

void add_edge(Graph &g, int a, int b, int w){
    g[a].push_back({b,w});
    g[b].push_back({a,w});
}

void solve(){
    Graph grp = Graph(n, vector<Edge>());
    for(int i = 0; i<m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        add_edge(grp, a, b, w);
    }
    vector<int> hosp(q);
    for(int &i :hosp){
        cin>>i;
    }
    vector<int> dist = dijkstra(grp, hosp);

    int ans = -1;
    for(int x :dist){
        ans = max(ans,x);
    cout <<ans <<endl;
    }
}

bool aStar(Grafo &grafo, int n, double s, int q) {
    vector<vector<double>> dist(n, vector<double>(q + 1, INF));
    Heap pq(n * (q + 1)); // Heap personalizado
    
    dist[0][0] = 0;
    pq.Inserir(make_tuple(0, 0, 0)); // (vértice, custo, portais usados)

    while (!pq.Vazio()) {
        Estado atual = pq.Remover();
        int u = get<0>(atual);
        double custo = get<1>(atual);
        int portais_usados = get<2>(atual);

        if (u == n - 1 && custo <= s && portais_usados <= q) return true;

        for (auto &[v, peso] : grafo.adj[u]) {
            int novos_portais_usados = portais_usados + (peso == 0);
            double novo_custo = custo + peso + distanciaEuclidiana(grafo.clareiras[v], grafo.clareiras[n - 1]);

            if (novos_portais_usados <= q && novo_custo < dist[v][novos_portais_usados]) {
                dist[v][novos_portais_usados] = novo_custo;
                pq.Inserir(make_tuple(v, novo_custo, novos_portais_usados));
            }
        }
    }

    return false;
}

bool dijkstra(Grafo &grafo, int n, double s, int q) {
    vector<vector<double>> dist(n, vector<double>(q + 1, INF));
    Heap pq(n * (q + 1)); // Heap personalizado
    
    dist[0][0] = 0;
    pq.Inserir(make_tuple(0, 0, 0)); // (vértice, custo, portais usados)

    while (!pq.Vazio()) {
        Estado atual = pq.Remover();
        int u = get<0>(atual);
        double custo = get<1>(atual);
        int portais_usados = get<2>(atual);

        if (u == n - 1 && custo <= s && portais_usados <= q) return true;

        for (auto &[v, peso] : grafo.adj[u]) {
            int novos_portais_usados = portais_usados + (peso == 0);
            double novo_custo = custo + peso;

            if (novos_portais_usados <= q && novo_custo < dist[v][novos_portais_usados]) {
                dist[v][novos_portais_usados] = novo_custo;
                pq.Inserir(make_tuple(v, novo_custo, novos_portais_usados));
            }
        }
    }

    return false;
}



int main(){
    while(cin >> n >> m >> q){
        solve();}

}