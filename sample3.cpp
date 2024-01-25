#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>

const float TRACK_WIDTH = 100.0f;
const float TRACK_BREADTH = 200.0f;

const int ROAD_POINT_COUNT = 4000;
const float ROAD_WIDTH = 40.0f;

GLfloat boundaryPoints[4000][2];
GLfloat innerBoundary[4000][2];
GLfloat centerLine[4000][2];

float twist;
float twistDirection;

GLfloat obstacles[100][2];
GLfloat powerups[30][2];

void generateTrackPoints() {
    // Generate outer boundary
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        float theta = i * 2 * M_PI / ROAD_POINT_COUNT;
        boundaryPoints[i][0] = TRACK_BREADTH * 0.5f * cos(theta);
        boundaryPoints[i][1] = TRACK_BREADTH * 0.5f * sin(theta);
    }

    // Generate inner boundary
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        innerBoundary[i][0] = (TRACK_BREADTH - ROAD_WIDTH) * 0.5f * cos(twist + i * 2 * M_PI / ROAD_POINT_COUNT);
        innerBoundary[i][1] = (TRACK_BREADTH - ROAD_WIDTH) * 0.5f * sin(twist + i * 2 * M_PI / ROAD_POINT_COUNT);
    }

    // Generate center line
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        centerLine[i][0] = 0.5 * (innerBoundary[i][0] + boundaryPoints[i][0]);
        centerLine[i][1] = 0.5 * (innerBoundary[i][1] + boundaryPoints[i][1]);
    }

    // Add twisting
    twist = 0.0f;
    twistDirection = 1.0f;
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        twist += 0.001f * twistDirection;
        if (twist > 0.2f || twist < -0.2f) {
            twistDirection *= -1.0f;
        }
        boundaryPoints[i][0] += twist * cos(i * 2 * M_PI / ROAD_POINT_COUNT);
        boundaryPoints[i][1] += twist * sin(i * 2 * M_PI / ROAD_POINT_COUNT);
        innerBoundary[i][0] += twist * cos(i * 2 * M_PI / ROAD_POINT_COUNT);
        innerBoundary[i][1] += twist * sin(i * 2 * M_PI / ROAD_POINT_COUNT);
        centerLine[i][0] += twist * cos(i * 2 * M_PI / ROAD_POINT_COUNT);
        centerLine[i][1] += twist * sin(i * 2 * M_PI / ROAD_POINT_COUNT);
    }

    // Add obstacles
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        int index = rand() % ROAD_POINT_COUNT;
        obstacles[i][0] = boundaryPoints[index][0];
        obstacles[i][1] = boundaryPoints[index][1];
    }

    // Add powerups
    for (int i = 0; i < 30; i++) {
        int index = rand() % ROAD_POINT_COUNT;
        powerups[i][0] = centerLine[index][0];
        powerups[i][1] = centerLine[index][1];
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw road surface
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        glVertex2fv(boundaryPoints[i]);
        glVertex2fv(innerBoundary[i]);
        glVertex2fv(innerBoundary[(i + 1) % ROAD_POINT_COUNT]);
        glVertex2fv(boundaryPoints[(i + 1) % ROAD_POINT_COUNT]);
    }
    glEnd();

    // Draw outer boundary
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        glVertex2fv(boundaryPoints[i]);
    }
    glEnd();

    // Draw inner boundary
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        glVertex2fv(innerBoundary[i]);
    }
    glEnd();

    // Draw center line
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < ROAD_POINT_COUNT; i++) {
        glVertex2fv(centerLine[i]);
    }
    glEnd();

    // Draw obstacles
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
        glVertex2fv(obstacles[i]);
    }
    glEnd();

    // Draw powerups
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 30; i++) {
        glVertex2fv(powerups[i]);
    }
    glEnd();

    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Detailed Race Track");

    generateTrackPoints();

    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 0;
}
