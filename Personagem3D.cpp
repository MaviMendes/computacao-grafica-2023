#include "Personagem.h"
#include "Objeto.h"
using namespace std;

float cor_perna_direita[3] = {0.0, 1.0, 0.0};
vector<Vertice *> vertices_perna_direita = {
    new Vertice(0.00, -4.00, -0.50),
    new Vertice(0.00, -7.00, -0.50),
    new Vertice(1.00, -4.00, -0.50),
    new Vertice(1.00, -7.00, -0.50),
    new Vertice(0.00, -4.00, 0.50),
    new Vertice(0.00, -7.00, 0.50),
    new Vertice(1.00, -4.00, 0.50),
    new Vertice(1.00, -7.00, 0.50),
};
vector<Vertice *> normais_perna_direita = {
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
    new Vertice(0.00, 0.00, 1.00),
    new Vertice(0.00, -1.00, 0.00),
    new Vertice(0.00, 0.00, -1.00),
    new Vertice(-1.00, 0.00, 0.00),
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
};

float cor_perna_esquerda[3] = {1.0, 0.0, 0.0};
vector<Vertice *> vertices_perna_esquerda = {
    new Vertice(-1.00, -4.00, -0.50),
    new Vertice(-1.00, -7.00, -0.50),
    new Vertice(0.00, -4.00, -0.50),
    new Vertice(0.00, -7.00, -0.50),
    new Vertice(-1.00, -4.00, 0.50),
    new Vertice(-1.00, -7.00, 0.50),
    new Vertice(0.00, -4.00, 0.50),
    new Vertice(0.00, -7.00, 0.50),
};
vector<Vertice *> normais_perna_esquerda = {
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
    new Vertice(0.00, 0.00, 1.00),
    new Vertice(0.00, -1.00, 0.00),
    new Vertice(0.00, 0.00, -1.00),
    new Vertice(-1.00, 0.00, 0.00),
};

float cor_braco_esquerdo[3] = {0.0, 0.0, 0.0};
vector<Vertice *> vertices_braco_esquerdo = {
    new Vertice(-2.00, -1.00, -0.50),
    new Vertice(-2.00, -4.00, -0.50),
    new Vertice(-1.00, -1.00, -0.50),
    new Vertice(-1.00, -4.00, -0.50),
    new Vertice(-2.00, -1.00, 0.50),
    new Vertice(-2.00, -4.00, 0.50),
    new Vertice(-1.00, -1.00, 0.50),
    new Vertice(-1.00, -4.00, 0.50),
};
vector<Vertice *> normais_braco_esquerdo = {
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
    new Vertice(0.00, 0.00, 1.00),
    new Vertice(0.00, -1.00, 0.00),
    new Vertice(0.00, 0.00, -1.00),
    new Vertice(-1.00, 0.00, 0.00),
};

float cor_braco_direito[3] = {0.0, 0.0, 0.0};
vector<Vertice *> vertices_braco_direito = {
    new Vertice(1.00, -1.00, -0.50),
    new Vertice(1.00, -4.00, -0.50),
    new Vertice(2.00, -1.00, -0.50),
    new Vertice(2.00, -4.00, -0.50),
    new Vertice(1.00, -1.00, 0.50),
    new Vertice(1.00, -4.00, 0.50),
    new Vertice(2.00, -1.00, 0.50),
    new Vertice(2.00, -4.00, 0.50),
};
vector<Vertice *> normais_braco_direito = {
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
    new Vertice(0.00, 0.00, 1.00),
    new Vertice(0.00, -1.00, 0.00),
    new Vertice(0.00, 0.00, -1.00),
    new Vertice(-1.00, 0.00, 0.00),
};

float cor_corpo[3] = {0.0, 0.0, 1.0};
vector<Vertice *> vertices_corpo = {
    new Vertice(-1.00, -1.00, -0.50),
    new Vertice(-1.00, -4.00, -0.50),
    new Vertice(1.00, -1.00, -0.50),
    new Vertice(1.00, -4.00, -0.50),
    new Vertice(-1.00, -1.00, 0.50),
    new Vertice(-1.00, -4.00, 0.50),
    new Vertice(1.00, -1.00, 0.50),
    new Vertice(1.00, -4.00, 0.50),
};
vector<Vertice *> normais_corpo = {
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
    new Vertice(0.00, 0.00, 1.00),
    new Vertice(0.00, -1.00, 0.00),
    new Vertice(0.00, 0.00, -1.00),
    new Vertice(-1.00, 0.00, 0.00),
};

float cor_cabeca[3] = {0.0, 0.0, 0.0};
vector<Vertice *> vertices_cabeca = {
    new Vertice(1.00, 1.00, -1.00),
    new Vertice(1.00, -1.00, -1.00),
    new Vertice(1.00, 1.00, 1.00),
    new Vertice(1.00, -1.00, 1.00),
    new Vertice(-1.00, 1.00, -1.00),
    new Vertice(-1.00, -1.00, -1.00),
    new Vertice(-1.00, 1.00, 1.00),
    new Vertice(-1.00, -1.00, 1.00),
};
vector<Vertice *> normais_cabeca = {
    new Vertice(0.00, 1.00, 0.00),
    new Vertice(0.00, -0.00, 1.00),
    new Vertice(-1.00, 0.00, 0.00),
    new Vertice(0.00, -1.00, 0.00),
    new Vertice(1.00, 0.00, 0.00),
    new Vertice(0.00, 0.00, -1.00),
};

Personagem3D::Personagem3D()
{
    this->cabeca = Objeto(vertices_cabeca, normais_cabeca, cor_cabeca);
    this->corpo = Objeto(vertices_corpo, normais_corpo, cor_corpo);
    this->braco_direito = Objeto(vertices_braco_direito, normais_braco_direito, cor_braco_direito);
    this->braco_esquerdo = Objeto(vertices_braco_esquerdo, normais_braco_esquerdo, cor_braco_esquerdo);
    this->perna_direita = Objeto(vertices_perna_direita, normais_perna_direita, cor_perna_direita);
    this->perna_esquerda = Objeto(vertices_perna_esquerda, normais_perna_esquerda, cor_perna_esquerda);
    this->membros = vector<Objeto *>{&corpo, &braco_direito, &braco_esquerdo, &perna_direita, &perna_esquerda, &cabeca};
}

Personagem3D::Personagem3D(vector<Objeto *> membros)
{
    this->corpo = *membros[0];
    this->braco_direito = *membros[1];
    this->braco_esquerdo = *membros[2];
    this->perna_direita = *membros[3];
    this->perna_esquerda = *membros[4];
    this->cabeca = *membros[5];
    this->membros = membros;
}

Personagem3D::Personagem3D(Objeto cabeca, Objeto corpo, Objeto braco_direito, Objeto braco_esquerdo, Objeto perna_direita, Objeto perna_esquerda)
{
    this->cabeca = cabeca;
    this->corpo = corpo;
    this->braco_direito = braco_direito;
    this->braco_esquerdo = braco_esquerdo;
    this->perna_direita = perna_direita;
    this->perna_esquerda = perna_esquerda;
    this->membros = vector<Objeto *>{&corpo, &braco_direito, &braco_esquerdo, &perna_direita, &perna_esquerda, &cabeca};
}

void Personagem3D::desenharPersonagem3D()
{
    // desenha membros do corpo
    for (int i = 0; i < this->membros.size() - 1; i++)
    {
        Objeto &objeto = *this->membros[i];
        vector<Vertice *> vertices = objeto.vertices;
        glBegin(GL_QUADS);
        glColor3f(objeto.cor[0], objeto.cor[1], objeto.cor[2]);

        for (int j = 0; j < vertices.size(); j++)
        {
            //if(j < objeto.normais.size())
                //glNormal3f(objeto.normais[j]->x, objeto.normais[j]->y, objeto.normais[j]->z);
            glVertex3f(vertices[j]->x, vertices[j]->y, vertices[j]->z);
        }

        glEnd();
        vertices.clear();
    }
}