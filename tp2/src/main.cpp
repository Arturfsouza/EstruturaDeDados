#include <iostream>
#include "../include/heap.hpp"
using namespace std;

int main() {
    cout << "Digite o tamanho maximo do heap: " << endl;
    int n;
    cin >> n;
    Heap heap(n);
    int x;
    cout << "Digite os numeros que irao entrar na heap: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> x;
        heap.Inserir(x);
    }
    while (!heap.Vazio()) {
        cout << heap.Remover() << " ";
    }
    cout << endl;
    return 0;
}