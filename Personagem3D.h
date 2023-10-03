#ifndef PERSONAGEM3D_H
#define PERSONAGEM3D_H

#include "libs.h"
#include "Objeto.h"

using namespace std;

class Personagem3D
{
public:
    Objeto cabeca;
    Objeto corpo;
    Objeto braco_direito;
    Objeto braco_esquerdo;
    Objeto perna_direita;
    Objeto perna_esquerda;
    vector<Objeto*> membros;
    Personagem3D();
    Personagem3D(vector<Objeto*> membros);
    Personagem3D(Objeto cabeca, Objeto corpo, Objeto braco_direito, Objeto braco_esquerdo,
               Objeto perna_direita, Objeto perna_esquerda);
    void andar();
    void desenharPersonagem();
    void chutarBola();
private:
    Vertice posicao_atual;
    int pe_frontal = 2; //0 -> vermelho/esquerdo, 1 -> verde/direito, 2 -> inicial
    void entrarPosicaoAndar();
    void desenharMembro(Objeto membro);
};

#endif