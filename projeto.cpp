//****************************************************
//
// pratica5.cpp
// Iluminação
// 
//*****************************************************
#include <GL/glut.h>
#include <iostream>
GLfloat angle, fAspect, largura, altura, ycamera;

GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = 250.0f;

void EspecificaParametrosVisualizacao(void)
{
    // Set the camera's initial position
    cameraX = 0.0f;
    cameraY = 200.0f; // Adjust this value to position the camera above the floor
    cameraZ = 200.0f; // Adjust this value to control the distance from the floor

    // Specify the position of the camera and target
    gluLookAt(cameraX, cameraY, cameraZ,   // position of the camera
              0, 0, 0,                   // position of the target (center of the scene)
              0, 1, 0);                  // up vector of the camera

    
    
}

void Inicializa(void)
{
    GLfloat luzAmbiente[4]={0.2, 0.2, 0.2, 1.0};   // {R, G, B, alfa}
	GLfloat luzDifusa[4]={0.5, 0.5, 0.5, 1.0};	   // o 4o componente, alfa, controla a opacidade/transparência da luz
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={50.0, 50.0, 50.0, 1.0};  // aqui o 4o componente indica o tipo de fonte:
                                                    // 0 para luz direcional (no infinito) e 1 para luz pontual (em x, y, z)

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0, 1.0, 1.0, 1.0}; 
	GLint especMaterial = 100;

 	// Especifica a cor de fundo da janela
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);  // a cor de cada ponto da primitiva é interpolada a partir dos vértices
    //glShadeModel(GL_FLAT);  // a cor de cada primitiva é única em todos os pontos

	// Define a refletância do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	angle = 45;
    ycamera = 0;
}

void DrawFloor()
{
    glColor3f(0.0f, 0.5f, 0.0f);  // Set the floor color (green, for example)
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);  // Define the vertices of the floor
    glVertex3f(100.0f, 0.0f, -100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glEnd();
}


void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica a viewport
    glViewport(0, 0, largura, altura);

    // Draw the floor
    DrawFloor();

    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
        glTranslated(0, 0, 40);
        glutSolidTeapot(50.0f);
    glPopMatrix();

    glutSwapBuffers();
}


/* Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
	gluPerspective(angle, fAspect, 0.1, 1000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0, ycamera, 250,  // posição da câmera
              0, 0, 0,          // posição do alvo
              0, 5, 5);         // vetor UP da câmera
}
*/

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLint largura, GLint altura)
{
	// Para previnir uma divisão por zero
	if (altura == 0) altura = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, largura, altura);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			//if (angle >= 10) angle -= 5;
            ycamera += 10;  
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			//if (angle <= 130) angle += 5;
            ycamera -= 10; 
		}
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //aplica o zBuffer  
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //GLUT_DEPTH habilita o  depth-buffering
	
    glutInitWindowPosition(700,100);
    largura = 600;
    altura = 500;
    //ycamera = 100;
	fAspect = (GLfloat)largura / (GLfloat)altura;
    glutInitWindowSize(largura,altura);
    glutCreateWindow("Aula Pratica 5"); 

	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela); // Função para ajustar o tamanho da tela
    glutMouseFunc(GerenciaMouse);
    //glutKeyboardFunc(GerenciaTeclado); // Define qual funcao gerencia o comportamento do teclado
    //glutSpecialFunc(TeclasEspeciais); // Define qual funcao gerencia as teclas especiais
	Inicializa();
	glutMainLoop();

}