#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "ListaAdjacencia.hpp"
#include <iostream>

/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Nenhuma outra alteração neste arquivo é permitida
 */


class Grafo{
    public:
        Grafo();
        ~Grafo();

        void InsereVertice();
        void InsereAresta(int v, int w);

        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();

        void ImprimeVizinhos(int v);
        bool Completo();
    private:
        
        /*  Você deve implementar ListaAdjacencia como um TAD que irá armazenar
         * os dados do grafo. Lembrando que este TAD deve ser uma lista 
         * encadeada
         */
        ListaAdjacencia vertices;
};

#endif