#include "libs.h"
#include "Vertice.h"
#include "Objeto.h"
#include "Personagem.h"

GLfloat ang = 60.0, angulo=30.0;
using namespace std;

Personagem *personagem;


void desenha_esfera() {
    // Posição inicial da esfera
    GLfloat x = 0.5f;
    GLfloat y = 0.2f;
    GLfloat z = 0.0f;

    // Raio da esfera (pode ser menor)
    GLfloat raio = 0.2f;

    // Número de slices e stacks para a esfera
    GLint slices = 50;
    GLint stacks = 50;

    // Cor da esfera
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul

    // Desenha a esfera na posição desejada
    glPushMatrix();
    glTranslatef(x, y, z);

    glutSolidSphere(raio, slices, stacks);

    glPopMatrix();
}


void desenha_gol(){

    // Posição da base da bola (mesma altura da base do boneco)
    GLfloat posY = 0.0f;

    // Posição X do quadrado
    GLfloat posX = 4.2f;

    // Tamanho do quadrado
    GLfloat tamanho = 1.5f; // Pode ser ajustado conforme necessário


    // Cor do contorno (preto)
    glColor3f(0.0f, 0.0f, 0.0f);

    // Desenhar o contorno do quadrado (linhas)
    glBegin(GL_LINE_LOOP);
    glVertex3f(posX - tamanho / 2.0f, posY, 0.0f); // Vértice inferior esquerdo
    glVertex3f(posX + tamanho / 2.0f, posY, 0.0f);  // Vértice inferior direito
    glVertex3f(posX + tamanho / 2.0f, posY + tamanho, 0.0f);  // Vértice superior direito
    glVertex3f(posX - tamanho / 2.0f, posY + tamanho, 0.0f); // Vértice superior esquerdo
    glEnd();
}



void desenha(void){
    // limpar buffers
    // define a viewport - tudo que desenha fica dentro da viewport
    glViewport(0, 0, 800,800);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
	//glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
	//glLoadIdentity();
    // Define uma projeção perspectiva 2D
   
   
    // Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // ao desenhar os vértices, especificar no sentido anti-horário
    // 1- desenha boneco 2d
    personagem->desenharPersonagem();
    //desenha_boneco();
    // 2- desenha bola 3d
    // Desenhar a esfera
    //glPushMatrix(); // Salva a matriz atual
    //glTranslatef(0.5f, 0.2f, 0.0f); // Translada para a posição da esfera (altura da base da perna do boneco)
    desenha_esfera();
    //glPopMatrix(); // Restaura a matriz anterior

    // 3 - desenha "gol"
    desenha_gol();
    // 4- movimento boneco ate certo ponto e chute - https://www.youtube.com/watch?v=NT-0Q2Psp2Y&list=PLWzp0Bbyy_3jy34HlDrEWlcG3rF99gkvk&index=4
    //movimento_boneco();
    
    // 5- trajetoria da bola em uma curva e ela gira em torno do proprio centro (colocar menos faces na bola pra dar pra ver ela girando)
    // quando 1 a 5 funcionar, adicionar o controle por teclado
    
    // executa os comandos opengl
    glFlush();
    glutSwapBuffers();

}

void inicializa(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    // tamanho da janela de visualização - ortho2d é a janela da camera
    //gluOrtho2D(0.0, 400.0, 0.0, 400.0);// 0 a 500 em x e em y
    // window da câmera
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    personagem = new Personagem();
    
	
}

void ControleTeclado(unsigned char key, int x, int y) { 

    switch (key) {
        case 'C':
        case 'c': 
            personagem->andar();
        break;
    }
    glutPostRedisplay();
}


void Timer(int value) {
    if (angulo < ang) {
        // Aumenta gradualmente o ângulo da perna direita
        angulo += 1.0; // Você pode ajustar a velocidade da animação aqui

        // Redesenha o boneco com a nova posição da perna direita
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, Timer, value);
    } else {
        glutPostRedisplay();
    }
}

int main(int argc, char **argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(1000, 1000);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Teste");

    glutKeyboardFunc(ControleTeclado); // Define qual funcao gerencia o comportamento do teclado

    // define a função Timer
    glutTimerFunc(1000 / 60, Timer, 0);

    //call back function - depois de criar a janela - display vai pertencer a essa janela
    glutDisplayFunc(desenha);
    inicializa();
    // Depois de fazer tudo, chama essa função para fechar tudo
    glutMainLoop();
}