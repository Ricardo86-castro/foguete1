/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include<math.h>
#include <stdlib.h>
#include<random>
#include<stdio.h>

//escala
GLfloat scalex=1.0;
GLfloat scaley=1.0;
GLfloat scalez=1.0;
//translação
GLfloat tx=0.0;
GLfloat ty=0.0;
GLfloat tz=0.0;

//xu e yu do universo
float xu = 0;
float yu = 0;
//coordenadas de origem de um quadrado
float xq = 0.0;
float yq = 0.0;



void grid(){
    //const float sizeL = 3.f;
    const float grid = 1.f;
    //------------------------------------------definicao de grid
    glLineWidth(1.0);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        for(float i=-10.0; i<10.0; i+=grid)
        {
            //linhas horizontais
            glVertex2f(-10.f, i);
            glVertex2f(10.f, i);
            //linhas verticais
            glVertex2f(i, -10.f);
            glVertex2f(i, 10.f);
        }
    glEnd();
}

void draw(){

    glClear(GL_COLOR_BUFFER_BIT);
    grid();
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // vermelho
        glVertex2f( -1, 1);
        glVertex2f( 1, 1);
        glVertex2f( 1, -2);
        glVertex2f( -1, -2);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // vermelho
        glVertex2f( 0, -1);
        glVertex2f( 0, -1);
        glVertex2f( 1, -3);
        glVertex2f( -1, -3);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2d( 0, 3);
        glVertex2d( 1, 1);
        glVertex2d( -1, 1);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2d( -1, -2);
        glVertex2d( -1, -1);
        glVertex2d( -3, -2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2d( 1, -2);
        glVertex2d( 1, -1);
        glVertex2d( 3, -2);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.85f, 0.0f);
        glVertex2f( 0, -4);
        glVertex2f( 0, -4);
        glVertex2f( 1, -3);
        glVertex2f( -1, -3);
    glEnd();
    glColor3f(0.0f, 1.0f, 1.0f); // Red

    glTranslatef(0.0f, -0.2f, 0.0f);
    // Draw the circle
    glBegin(GL_POLYGON);
    float radius = 0.6f;
    int numSegments = 100;
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.14159f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta); // Move o círculo para baixo
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();

    glFlush();
}
//método utilizado para controlar as entradas especiais do teclado
void directs(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT: {
            if (tx - 2.0 >= -8.0) // Check if the rocket won't go beyond the left boundary
                tx -= 2.0;
            break;
        }
        case GLUT_KEY_RIGHT: {
            if (tx + 2.0 <= 8.0) // Check if the rocket won't go beyond the right boundary
                tx += 2.0;
            break;
        }
        case GLUT_KEY_DOWN: {
            if (ty - 2.0 >= -8.0) // Check if the rocket won't go beyond the bottom boundary
                ty -= 2.0;
            break;
        }
        case GLUT_KEY_UP: {
            if (ty + 2.0 <= 8.0) // Check if the rocket won't go beyond the top boundary
                ty += 2.0;
            else
                ty = -5.5; // Reset the rocket's position to the bottom
            break;
        }
        default: ;
    }
    glutPostRedisplay();
}

//método utilizado para tratar as entradas ascii do teclado
void comands(unsigned char key, int x, int y){
   //printf("%d",key);
   switch(key){
        case '+':{scalex+=0.2;scaley+=0.2;scalez+=0.0;break;}
        case '-':{scalex-=0.2;scaley-=0.2;scalez-=0.0;break;}
        default:;
   }
   glutPostRedisplay();//método para nova chamada de desenho
}

void conversorSRU_SRD(int xd, int yd){
    //xd = ((xu+10) * 500) / 10
    xu = ((xd * 20) / 500)-10;

    //yd = (((yu+10) * -500) / 10) + 500
    yu = ((yd - 500) * 20 / -500) - 10;

    printf("%f,%f\n",xu,yu);

}

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    //configurando uma janela
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    //glutInitWindowPosition(0,0);    // Set window position
    glutInitWindowSize(400, 500);     // Set window size
    glutCreateWindow("Exemplo 01: exibindo uma janela");
    //glClearColor(1.0, 1.0, 1.0, 0.0); // Set display window colour to white
    //delimitando orientacoes do cenário
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);

    //registro de funcao de callback
    glutDisplayFunc(draw);
    glutKeyboardFunc(comands);
    glutSpecialFunc(directs);



    //iniciando variaveis
    glClearColor(0.0,0.0,0.0,0.0);


    //loop de tratamento de eventos
    glutMainLoop();


    return EXIT_SUCCESS;
}

