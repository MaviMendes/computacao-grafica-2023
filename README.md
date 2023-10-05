## Trabalho de computação gráfica

Autoras: Milena Monteiro e Maria Vitória

Animação: 
Boneco (2D) anda e chuta a bola (3D)  no gol.

Movimento controlado pelo usuário ao apertar a tecla 'c'.

Rodar:
g++ -o main *.cpp -lGL -lGLU -lglut -lm && ./main

Sugestão:
      Inicie a leitura do código pela função main.cpp:
            main()
            inicializa()
            desenha()
            outras funções

Para auxiliar na criação dos objetos que compõe a cena, temos os seguintes arquivos:

**Vertice.cpp**

Define que um objeto vértice possui coordenada x e y.

**Objeto.cpp**

Define que objetos são compostos por vértices e possuem cor.
Define operações que podem ser aplicadas sobre objetos: cisalhamento no eixo x ou y, rotação, translação, reflexão no eixo x ou y.

**Personagem.cpp**

Define um personagem, no caso o boneco.
O boneco tem membros, cada um deles é um objeto, sendo cada objeto um conjunto de vértices que possui cor e pode ter operações aplicacas sobre ele.
O boneco anda, gira a perna do chute e comemora. Cada uma dessas ações está definida em uma função.

### Conclusão

Esse trabalho consiste em posicionar objetos em posições iniciais, iniciar um movimento a partir de ação do usuário e controlar
a movimentação dos objetos usando como parâmetro a posição deles ao longo do tempo.
Foram criados objetos 2D e 3D, utilizados recursos de iluminação e profundidade, por exemplo. Além disso, foram aplicadas operações de translação, rotação
e foi feito uso da curva de bezier para definir o movimento de um objeto ao longo dela.