#include <iostream>
#include "../include/heap.hpp"

Heap::Heap(int maxsize){
    tamanho = 0;
    data = new int[maxsize + 1];
}

Heap::~Heap(){
    delete[] data;
}

void Heap::Inserir(int x){
    data[tamanho] = x;
    int i = tamanho;
    int p = (i - 1)/2;
    while(data[i]<data[p]){
        int aux = data[i];
        data[i] = data[p];
        data[p] = aux;
        i = p;
        p = (i - 1)/2;
    }
    tamanho = tamanho + 1;
}

int Heap::Remover(){
    int x = data[0];
    data[0] = data[tamanho-1];
    tamanho = tamanho -1;
    int i = 0;
    while (true) {
        int esq = GetSucessorEsq(i);
        int dir = GetSucessorDir(i);
        int menor = i;

        if (esq < tamanho && data[esq] < data[menor]) {
            menor = esq;
        }
        if (dir < tamanho && data[dir] < data[menor]) {
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
    return 2*posicao +2;
}