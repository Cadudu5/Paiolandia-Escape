#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Estrutura Point
struct Point {
    int x, y;
};

Point pontoAzul;
Point bolaVermelha;

const int TAMANHO = 50;
float pontoX, pontoY;
GLfloat angle, fAspect;
GLfloat obsX = 3401;
GLfloat obsY = 7700;
GLfloat obsZ = 3000;
GLfloat alvoX = -1700;
GLfloat alvoY = -41900;
GLfloat alvoZ = 3000;
GLfloat vetX = 0;
GLfloat vetY = 1;
GLfloat vetZ = 0;
GLfloat cam_near = 0.1;
GLfloat cam_far = 100000000000000.0;
GLfloat bolaX = 100;
GLfloat bolaY = 20;
GLfloat bolaZ = 100;

const int TAMANHO = 50;
int labirinto[TAMANHO][TAMANHO] = {0}; // Inicialize o labirinto com zeros

void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, cam_near, cam_far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(obsX, obsY, obsZ, alvoX, alvoY, alvoZ, 0, 1, 0);
}

// Função para gerar o ponto azul aleatoriamente
void gerarPontoFinal() {
    pontoX = std::rand() % TAMANHO;
    pontoY = std::rand() % TAMANHO;
}

// Função para implementar o algoritmo de Prim para gerar o labirinto
void gerarLabirinto() {
    // Implemente o algoritmo de Prim aqui para preencher o labirinto
    std::srand(std::time(0));

    // Inicializa as coordenadas do ponto azul aleatoriamente
    pontoAzul = {std::rand() % TAMANHO, std::rand() % TAMANHO};
    labirinto[pontoAzul.x][pontoAzul.y] = 0; // Abre um caminho para o ponto azul

    std::vector<Point> fronteira;
    fronteira.push_back(bolaVermelha);

    while (!fronteira.empty()) {
        int index = std::rand() % fronteira.size();
        Point current = fronteira[index];
        fronteira.erase(fronteira.begin() + index);

        std::vector<Point> vizinhos = {
            {current.x - 2, current.y},
            {current.x + 2, current.y},
            {current.x, current.y - 2},
            {current.x, current.y + 2}
        };

        for (const Point& vizinho : vizinhos) {
            if (vizinho.x >= 0 && vizinho.x < TAMANHO && vizinho.y >= 0 && vizinho.y < TAMANHO && labirinto[vizinho.x][vizinho.y] == 1) {
                labirinto[vizinho.x][vizinho.y] = 0; // Abre um caminho
                fronteira.push_back(vizinho);
            }
        }
    }
}

void Desenha(void) {
    // Implementação da função Desenha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (cameraTerceiraPessoa)
    {
        glLoadIdentity();
        gluLookAt(bolaX + 200, bolaY + 400, bolaZ + 200, bolaX, bolaY, bolaZ, vetX, vetY, vetZ);
    }
    else
    {
        EspecificaParametrosVisualizacao();
    }

    // Labirinto
    glLineWidth(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (labirinto[i][j] == 1) {
                for (int k = 0; k < 200; k++) {
                    glBegin(GL_QUADS);
                    glVertex3f(j * 100.0f, k, i * 100.0f);
                    glVertex3f(j * 100.0f, k, (i + 1) * 100.0f);
                    glVertex3f((j + 1) * 100.0f, k, (i + 1) * 100.0f);
                    glVertex3f((j + 1) * 100.0f, k, i * 100.0f);
                    glEnd();
                }
            }
        }
    }
    // Desenhar o ponto aleatório
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o ponto
    glPushMatrix();
    glTranslatef(pontoY * 100.0f, 0, pontoX * 100.0f); // Posição do ponto no labirinto
    glutSolidCube(100); // Desenha um cubo (que aparece como um quadrado devido à escala)
    glPopMatrix();

    //base
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 5100.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(5100.0f, 0.0f, 0.0f);
    glVertex3f(5100.0f, 0.0f, 5100.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(bolaX, bolaY, bolaZ);
    glutSolidSphere(20.0f, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

bool ColisaoComParede(GLfloat x, GLfloat z) {
    // Calcular as coordenadas da célula na qual a bola está tentando entrar
    int i = static_cast<int>((bolaZ + z) / 100.0f);
    int j = static_cast<int>((bolaX + x) / 100.0f);

    // Verificar se a célula é uma parede (valor 1 no labirinto)
    if (i >= 0 && i < TAMANHO && j >= 0 && j < TAMANHO) {
        return labirinto[i][j] == 1;
    } else {
        // Se as coordenadas estiverem fora dos limites do labirinto, tratar como colisão
        return true;
    }
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    GLfloat novaPosX = bolaX;
    GLfloat novaPosZ = bolaZ;

    switch (key)
    {
    case 'd':
        if (cameraTerceiraPessoa)
            novaPosZ -= 50;
        break;
    case 'a':
        if (cameraTerceiraPessoa)
            novaPosZ += 50;
        break;
    case 'w':
        if (cameraTerceiraPessoa)
            novaPosX -= 50;
        break;
    case 's':
        if (cameraTerceiraPessoa)
            novaPosX += 50;
        break;
    case 'c':
        cameraTerceiraPessoa = !cameraTerceiraPessoa;
        break;

    case 'y':
        obsX += 100;
        break;
    case 'u':
        obsX -= 100;
        break;
    case 'i':
        obsY += 100;
        break;
    case 'o':
        obsY -= 100;
        break;
    case 'h':
        obsZ += 100;
        break;
    case 'j':
        obsZ -= 100;
        break;
    case 'k':
        alvoX += 100;
        break;
    case 'l':
        alvoX -= 100;
        break;
    case 'v':
        alvoY += 100;
        break;
    case 'b':
        alvoY -= 100;
        break;
    case 'n':
        alvoZ += 100;
        break;
    case 'm':
        alvoZ -= 100;
        break;
    case 'z':
         obsX = 3201;
 obsY = 5900;
 obsZ = 3000;
 alvoX = 200;
 alvoY = -21000;
 alvoZ = 3000;
        break;
    case 'f':
        cout<< "obsX = "<< obsX << "\n";
        cout<< "obsY = "<< obsY << "\n";
        cout<< "obsZ = "<< obsZ << "\n";
        cout<< "alvoX = "<< alvoX << "\n";
        cout<< "alvoY = "<< alvoY << "\n";
        cout<< "alvoZ = "<< alvoZ<< "\n";
        break;
    }

    if (!ColisaoComParede(novaPosX - bolaX, novaPosZ - bolaZ))
    {
        bolaX = novaPosX;
        bolaZ = novaPosZ;
    }

    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    EspecificaParametrosVisualizacao();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Labirinto com Paredes e Colisões");
    glutKeyboardFunc(GerenciaTeclado);
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);

    // Gere o labirinto usando o algoritmo de Prim
    gerarLabirinto();

    // Gere o ponto azul aleatoriamente
    gerarPontoFinal();

    // Inicialize o restante do labirinto
    // ...

    glutMainLoop();
    return 0;
}
