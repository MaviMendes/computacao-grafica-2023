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
    vector<Vertice *> vertices = this->corpo.vertices;
    // desenha corpo
    glBegin(GL_QUADS);
    glColor3f(this->corpo.cor[0], this->corpo.cor[1], this->corpo.cor[2]);
    for (int i = 0; i < this->corpo.vertices.size(); i++)
    {
        glVertex2f(vertices[i]->x, vertices[i]->y);
    }
    glEnd();

    // desenha perna_direita
    vertices = this->perna_direita.vertices;
    glBegin(GL_QUADS);
    glColor3f(perna_direita.cor[0], perna_direita.cor[1], perna_direita.cor[2]);
    for (int i = 0; i < this->perna_direita.vertices.size(); i++)
    {
        glVertex2f(vertices[i]->x, vertices[i]->y);
    }
    glEnd();

    vertices = this->perna_esquerda.vertices;
    glPushMatrix(); // [2]
    glTranslated((vertices[2]->x), (vertices[2]->y), 0);
    glRotated(this->angulo_perna, 0, 0, 1);
    glTranslated(-(vertices[2]->x), -(vertices[2]->y), 0);
    //  desenha perna_esquerda
    glBegin(GL_QUADS);
    glColor3f(this->perna_esquerda.cor[0], this->perna_esquerda.cor[1], this->perna_esquerda.cor[2]);
    for (int i = 0; i < this->perna_esquerda.vertices.size(); i++)
    {
        cout << vertices[i]->x << vertices[i]->y << endl;
        glVertex2f(vertices[i]->x, vertices[i]->y);
    }
    glEnd();
    glPopMatrix();

    // desenha braco_direito
    vertices = this->braco_direito.vertices;
    glBegin(GL_QUADS);
    glColor3f(this->braco_direito.cor[0], this->braco_direito.cor[1], this->braco_direito.cor[2]);
    for (int i = 0; i < this->braco_direito.vertices.size(); i++)
    {
        glVertex2f(vertices[i]->x, vertices[i]->y);
    }
    glEnd();

    // desenha braco_esquerdo
    glBegin(GL_QUADS);
    glColor3f(this->braco_esquerdo.cor[0], this->braco_esquerdo.cor[1], this->braco_esquerdo.cor[2]);
    vertices = this->braco_esquerdo.vertices;
    for (int i = 0; i < this->braco_esquerdo.vertices.size(); i++)
    {
        glVertex2f(vertices[i]->x, vertices[i]->y);
    }
    glEnd();

    // desenha cabeça
    glBegin(GL_TRIANGLES);
    glColor3f(this->cabeca.cor[0], this->cabeca.cor[1], this->cabeca.cor[2]);
    vertices = this->cabeca.vertices;
    for (int j = 0; j < this->cabeca.vertices.size(); j++)
    {
        glVertex2f(vertices[j]->x, vertices[j]->y);
    }
    glEnd();
    vertices.clear();
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
    glEnd();
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
    if (passos == 0)
    {
        entrarPosicaoAndar();
        passos += 1;
        return;
    }
    else if (boneco_andou_tudo == false)
    {
        glPushMatrix();
        corpo.transladar(1.3, 0.0);
        cabeca.transladar(1.3, 0.0);
        braco_direito.transladar(1.3, 0.0);
        braco_esquerdo.transladar(1.3, 0.0);

        // se o pé atual for vermelho/esquerdo
        perna_direita.reflexaoEmY(-1);
        perna_direita.transladar(-1.7, 0.0);

        perna_esquerda.reflexaoEmY(-1);
        perna_esquerda.transladar(-1.7, 0.0);

        glPopMatrix();
        glFlush();
        passos++;
        if (passos == 2)
            boneco_andou_tudo = true;
    }
}

void Personagem::girarPernaDireita(float angulo)
{
    angulo_perna += angulo;
}

void Personagem::chutarBola()
{
}
