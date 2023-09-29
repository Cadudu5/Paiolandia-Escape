//Testando o baguio

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

GLfloat angle, fAspect;
GLfloat obsX = 0;
GLfloat obsY = 3000;
GLfloat obsZ = 1000;
//GLfloat obsEixo = 0;
GLfloat alvoX = 0;
GLfloat alvoY = 0;
GLfloat alvoZ = 0;
GLfloat vetX = 0;
GLfloat vetY = 1;
GLfloat vetZ = 0;
GLfloat cam_near = 0.1;
GLfloat cam_far = 100000000000000.0;

GLfloat bolaX = 0;
GLfloat bolaY = 0;
GLfloat bolaZ = 0;

// Variáveis para controle de câmera
bool cameraTerceiraPessoa = true;

void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, cam_near, cam_far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1, 5000, 0, 0, 0, 0, 0, 1, 0);
}


void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (cameraTerceiraPessoa) {
        glLoadIdentity();
		gluLookAt(bolaX+200, bolaY+400, bolaZ+200, bolaX, bolaY, bolaZ, vetX, vetY, vetZ);

    } else {
        EspecificaParametrosVisualizacao();
    }

    // Defina a espessura das linhas brancas
    glLineWidth(5.0f);  // Ajuste o valor conforme necessário
    // Desenhe as bordas do quadrado verde
    glColor3f(1.0f, 1.0f, 1.0f);  // Cor das bordas (preto)
    glBegin(GL_LINES);
    glVertex3f(-1000.0f, 0.0f, -1000.0f);  // Linha inferior do quadrado
    glVertex3f(1000.0f, 0.0f, -1000.0f);

    glVertex3f(-1000.0f, 0.0f, 1000.0f);  // Linha superior do quadrado
    glVertex3f(1000.0f, 0.0f, 1000.0f);

    glVertex3f(-1000.0f, 0.0f, -1000.0f);  // Linha esquerda do quadrado
    glVertex3f(-1000.0f, 0.0f, 1000.0f);

    glVertex3f(1000.0f, 0.0f, -1000.0f);  // Linha direita do quadrado
    glVertex3f(1000.0f, 0.0f, 1000.0f);
    glEnd();

    // Desenhe o chão
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1000.0f, 0.0f, -1000.0f);
    glVertex3f(-1000.0f, 0.0f, 1000.0f);
    glVertex3f(1000.0f, 0.0f, 1000.0f);
    glVertex3f(1000.0f, 0.0f, -1000.0f);
    glEnd();

    // Bolinha
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(bolaX, bolaY, bolaZ);
    glutSolidSphere(20.0f, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

void Def_Iluminacao() {
	// Configuração de Iluminação
	GLfloat luzAmbiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat luzDifusa[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat posicaoLuz[4] = { -900.0, 0.0, 0.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0, 1.0,1.0,1.0 }; // define a cor do brilho no material, geralmente branco
	GLint expoenteEspecular = 50; // define o brilho do material. varia de 0-128. Mais espelhado ou menos espelhado.

	// Especifica que a cor de fundo da janela ser� preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
}

void Inicializa(void)
{
    // Define iluminacao
    Def_Iluminacao();

    angle = 45;
}


void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    EspecificaParametrosVisualizacao();
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        if (cameraTerceiraPessoa) bolaZ += 50;
        break;
    case 'a':
        if (cameraTerceiraPessoa) bolaZ -= 50;
        break;
    case 'w':
        if (cameraTerceiraPessoa) bolaX += 50;
        break;
    case 's':
        if (cameraTerceiraPessoa) bolaX -= 50;
        break;
    case 'c':
        cameraTerceiraPessoa = !cameraTerceiraPessoa;
        break;
    }

    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(700, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Paiolandia Escape");

    glutKeyboardFunc(GerenciaTeclado);
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);

    Inicializa();
    glutMainLoop();
}
