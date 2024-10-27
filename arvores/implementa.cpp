#include <iostream>
#include "arvore.hpp"


TipoNo::TipoNo(){
    item.SetChave(-1);
    esq=NULL;
    dir=NULL;
}

ArvoreBinaria::ArvoreBinaria(){
    raiz = NULL;
}

ArvoreBinaria::~ArvoreBinaria(){
    Limpa();
}

void ArvoreBinaria::Insere(TipoItem item){
    InsereRecursivo(raiz, item);
}

void ArvoreBinaria::InsereRecursivo(TipoNo* &p, TipoItem item){
    if(p == NULL){
        p = new TipoNo();
        p ->item = item;
    }
    else{
        if(item.GetChave() < p->item.GetChave()){
            InsereRecursivo(p->esq, item);
        }
        else
            InsereRecursivo(p->dir, item);
    }
}

void ArvoreBinaria::PreOrdem(TipoNo *p){
    if (p != NULL){
        p->item.Imprime();
        PreOrdem(p->esq);
        PreOrdem(p->dir);
    }
}

void ArvoreBinaria::InOrdem(TipoNo *p){
    if (p != NULL){
        InOrdem(p->esq);
        p->item.Imprime();
        InOrdem(p->dir);
    }
}

void ArvoreBinaria::PosOrdem(TipoNo *p){
    if (p!= NULL){
        PosOrdem(p->esq);
        PosOrdem(p->dir);
        p->item.Imprime();
    }
}

void ArvoreBinaria::CaminhaNive(){
    FilaArranjo F;
    TipoNo *p;

    F.Enfileira(raiz);
    while(!F.Vazia()){
        p = F.Desenfileira();
        if (p!=NULL){
            p->Item.Imprime();
            F.Enfileira (p->esq);
            F.Enfileira(p->dir);
        }
    }
}

void ArvoreBinaria::Limpa(){
    ApagaRecursivo(raiz);
    raiz=NULL;
}

void ArvoreBinaria::ApagaRecursivo(TipoNo *p){
    if (p!=NULL){
        ApagaRecursivo(p->esq);
        ApagaRecursivo(p->dir);
        delete p;
    }
}

HeapBinario::HeapBinario(int maxtam){
    int v[maxtam +1];
    tamanho = 0;
}

int HeapBinario::GetAncestral(int i){
    return (i-1)/2;
}

int HeapBinario::GetSucessorEsq(int i){
    return 2*i +1;
}

int HeapBinario::GetSucessorDir(int i){
    return 2*i +2;
}

void HeapBinario::Insere(int x){
    v[tamanho] = x;
    int i = tamanho;
    int p = (i - 1)/2;
    while(v[i]>v[p]){
        std::swap(v[i], v[p]);
        i =p;
        p = (i-1)/2;
    }
}

int HeapBinario::Remover(){
    int x = v[0];
    v[0]= v[tamanho-1];
    tamanho = tamanho -1;
    int i = 0;
    int s;
    if(GetSucessorDir(v[i])>GetSucessorEsq(v[i])){
        s =  GetSucessorDir(v[i]);
    }
    if(GetSucessorEsq(v[i])>GetSucessorDir(v[i])){
        s = GetSucessorEsq(v[i]);
    }
    while(v[i]<v[s]){
        std::swap(v[i],v[s]);
        i = s;
        if(GetSucessorDir(v[i])>GetSucessorEsq(v[i])){
        s =  GetSucessorDir(v[i]);
        }
        if(GetSucessorEsq(v[i])>GetSucessorDir(v[i])){
        s = GetSucessorEsq(v[i]);
        }
    }
    return x;
}

Matriz::Matriz(int linhas, int colunas, int LeTeclado){
    l = linhas,
    c = colunas,
    M = new double*[l];
    if(!LeTeclado){
        for(int i = 0; i < l; i++){
            M[i] = new double [c];
            for (int j =0; j<c; j++){
                M[i][j] = 0;
            }
        }
    }
    else{
        LeMatriz();
    }
}

void Matriz::LeMatriz(){
    for(int i = 0; i<l; i++){
        M[i]= new double [c];
        for (int j = 0;j<c;j++){
            std::cin>>M[i][j];
        }
    }
}

Matriz::~Matriz(){
    for(int i = 0; i <l; i++){
        delete[](M[i]);
    }
    delete[](M);
}

double Matriz::Get(int linha, int coluna){
    if(linha<0 || linha >= l || coluna <0 || coluna  >= c){
        throw "Posicao Invalida!\n";
    }
    return M[linha][coluna];
}

void Matriz::Set(int linha, int coluna, double valor){
    if (linha<0 || linha >=l || coluna<0||coluna>=c){
        throw "Posicao invalida\n";
    }
    M[linha][coluna] = valor;
}

void Matriz::Imprime(){
    for(int i = 0; i <l;i++){
        for(int j =0; j<c;j++){
            std::cout<<M[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

double* Matriz::Produto(Matriz A, double* v, int n){
    if(A.c != n){
        throw "Dimensoes Incompativeis\n";
    }
    double* s = new double[n];
    for (int i=0;i<n;i++){
        s[i] = 0;
    }
    for(int i =0; i<n;i++){
        for(int j = 0; j<c;j++){
            s[i] += A.M[i][j]*v[j];
        }
    }
    return s;
}

Matriz Matriz::Soma(Matriz A, Matriz B){
    if(A.l != B.l||A.c != B.c){
        throw "Medidas Incompativeis\n";
    }
    Matriz C = Matriz(A.l,A.c,0);
    for(int i = 0; i<A.l;i++){
        for(int j = 0 ; j <c;j++){
            C.Set(i,j, A.M[i][j]+B.M[i][j]);
        }
    }
    return C;
}

double** MatrizCOO::GetArranjoTamanhoN(int n){
    double** arranjo = new double*[n];
    for (int i = 0; i<n;i++){
        arranjo[i] = new double[3];
        for (int j =0;j<c;j++){
            arranjo[i][j]=0.0;
        }
    }
    return arranjo;
}
