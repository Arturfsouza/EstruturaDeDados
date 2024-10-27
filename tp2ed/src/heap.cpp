#include "heap.hpp"
#include <stdexcept>
#include <algorithm>

Heap::Heap(int maxsize) {
    this->maxsize = maxsize;  // Atribui o valor de maxsize ao atributo da classe
    tamanho = 0;
    data = new Estado[maxsize + 1];
}

Heap::~Heap() {
    delete[] data;
}

void Heap::Inserir(Estado x) {
    if (tamanho >= maxsize) {
        throw std::overflow_error("Heap overflow");
    }

    data[tamanho] = x;
    int i = tamanho;
    int p = GetAncestral(i);
    while (i > 0 && Comparar(data[i], data[p])) {
        std::swap(data[i], data[p]);
        i = p;
        p = GetAncestral(i);
    }
    tamanho++;
}

Estado Heap::Remover() {
    if (Vazio()) {
        throw std::underflow_error("Heap underflow");
    }

    Estado x = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;

    int i = 0;
    while (true) {
        int esq = GetSucessorEsq(i);
        int dir = GetSucessorDir(i);
        int menor = i;

        if (esq < tamanho && Comparar(data[esq], data[menor])) {
            menor = esq;
        }
        if (dir < tamanho && Comparar(data[dir], data[menor])) {
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

bool Heap::Vazio() {
    return (tamanho == 0);
}

int Heap::GetAncestral(int posicao) {
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao) {
    return 2 * posicao + 1;
}

int Heap::GetSucessorDir(int posicao) {
    return 2 * posicao + 2;
}

bool Heap::Comparar(Estado a, Estado b) {
    return a.custo < b.custo; // Compara baseado no custo acumulado
}
