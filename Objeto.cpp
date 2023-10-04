#include "Objeto.h"

Objeto::Objeto()
{
}

Objeto::Objeto(vector<Vertice *> vertices)
{
    this->vertices = vertices;
}

Objeto::Objeto(vector<Vertice *> vertices, float cor[3])
{
    this->cor[0] = cor[0];
    this->cor[1] = cor[1];
    this->cor[2] = cor[2];
    this->vertices = vertices;
}

Objeto::Objeto(vector<Vertice *> vertices, vector<Vertice *> normais, float cor[3])
{
    this->cor[0] = cor[0];
    this->cor[1] = cor[1];
    this->cor[2] = cor[2];
    this->vertices = vertices;
    this->normais = normais;
}

void Objeto::cisalhamentoEmY(float shY)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        this->vertices[i]->y += shY * vertices[i]->x;
    }
}

void Objeto::cisalhamentoEmX(float shx)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        this->vertices[i]->x += shx * vertices[i]->y;
    }
}

void Objeto::transladar(float x, float y)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        this->vertices[i]->x += x;
        this->vertices[i]->y += y;
    }
}

void Objeto::rotacionar(float angulo)
{
    for (int i = 0; i < vertices.size(); i++) {
        float x = vertices[i]->x;
        float y = vertices[i]->y;
        this->vertices[i]->x = x * cos(angulo) - y * sin(angulo);
        this->vertices[i]->y = x * sin(angulo) - y * cos(angulo);
    }
}


void Objeto::reflexaoEmX(float escala)
{
    for (int i = 0; i < vertices.size(); i++) {
        this->vertices[i]->y *= escala;
    }
}

void Objeto::reflexaoEmY(float escala)
{
    for (int i = 0; i < vertices.size(); i++) {
        this->vertices[i]->x *= escala;
    }
}
