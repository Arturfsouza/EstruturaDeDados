#ifndef HEAP_HPP
#define HEAP_HPP

struct Estado {
    int vertice;
    double custo;
    int portais_usados;
};

class Heap {
public:
    Heap(int maxsize);
    ~Heap();

    void Inserir(Estado x);
    Estado Remover();
    bool Vazio();

private:
    int GetAncestral(int posicao);
    int GetSucessorEsq(int posicao);
    int GetSucessorDir(int posicao);
    bool Comparar(Estado a, Estado b);

    int tamanho;
    Estado* data;
    int maxsize;  // Para armazenar o tamanho máximo do heap
};

#endif
