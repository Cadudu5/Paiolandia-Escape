// Defina as dimensões do labirinto
#define ROWS 50
#define COLS 50

int labirinto[ROWS][COLS];

// Função para gerar o labirinto aleatório
void generate_maze() {
    // Código para gerar o labirinto aleatório (como o código Python fornecido anteriormente)
    // ...

    // Exemplo: Preenchendo o labirinto com dados aleatórios (substitua isso pelo seu código de geração)
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            labirinto[i][j] = rand() % 2; // Preenche com 0 ou 1 de forma aleatória
        }
    }
}

// Função para renderizar o labirinto
void render_maze() {
    // Configurações de renderização (glLineWidth, glColor, etc.)

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
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
}

// Função de exibição (chamada pelo OpenGL)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Configurações de câmera, luz, etc.

    // Gera o labirinto aleatório
    generate_maze();

    // Renderiza o labirinto
    render_maze();

    glutSwapBuffers();
}
