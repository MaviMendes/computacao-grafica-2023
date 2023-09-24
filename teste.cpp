#include <GL/glut.h>
#include <iostream>
#include <math.h>

void desenha_boneco() {
    int x = -2;

    // CORPO COM BRAÇOS
    glBegin(GL_QUADS);
    // define os vértices do quadrilátero BRAÇO ESQ
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(2.0 + x, 1.0 + x);
    glVertex2f(1.5 + x, 1.5 + x);
    glVertex2f(1.2 + x, 1.5 + x);
    glVertex2f(1.7 + x, 1.0 + x);
    glEnd();

    glBegin(GL_QUADS);
    // define os vértices do quadrilátero BRAÇO DIR
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.0 + x, 1.0 + x);
    glVertex2f(0.3 + x, 1.0 + x);
    glVertex2f(0.8 + x, 1.5 + x);
    glVertex2f(0.5 + x, 1.5 + x);
    glEnd();

    glBegin(GL_QUADS);
    // define os vértices do quadrilátero CORPO
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5 + x, 0.5 + x);
    glVertex2f(1.5 + x, 0.5 + x);
    glVertex2f(1.5 + x, 1.5 + x);
    glVertex2f(0.5 + x, 1.5 + x);
    glEnd();

    glBegin(GL_QUADS);
    // define os vértices do quadrilátero PERNA DIR
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.5 + x, 0.0 + x);
    glVertex2f(0.8 + x, 0.0 + x);
    glVertex2f(0.8 + x, 0.5 + x);
    glVertex2f(0.5 + x, 0.5 + x);
    glEnd();

    glBegin(GL_QUADS);
    // define os vértices do quadrilátero PERNA ESQ
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(1.2 + x, 0.0 + x);
    glVertex2f(1.5 + x, 0.0 + x);
    glVertex2f(1.5 + x, 0.5 + x);
    glVertex2f(1.2 + x, 0.5 + x);
    glEnd();

    glBegin(GL_TRIANGLES);
    // define os vértices do triângulo CABEÇA
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.75 + x, 1.5 + x);
    glVertex2f(1.25 + x, 1.5 + x);
    glVertex2f(1.0 + x, 2.0 + x);
    glEnd();
}

void desenha_esfera() {

    // Raio da esfera (pode ser menor)
    GLfloat raio = 0.2f;

    // Número de slices e stacks para a esfera
    GLint slices = 50;
    GLint stacks = 50;

    // Cor da esfera
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul

    // Desenha a esfera
    glutSolidSphere(raio, slices, stacks);
}

void desenha_gol(){

    // Posição da base da bola (mesma altura da base do boneco)
    GLfloat posY = -2.0f;

    // Tamanho do quadrado
    GLfloat tamanho = 1.0f; // Pode ser ajustado conforme necessário

    // Posição X do quadrado
    GLfloat posX = 2.0f;

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
   
    // Especifica sistema de coordenadas do modelo
	//glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    // ao desenhar os vértices, especificar no sentido anti-horário
    // 1- desenha boneco 2d
    desenha_boneco();
    
    // 2- desenha bola 3d
    // Desenhar a esfera
    glPushMatrix(); // Salva a matriz atual
    glTranslatef(0.05f, -1.8f, 0.0f); // Translada para a posição da esfera (altura da base da perna do boneco)
    desenha_esfera();
    glPopMatrix(); // Restaura a matriz anterior

    // 3 - desenha "gol"
    desenha_gol();
    // 4- movimento boneco ate certo ponto e chute - https://www.youtube.com/watch?v=NT-0Q2Psp2Y&list=PLWzp0Bbyy_3jy34HlDrEWlcG3rF99gkvk&index=4
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
    gluOrtho2D(-2.5, 2.5, -2.5, 2.5);
	
}

int main(int argc, char **argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(1000, 1000);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Teste");

    //call back function - depois de criar a janela - display vai pertencer a essa janela
    glutDisplayFunc(desenha);
    inicializa();
    // Depois de fazer tudo, chama essa função para fechar tudo
    glutMainLoop();
}
