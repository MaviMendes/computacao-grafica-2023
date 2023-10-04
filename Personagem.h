#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "libs.h"
#include "Objeto.h"

using namespace std;

class Personagem
{
public:
    Objeto cabeca;
    Objeto corpo;
    Objeto braco_direito;
    Objeto braco_esquerdo;
    Objeto perna_direita;
    Objeto perna_esquerda;
    vector<Objeto*> membros;
    bool boneco_andou_tudo = false;
    GLfloat ang = 60.0;
    GLfloat angulo=30.0;
    GLfloat angulo_perna=0.0;
    Personagem();
    Personagem(vector<Objeto*> membros);
    Personagem(Objeto cabeca, Objeto corpo, Objeto braco_direito, Objeto braco_esquerdo,
               Objeto perna_direita, Objeto perna_esquerda);
    void andar();
    void desenharPersonagem();
    void girarPernaDireita(float angulo);
    void chutarBola();
private:
    int passos = 0;
    void entrarPosicaoAndar();
    void desenharMembro(Objeto membro);
};

#endif