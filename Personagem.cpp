#include "Personagem.h"
#include "Objeto.h"
using namespace std;

float cor_perna_direita[3] = {0.0, 1.0, 0.0};
vector<Vertice *> vertices_perna_direita = {
    new Vertice(-1.5, 0.0),
    new Vertice(-1.2, 0.0),
    new Vertice(-1.2, 0.5),
    new Vertice(-1.5, 0.5)};

float cor_perna_esquerda[3] = {1.0, 0.0, 0.0};
vector<Vertice *> vertices_perna_esquerda = {
    new Vertice(-1.9, 0.0),
    new Vertice(-1.6, 0.0),
    new Vertice(-1.6, 0.5),
    new Vertice(-1.9, 0.5)};

float cor_braco_esquerdo[3] = {0.0, 0.0, 0.0};
vector<Vertice *> vertices_braco_esquerdo = {
    new Vertice(-0.5, 1.0),
    new Vertice(-1.0, 1.5),
    new Vertice(-1.3, 1.5),
    new Vertice(-0.8, 1.0)};

float cor_braco_direito[3] = {0.0, 0.0, 0.0};
vector<Vertice *> vertices_braco_direito = {
    new Vertice(-2.5, 1.0),
    new Vertice(-2.2, 1.0),
    new Vertice(-1.7, 1.5),
    new Vertice(-2.0, 1.5)};

float cor_corpo[3] = {0.0, 0.0, 1.0};
vector<Vertice *> vertices_corpo = {
    new Vertice(-2.0, 0.5),
    new Vertice(-1.0, 0.5),
    new Vertice(-1.0, 1.5),
    new Vertice(-2.0, 1.5)};

float cor_cabeca[3] = {0.0, 0.0, 0.0};
vector<Vertice *> vertices_cabeca = {
    new Vertice(-1.75, 1.5),
    new Vertice(-1.25, 1.5),
    new Vertice(-1.5, 2.0)};

Personagem::Personagem()
{
    this->cabeca = Objeto(vertices_cabeca, cor_cabeca);
    this->corpo = Objeto(vertices_corpo, cor_corpo);
    this->braco_direito = Objeto(vertices_braco_direito, cor_braco_direito);
    this->braco_esquerdo = Objeto(vertices_braco_esquerdo, cor_braco_esquerdo);
    this->perna_direita = Objeto(vertices_perna_direita, cor_perna_direita);
    this->perna_esquerda = Objeto(vertices_perna_esquerda, cor_perna_esquerda);
    this->membros = vector<Objeto *>{&corpo, &braco_direito, &braco_esquerdo, &perna_direita, &perna_esquerda, &cabeca};
}

Personagem::Personagem(vector<Objeto *> membros)
{
    this->corpo = *membros[0];
    this->braco_direito = *membros[1];
    this->braco_esquerdo = *membros[2];
    this->perna_direita = *membros[3];
    this->perna_esquerda = *membros[4];
    this->cabeca = *membros[5];
    this->membros = membros;
}

Personagem::Personagem(Objeto cabeca, Objeto corpo, Objeto braco_direito, Objeto braco_esquerdo, Objeto perna_direita, Objeto perna_esquerda)
{
    this->cabeca = cabeca;
    this->corpo = corpo;
    this->braco_direito = braco_direito;
    this->braco_esquerdo = braco_esquerdo;
    this->perna_direita = perna_direita;
    this->perna_esquerda = perna_esquerda;
    this->membros = vector<Objeto *>{&corpo, &braco_direito, &braco_esquerdo, &perna_direita, &perna_esquerda, &cabeca};
}

void Personagem::desenharPersonagem()
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
            glVertex2f(vertices[j]->x, vertices[j]->y);
        }

        glEnd();
        vertices.clear();
    }

    // desenha cabeça
    glBegin(GL_TRIANGLES);
    glColor3f(this->cabeca.cor[0], this->cabeca.cor[1], this->cabeca.cor[2]);
    vector<Vertice *> vertices = this->cabeca.vertices;
    for (int j = 0; j < this->cabeca.vertices.size(); j++)
    {
        glVertex2f(vertices[j]->x, vertices[j]->y);
    }
    glEnd();
}

void Personagem::desenharMembro(Objeto membro)
{
    vector<Vertice *> vertices = membro.vertices;
    glBegin(GL_QUADS);
    glColor3f(membro.cor[0], membro.cor[1], membro.cor[2]);

    for (int j = 0; j < vertices.size(); j++)
    {
        glVertex2f(vertices[j]->x, vertices[j]->y);
    }
    vertices.clear();
    glutSwapBuffers();
}

// sai da posição inicial e inclina os dois pés pra parecer passos
void Personagem::entrarPosicaoAndar()
{
    float angulo = 30.0;
    glPushMatrix();
    perna_direita.transladar(0.1, 0.0);
    perna_direita.cisalhamentoEmX(-0.5);

    // perna_esquerda.transladar(0.2, 0.0);
    perna_esquerda.cisalhamentoEmX(0.5);
    glPopMatrix();
    glFlush();
}

void Personagem::andar()
{
    if (pe_frontal == 2)
    {
        entrarPosicaoAndar();
        pe_frontal = 1;
        return;
    }

    // alterna o pé frontal
    // 0 -> vermelho/esquerdo, 1 -> verde/direito, 2 -> inicial
    pe_frontal = pe_frontal == 0 ? 1 : 0;

    glPushMatrix();
    corpo.transladar(1.0, 0.0);
    cabeca.transladar(1.0, 0.0);
    braco_direito.transladar(1.0, 0.0);
    braco_esquerdo.transladar(1.0, 0.0);

    // se o pé atual for vermelho/esquerdo
    perna_direita.reflexaoEmY(-1);
    perna_direita.transladar(-2.0, 0.0);

    perna_esquerda.reflexaoEmY(-1);
    perna_esquerda.transladar(-2.0, 0.0);

    glPopMatrix();
    glFlush();
}

void Personagem::chutarBola()
{
}
