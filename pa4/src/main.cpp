#include <iostream>
#include "unionFind.hpp"
#include "heap.hpp"

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    Heap heap(m);  // Criando o heap para armazenar até m arestas

    for (int i = 0; i < m; i++) {
        Aresta aresta;
        cin >> aresta.u >> aresta.v >> aresta.custo;
        heap.Inserir(aresta);  // Inserindo cada aresta no heap
    }

    UnionFind uf(n);

    int custoTotal = 0;
    int arestasSelecionadas = 0;

    // Aplicando o algoritmo de Kruskal com o Heap
    while (!heap.Vazio() && arestasSelecionadas < n - 1) {
        Aresta aresta = heap.Remover();
        int u = aresta.u;
        int v = aresta.v;
        int custo = aresta.custo;

        if (uf.Find(u) != uf.Find(v)) {
            uf.Union(u, v);
            custoTotal += custo;
            arestasSelecionadas++;
        }
    }

    // Imprime o custo total da Árvore Geradora Mínima
    cout << custoTotal << endl;

    return 0;
}
