#ifndef HEAP_HPP
#define HEAP_HPP

#include "unionFind.hpp"

class Heap{

    public:
        Heap(int maxsize);
        ~Heap();

        void Inserir(Aresta x);
        Aresta Remover();

        //Retorna true caso o heap esteja vazio, false caso contrário.
        bool Vazio();

    private:
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);

        int tamanho;
        Aresta* data;  // Alteração para armazenar arestas
};


#endif
