#include <iostream>

class TipoNo{
    public:
        TipoNo();
    private:
        TipoItem item;
        TipoNo *esq;
        TipoNo *dir;

    friend class ArvoreBinaria;
};



class ArvoreBinaria{
    public:
        ArvoreBinaria();
        ~ArvoreBinaria();

        void Insere(TipoItem item);
        void Caminha(int tipo);
        void Limpa();

    private:
        void InsereRecursivo(TipoNo* &p, TipoItem item);
        void ApagaRecursivo(TipoNo* p);
        void PorNivel();
        void PreOrdem(TipoNo* p);
        void InOrdem(TipoNo* p);
        void PosOrdem(TipoNo* p);

        TipoNo *raiz;
};

class HeapBinario{
    public:
        HeapBinario(int maxtam);
        void Insere(int x);
        int Remover();
    private:
        int GetAncestral(int i);
        int GetSucessorEsq(int i);
        int GetSucessorDir(int i);
        int tamanho;
        int v[];
};


class Matriz{
    public:
        Matriz(int linhas, int colunas, int LeTeclado);
        ~Matriz();

        double Get(int linha, int coluna);
        void Set(int linha, int coluna, double valor);
        void Imprime();
        static Matriz Soma(Matriz A, Matriz B);
        static double* Produto(Matriz A, double* v, int n);
    private:
    double** M;
    int l, c;
    void LeMatriz();
};

class MatrizCOO{
    public:
        MatrizCOO(int linhas, int colunas, int leTeclado);
        ~MatrizCOO();

        double Get(int linha, int coluna);
        void Set(int linha, int coluna, double valor);
        void Imprime();
        static MatrizCOO Soma(MatrizCOO A, MatrizCOO B);
        static double* Produto(MatrizCC A, MatrizCOO B);
        double** GetArranjoTamanhoN(int n);
        void InsereElemento(int l, int c, int v);
    private:
        double** M;
        int tamanho, tamanhoMAX, l, c;
        void LeMatriz();
};

class MatrizCSR{
    public:
        MatrizCSR(int linhas, int colunas, int leTeclado);
        ~MatrizCSR();
        double Get(int linhas, int colunas);
        void Set(int linhas, int colunas, double valor);
        void Imprime();

    private:
    int* linhas;
    int* colunas;
    double* valores;
    int tamanho, tamanhoMAX, l, c;
};