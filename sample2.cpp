#include <GL/glut.h>
#include <math.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int numFlags = 8;
float flagPositions[8][2] = {
    {-0.8, 0.2}, {-0.3, -0.5}, {0.2, 0.3}, 
    {0.6, -0.3}, {0.8, 0.5}, {-0.6, 0.4},
    {0.2, -0.7}, {-0.4, -0.3}
};

float flagWaves[8] = {0.0};

float manPos[2] = {0.0, 0.0};  

int manWalkDirection = 1;  

void drawFlags() {
    glColor3f(1.0, 0.0, 0.0);
    for(int i=0; i<numFlags; i++) {
        glPushMatrix();
        glTranslatef(flagPositions[i][0], flagPositions[i][1], 0);
        glRotatef(flagWaves[i], 0, 0, 1);
        glRectf(-0.05, 0.0, 0.05, 0.3); 
        glPopMatrix();
    }
}

void drawMan() {
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix(); 
        glTranslatef(manPos[0], manPos[1], 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(-0.05,-0.05, 0);
            glVertex3f( 0.05,-0.05, 0);
            glVertex3f( 0.0, 0.05, 0);
        glEnd();
    glPopMatrix();
}

void displayScene() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // sky
    glBegin(GL_QUADS);
      glColor3f(0.529, 0.808, 0.922);
      glVertex2f(-1.0f, 0.8f);
      glVertex2f(1.0f, 0.8f);
      glColor3f(0.282, 0.718, 0.867);  
      glVertex2f(1.0f, -1.0f);
      glVertex2f(-1.0f, -1.0f);
   glEnd();

   // ground
   glBegin(GL_QUADS);
      glColor3f(0.0, 0.749, 0.0);
      glVertex2f(-1.0f, -0.2f);
      glVertex2f(1.0f, -0.2f);
      glColor3f(0.0, 0.498, 0.0);    
      glVertex2f(1.0f, -1.0f);
      glVertex2f(-1.0f, -1.0f);
   glEnd();
   
   // grass
   glColor3f(0.0, 0.502, 0.0);
   for(int i=-5; i<5; i++) {
       for(int j=-5; j<5; j++) {
           glBegin(GL_TRIANGLES);
               glVertex2f((float)i/10.0, (float)j/10.0-0.05);
               glVertex2f((float)(i+1)/10.0, (float)j/10.0-0.05); 
               glVertex2f((float)(i+0.5)/10, (float)j/10.0+0.05);           
           glEnd();
       }
   } 
   
   // trees
   glColor3f(0.565, 0.933, 0.565);
   for(int i=-5; i<5; i++) {
       for(int j=-5; j<5; j++) {
           glBegin(GL_TRIANGLES);
               glVertex2f((float)i/10.0 + 0.1, (float)j/10.0 + 0.05);
               glVertex2f((float)i/10.0 + 0.1, (float)j/10.0 - 0.05); 
               glVertex2f((float)i/10.0 - 0.1, (float)j/10.0 - 0.05);        
           glEnd();
       }
   }  
   
   drawFlags();
   
   drawMan();
   
   glutSwapBuffers();  
   
}

void update(int value) {

    manPos[0] += 0.01 * manWalkDirection;
    
    if(manPos[0] > 1.0) manWalkDirection = -1;
    if(manPos[0] < -1.0) manWalkDirection = 1;
    
    for(int i=0; i<numFlags; i++) {
        flagWaves[i] += 0.5;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);         
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Nature Scene");
    glutDisplayFunc(displayScene);
    glutTimerFunc(20, update, 0);   
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    
    glutMainLoop();

    return 0; 
}