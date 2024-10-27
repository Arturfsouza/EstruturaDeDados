#include "ListaAdjacencia.hpp"
#include <iostream>


// Implementação da ListaEncadeada

ListaAdjacencia::ListaAdjacencia() {
    primeiro = new TipoCelula();
    ultimo = primeiro;
    tamanho = 0;
}

ListaAdjacencia::~ListaAdjacencia() {
    Limpa();
    delete primeiro;
}

void ListaAdjacencia::InsereFinal(TipoItem item) {
    TipoCelula* nova = new TipoCelula();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
}

TipoItem ListaAdjacencia::Pesquisa(TipoChave c) {
    TipoCelula* p = primeiro->prox;
    while (p != nullptr) {
        if (p->item.GetChave() == c) {
            return p->item;
        }
        p = p->prox;
    }
    return TipoItem();  // Retorna item com chave -1 se não encontrado
}

void ListaAdjacencia::Imprime() {
    TipoCelula* p = primeiro->prox;
    while (p != nullptr) {
        p->item.Imprime();
        p = p->prox;
    }
    std::cout << std::endl;
}

void ListaAdjacencia::Limpa() {
    TipoCelula* p;
    while (primeiro->prox != nullptr) {
        p = primeiro->prox;
        primeiro->prox = p->prox;
        delete p;
    }
    ultimo = primeiro;
    tamanho = 0;
}

TipoCelula* ListaAdjacencia::Posiciona(int pos, bool antes = false) {
    if (pos > tamanho || pos < 0) {
        throw std::out_of_range("Posição inválida!");
    }

    TipoCelula* p = primeiro;
    for (int i = 0; i < pos; i++) {  // Mudei o loop para começar de 0
        p = p->prox;
    }

    if (!antes && p->prox != nullptr) {
        p = p->prox;
    }

    return p;
}


TipoItem ListaAdjacencia::GetItem(int pos) {
    TipoCelula* p = Posiciona(pos);
    return p->item;
}

void ListaAdjacencia::SetItem(TipoItem item, int pos) {
    TipoCelula* p = Posiciona(pos);
    p->item = item;
}

void TipoItem::Imprime() {
    if (listaAdjacencia) {
        listaAdjacencia->Imprime();  // Imprime a lista de adjacência
    } else {
        std::cout << chave << " ";  // Imprime a chave
    }
}