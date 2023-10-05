#include "libs.h"
#include "Vertice.h"
#include "Objeto.h"
#include "Personagem.h"

using namespace std;

// ângulos que irão controlar movimento de chute boneco. variáveis usadas na função Timer()
GLfloat anguloMax = 20.0, anguloMin = 0.0;

Personagem *personagem;

// variáveis que serão usadas de parâmetro para controlar o movimento da esfera
GLfloat x_esf = 0.5f, y_esf = 0.2f, z_esf = 0.0f; // posição inicial da esfera
GLfloat x_final_esf = 4.0f; // posição final
GLfloat x_med_esf = 2.25f; // posição intermediária no eixo x. a partir dessa posição, ela para de subir e começa a descer
GLfloat y_med_esf = 2.0; 

// variáveis usadas na função Timer() e controle do movimento da esfera ao longo da curva de bezier
float t = 0.0f; // usada em mover_esfera_bezier(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat t)
float velocidadeAnimacao = 0.001f; 

// variável de controle usada no Timer(): se a pos atual for menor q 4.3 e a prox maior q .5

bool boneco_virou_perna = false;

GLfloat bezier(GLfloat P0, GLfloat P1, GLfloat P2, GLfloat P3, GLfloat t)
{
    return pow(1 - t, 3) * P0 + 3 * t * pow(1 - t, 2) * P1 + 3 * pow(t, 2) * (1 - t) * P2 + pow(t, 3) * P3;
}

void mover_esfera_bezier(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat t)
{
    // Definição de pontos de controle da curva de bezier
    GLfloat P0x = 0.5f, P0y = 0.2f, P0z = 0.0f; // Ponto inicial da esfera
    GLfloat P1x = 1.5f, P1y = 3.0f, P1z = 0.0f; //ponto de controle 1
    GLfloat P2x = 2.5f, P2y = 1.5f, P2z = 0.0f; // ponto de controle 2
    GLfloat P3x = 4.0f, P3y = 0.2f, P3z = 0.0f; //posição final da esfera

    // calcular nova posição da esfera ao longo da curva de bezier
    x = bezier(P0x, P1x, P2x, P3x, t);
    y = bezier(P0y, P1y, P2y, P3y, t);
    z = bezier(P0z, P1z, P2z, P3z, t);
}

void desenha_esfera(GLfloat x, GLfloat y, GLfloat z)
{
    // Calcula as novas coordenadas da bola na curva de Bezier usando o valor de t
    mover_esfera_bezier(x_esf, y_esf, z_esf, t);

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

    // ao desenhar os vértices, especificar no sentido anti-horário
    // 1- desenha boneco 2d
    personagem->desenharPersonagem();
    //  2- desenha bola 3d
    //  Desenhar a esfera
    desenha_esfera(x_esf, y_esf, z_esf);
    // 3 - desenha "gol"
    desenha_gol();

    // Pontos 4 e 5 definidos posteriormente
    // 4- movimento boneco ate certo ponto e chute
    // 5- trajetoria da bola em uma curva e

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

    // Habilita o modelo de colorização
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentraçãoo do brilho
    glMateriali(GL_FRONT, GL_SHININESS, expoenteEspecular);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parametros da luz de numero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

    // Habilita a definiçãoo da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    // Habilita o uso de iluminaçãoo
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    personagem = new Personagem();
}

// Controle do usuário que faz o boneco andar

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

// variáveis de controle para auxiliar na animação

bool golRealizado = false;
bool podePular = false;

void Timer(int value)
{
    // se o boneco andou ate o ponto perto da bola, mas ainda não fez movimento de chute:
    // em void Personagem::andar() em Personagem.cpp o valor de boneco_andou_tudo é atualizado após ele dar dois passos
    if (!boneco_virou_perna && personagem->boneco_andou_tudo)
    {
        if (anguloMin < anguloMax)
        {
            // Aumenta gradualmente o ângulo da perna direita
            anguloMin += 10.0; // Você pode ajustar a velocidade da animação aqui
            personagem->girarPernaDireita(anguloMin);
            // Redesenha o boneco com a nova posição da perna direita
        }
        // boneco fez movimento de chute
        else
        {
            boneco_virou_perna = true;
        }
    }
    // boneco andou ate perto da bola e girou a perna
    if (boneco_virou_perna && !golRealizado) // chuta
    {
        value = 45;

        // Interpolação linear para suavizar o movimento
        float deltaT = velocidadeAnimacao * value; // Ajuste o valor conforme necessário para uma animação mais suave
        t += deltaT;

        // Garanta que t permaneça entre 0 e 1 para manter a animação dentro dos limites da curva de Bezier
        if (t > 1.0f)
        {
            t = 1.0f;
            golRealizado = true;
        }
    }
    // boneco chutou a bola, mas ainda não comemorou
    if (golRealizado && !podePular) {
        personagem->posicaoComemoracao();
        podePular = true;
    }

    glutPostRedisplay();
    glutTimerFunc(24, Timer, value + 1);
}


int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(1000, 1000);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Pressione C para andar");

    glutKeyboardFunc(ControleTeclado); // Define qual funcao gerencia o comportamento do teclado

    // define a função Timer
    glutTimerFunc(1000 / 60, Timer, 1);

    // call back function - depois de criar a janela - display vai pertencer a essa janela
    glutDisplayFunc(desenha);
    inicializa();
    // Depois de fazer tudo, chama essa função para fechar tudo
    glutMainLoop();
}