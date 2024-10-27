#include "Set.hpp"

// Construtor: Inicializa a tabela hash com um determinado tamanho
StringSet::StringSet(int tamanho) {
    tamanhoOriginal = tamanho;
    tamanhoTabela = tamanho;
    tamanhoConjunto = 0;
    tabela = new ElementoTabela[tamanhoTabela];
    for (int i = 0; i < tamanhoTabela; i++) {
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }
}

// Destrutor: Limpa a memória alocada
StringSet::~StringSet() {
    delete[] tabela;
}

// Função Hash: Converte uma string em um índice da tabela
int StringSet::Hash(string s) {
    unsigned long hash = 5381;
    for (char c : s) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tamanhoTabela;
}

// Função Inserir: Insere uma string no conjunto
void StringSet::Inserir(string s) {
    if (tamanhoConjunto >= tamanhoTabela / 2) {
        Resize(tamanhoTabela * 2);  // Redimensiona a tabela se necessário
    }
    
    int pos = Hash(s);
    while (!tabela[pos].vazio && !tabela[pos].retirada) {
        if (tabela[pos].dado == s) {
            return;  // String já está no conjunto, não inserir novamente
        }
        pos = (pos + 1) % tamanhoTabela;  // Rehash linear
    }

    tabela[pos].dado = s;
    tabela[pos].vazio = false;
    tabela[pos].retirada = false;
    tamanhoConjunto++;
}

// Função Remover: Remove uma string do conjunto
void StringSet::Remover(string s) {
    int pos = Hash(s);
    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada && tabela[pos].dado == s) {
            tabela[pos].retirada = true;
            tamanhoConjunto--;
            return;
        }
        pos = (pos + 1) % tamanhoTabela;
    }
}

// Função Pertence: Verifica se uma string pertence ao conjunto
bool StringSet::Pertence(string s) {
    int pos = Hash(s);
    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada && tabela[pos].dado == s) {
            return true;
        }
        pos = (pos + 1) % tamanhoTabela;
    }
    return false;
}

// Função Rehash: Redimensiona a tabela quando necessário
void StringSet::Rehash(int novoTamanho) {
    ElementoTabela* novaTabela = new ElementoTabela[novoTamanho];
    for (int i = 0; i < novoTamanho; i++) {
        novaTabela[i].vazio = true;
        novaTabela[i].retirada = false;
    }

    int velhoTamanho = tamanhoTabela;
    ElementoTabela* velhaTabela = tabela;
    tabela = novaTabela;
    tamanhoTabela = novoTamanho;
    tamanhoConjunto = 0;

    for (int i = 0; i < velhoTamanho; i++) {
        if (!velhaTabela[i].vazio && !velhaTabela[i].retirada) {
            Inserir(velhaTabela[i].dado);
        }
    }

    delete[] velhaTabela;
}

// Função Resize: Aumenta o tamanho da tabela e faz rehash
void StringSet::Resize(size_t novoTamanho) {
    Rehash(novoTamanho);
}

// Função Imprimir: Imprime todos os elementos do conjunto
void StringSet::Imprimir() {
    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            cout << tabela[i].dado << " ";
        }
    }
    cout << endl;
}

// Função Intersecao: Retorna um novo conjunto com a interseção de dois conjuntos
StringSet* StringSet::Intersecao(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoTabela);
    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio && !tabela[i].retirada && S->Pertence(tabela[i].dado)) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    return resultado;
}

// Função Uniao: Retorna um novo conjunto com a união de dois conjuntos
StringSet* StringSet::Uniao(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoTabela + S->tamanhoTabela);
    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado;
}

// Função DiferencaSimetrica: Retorna um novo conjunto com a diferença simétrica de dois conjuntos
StringSet* StringSet::DiferencaSimetrica(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoTabela + S->tamanhoTabela);
    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio && !tabela[i].retirada && !S->Pertence(tabela[i].dado)) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada && !Pertence(S->tabela[i].dado)) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado;
}
