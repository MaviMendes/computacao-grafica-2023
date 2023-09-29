#ifndef OBJETO_H
#define OBJETO_H

#include "Vertice.h"
#include "libs.h"
#include <vector>

using namespace std;

class Objeto {
    public:
        vector<Vertice*> vertices;
        Vertice posicao;
        float cor[3];

        Objeto();
        Objeto(vector<Vertice*> vertices);
        Objeto(vector<Vertice*> vertices, float cor[3]);

        void cisalhamentoEmY(float shY);
        void cisalhamentoEmX(float shX);
        void transladar(float x, float y);
        void rotacionar(float angulo);
        void reflexaoEmX(float escala);
        void reflexaoEmY(float escala);
};

#endif