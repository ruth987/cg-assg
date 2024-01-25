#include <GL/glut.h>

float angle = 0.0f; // Initial rotation angle

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    glRotatef(angle, 1.0, 1.0, 0.0); // Rotate the cube around the x and y axes
    
    glutWireCube(1.0); // Draw a wireframe cube
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
}

void update(int value) {
    angle += 2.0f; // Increment the rotation angle
    if (angle > 360.0) {
        angle -= 360.0;
    }

    glutPostRedisplay(); // Request a redraw to update the display
    glutTimerFunc(16, update, 0); // Set the next update call
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL Cube Example");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, update, 0); // Set up the timer for continuous rotation

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutMainLoop();

    return 0;
}
