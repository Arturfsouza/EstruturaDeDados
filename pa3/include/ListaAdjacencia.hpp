#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP
#include <iostream>

// Definição do TipoChave e TipoItem
typedef int TipoChave;

// Forward declaration da classe ListaAdjacencia
class ListaAdjacencia;

class TipoItem {
public:
    TipoItem() : chave(-1), listaAdjacencia(nullptr) {}  // Construtor padrão
    TipoItem(TipoChave c) : chave(c), listaAdjacencia(nullptr) {}  // Construtor com chave
    TipoItem(ListaAdjacencia* lista) : chave(-1), listaAdjacencia(lista) {}  // Construtor para lista de adjacência

    void SetChave(TipoChave c) { chave = c; }
    TipoChave GetChave() { return chave; }

    void SetListaAdjacencia(ListaAdjacencia* lista) { listaAdjacencia = lista; }
    ListaAdjacencia* GetListaAdjacencia() { return listaAdjacencia; }

    void Imprime();
   

private:
    TipoChave chave;
    ListaAdjacencia* listaAdjacencia;  // Ponteiro para a lista de adjacência
};

class TipoCelula {
public:
    TipoCelula() : prox(nullptr) {}
    TipoItem item;
    TipoCelula* prox;
};


class Lista{
    public:
        Lista(){tamanho = 0;};
        int GetTamanho() {return tamanho;};
        bool Vazia(){return tamanho == 0;};

        virtual TipoItem GetItem(int pos) = 0;
        virtual void SetItem(TipoItem item, int pos) = 0;
        virtual void InsereFinal(TipoItem item) = 0;
        virtual TipoItem Pesquisa(TipoChave c) = 0;
        virtual void Imprime() = 0;
        virtual void Limpa() = 0;
    protected:
        int tamanho;
};


class ListaAdjacencia : public Lista {
public:
    ListaAdjacencia();
    ~ListaAdjacencia();

    TipoItem GetItem(int pos);
    void SetItem(TipoItem item, int pos);
    void InsereFinal(TipoItem item);
    TipoItem Pesquisa(TipoChave c);
    void Imprime();
    void Limpa();

private:
    TipoCelula* primeiro;
    TipoCelula* ultimo;
    TipoCelula* Posiciona(int pos, bool antes);
};

#endif

