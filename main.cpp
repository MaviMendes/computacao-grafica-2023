#include "libs.h"
#include "Vertice.h"
#include "Objeto.h"
#include "Personagem.h"

GLfloat anguloMax = 20.0, anguloMin = 0.0;
using namespace std;

Personagem *personagem;

GLfloat x_esf = -0.7f, y_esf = 0.2f, z_esf = 0.0f;
GLfloat x_final_esf = 4.3f;
GLfloat x_med_esf = 2.25f;
GLfloat y_med_esf = 2.0;

bool boneco_virou_perna = false;

GLfloat bezier(GLfloat P0, GLfloat P1, GLfloat P2, GLfloat P3, GLfloat t)
{
    return pow(1 - t, 3) * P0 + 3 * t * pow(1 - t, 2) * P1 + 3 * pow(t, 2) * (1 - t) * P2 + pow(t, 3) * P3;
}

void moveSphereOnBezierCurve(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat t)
{
    // Define the control points for the Bezier curve
    GLfloat P0x = -0.7f, P0y = 0.2f, P0z = 0.0f; // Starting position of the sphere
    GLfloat P1x = 1.0f, P1y = 3.0f, P1z = 0.0f;  // Control point 1
    GLfloat P2x = 2.5f, P2y = 2.0f, P2z = 0.0f;  // Control point 2
    GLfloat P3x = 4.3f, P3y = 0.0f, P3z = 0.0f;  // Ending position of the sphere

    // Calculate the new position of the sphere along the Bezier curve
    x = bezier(P0x, P1x, P2x, P3x, t);
    y = bezier(P0y, P1y, P2y, P3y, t);
    z = bezier(P0z, P1z, P2z, P3z, t);
}

void desenha_esfera(GLfloat x, GLfloat y, GLfloat z)
{

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

void desenha_gol()
{

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
    glVertex3f(posX - tamanho / 2.0f, posY, 0.0f);           // Vértice inferior esquerdo
    glVertex3f(posX + tamanho / 2.0f, posY, 0.0f);           // Vértice inferior direito
    glVertex3f(posX + tamanho / 2.0f, posY + tamanho, 0.0f); // Vértice superior direito
    glVertex3f(posX - tamanho / 2.0f, posY + tamanho, 0.0f); // Vértice superior esquerdo
    glEnd();
}

void desenha(void)
{
    // limpar buffers
    // define a viewport - tudo que desenha fica dentro da viewport
    glViewport(0, 0, 800, 800);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
    // glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    // glLoadIdentity();
    // Define uma projeção perspectiva 2D

    // Especifica sistema de coordenadas do modelo
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // ao desenhar os vértices, especificar no sentido anti-horário
    // 1- desenha boneco 2d
    personagem->desenharPersonagem();
    // desenha_boneco();
    //  2- desenha bola 3d
    //  Desenhar a esfera
    // glPushMatrix(); // Salva a matriz atual
    // glTranslatef(0.5f, 0.2f, 0.0f); // Translada para a posição da esfera (altura da base da perna do boneco)
    desenha_esfera(x_esf, y_esf, z_esf);
    // glPopMatrix(); // Restaura a matriz anterior

    // 3 - desenha "gol"
    desenha_gol();
    // 4- movimento boneco ate certo ponto e chute - https://www.youtube.com/watch?v=NT-0Q2Psp2Y&list=PLWzp0Bbyy_3jy34HlDrEWlcG3rF99gkvk&index=4
    // movimento_boneco();

    // 5- trajetoria da bola em uma curva e ela gira em torno do proprio centro (colocar menos faces na bola pra dar pra ver ela girando)
    // quando 1 a 5 funcionar, adicionar o controle por teclado

    // executa os comandos opengl
    glFlush();
    glutSwapBuffers();
}

void inicializa(void)
{
    // Configuração de Iluminação
    GLfloat luzAmbiente[4] = {0.6, 0.6, 0.6, 1.0};
    // Capacidade de brilho do material
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0}; // define a cor do brilho no material, geralmente branco
    GLint expoenteEspecular = 50;                     // define o brilho do material. varia de 0-128. Mais espelhado ou menos espelhado.

    // Habilita o modelo de coloriza��o de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a reflet�ncia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentra��o do brilho
    glMateriali(GL_FRONT, GL_SHININESS, expoenteEspecular);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os par�metros da luz de n�mero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

    // Habilita a defini��o da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    // Habilita o uso de ilumina��o
    glEnable(GL_LIGHTING);
    // Habilita a luz de n�mero 0
    glEnable(GL_LIGHT0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    // tamanho da janela de visualização - ortho2d é a janela da camera
    // gluOrtho2D(0.0, 400.0, 0.0, 400.0);// 0 a 500 em x e em y
    // window da câmera
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    personagem = new Personagem();
}

void ControleTeclado(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'C':
    case 'c':
        personagem->andar();
        break;
    }
    glutPostRedisplay();
}

void Timer(int value)
{

    if (!boneco_virou_perna && personagem->boneco_andou_tudo)
    {
        if (anguloMin < anguloMax)
        {
            // Aumenta gradualmente o ângulo da perna direita
            anguloMin += 10.0; // Você pode ajustar a velocidade da animação aqui
            cout << anguloMin << endl;
            personagem->girarPernaDireita(anguloMin);
            // Redesenha o boneco com a nova posição da perna direita
            glutPostRedisplay();
            glutTimerFunc(1000 / 20, Timer, value + 1);
        }
        else
        {
            cout << boneco_virou_perna;
            cout << personagem->boneco_andou_tudo;
            boneco_virou_perna = true;
            // glutPostRedisplay();
        }
        // glutTimerFunc(1000 / 5, Timer, value+1);
    }
    if (boneco_virou_perna) // chuta
    {
        cout << personagem->boneco_andou_tudo;
        if (x_esf < x_med_esf && y_esf < y_med_esf)
        { // subindo
            x_esf += 0.2f;
            y_esf += 0.1f;
        }
        if (x_esf >= x_med_esf && x_esf < x_final_esf && y_esf > 0.3)
        {
            x_esf += 0.1f;
            y_esf -= 0.1f;
        }
        else
        {
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Timer, value + 1);
}

/**
 * void Timer(int value) {
    if (!boneco_andou_tudo){

        if (angulo < ang) {
            // Aumenta gradualmente o ângulo da perna direita
            angulo += 1.0; // Você pode ajustar a velocidade da animação aqui
            // Redesenha o boneco com a nova posição da perna direita
            glutPostRedisplay();
            glutTimerFunc(1000 / 60, Timer, value);

        } else{
            boneco_andou_tudo=true;

            glutPostRedisplay();
        }
    }
    if (boneco_andou_tudo){

        if(x_esf<x_med_esf && y_esf<y_med_esf){ //subindo
            x_esf+=0.2f;
            y_esf+=0.1f;
            glutPostRedisplay();
            glutTimerFunc(1000 / 20, Timer, value);
        }
        if(x_esf>=x_med_esf && x_esf<x_final_esf && y_esf>0.3){
            x_esf+=0.1f;
            y_esf-=0.1f;
            glutPostRedisplay();
            glutTimerFunc(1000 / 20, Timer, value);
        }
        else{
            glutPostRedisplay();
        }
    }
}
*/

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(1000, 1000);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Teste");

    glutKeyboardFunc(ControleTeclado); // Define qual funcao gerencia o comportamento do teclado

    // define a função Timer
    glutTimerFunc(1000 / 60, Timer, 1);

    // call back function - depois de criar a janela - display vai pertencer a essa janela
    glutDisplayFunc(desenha);
    inicializa();
    // Depois de fazer tudo, chama essa função para fechar tudo
    glutMainLoop();
}