#include <iostream>
#include "../include/heap.hpp"

Heap::Heap(int maxsize){
    tamanho = 0;
    data = new Aresta[maxsize + 1];  // Alocando para Arestas
}

Heap::~Heap(){
    delete[] data;
}

void Heap::Inserir(Aresta x){
    data[tamanho] = x;
    int i = tamanho;
    int p = (i - 1)/2;
    while(i > 0 && data[i].custo < data[p].custo){  // Comparando pelo custo da aresta
        std::swap(data[i], data[p]);
        i = p;
        p = (i - 1)/2;
    }
    tamanho = tamanho + 1;
}

Aresta Heap::Remover(){
    Aresta x = data[0];
    data[0] = data[tamanho-1];
    tamanho = tamanho -1;
    int i = 0;
    while (true) {
        int esq = GetSucessorEsq(i);
        int dir = GetSucessorDir(i);
        int menor = i;

        if (esq < tamanho && data[esq].custo < data[menor].custo) {  // Comparando pelo custo
            menor = esq;
        }
        if (dir < tamanho && data[dir].custo < data[menor].custo) {  // Comparando pelo custo
            menor = dir;
        }

        if (menor != i) {
            std::swap(data[i], data[menor]);
            i = menor;
        } else {
            break;
        }
    }

    return x;
}


bool Heap::Vazio(){
    return (tamanho == 0);
}

int Heap::GetAncestral(int posicao){
    return (posicao-1)/2;
}

int Heap::GetSucessorEsq(int posicao){
    return 2*posicao + 1;
}

int Heap::GetSucessorDir(int posicao){
    return 2*posicao + 2;
}
