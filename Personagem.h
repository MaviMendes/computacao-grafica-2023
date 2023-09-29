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
    Personagem();
    Personagem(vector<Objeto*> membros);
    Personagem(Objeto cabeca, Objeto corpo, Objeto braco_direito, Objeto braco_esquerdo,
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