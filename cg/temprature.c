#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>

#define ROWS 10
#define COLS 30

#define AMBIENT 25.0f
#define HOT 50.0f
#define COLD 0.0f
#define NHOTS 4
#define NCOLDS 5

GLfloat angle = 0.0;
GLfloat temps[ROWS][COLS],
        back[ROWS + 2][COLS + 2];
GLfloat theta = 0.0, vp = 30.0;

int hotspots[NHOTS][2] = {
    {ROWS / 2, 0}, {ROWS / 2 - 1, 0},
    {ROWS / 2 - 2, 0}, {0, 3 * COLS / 4}
};
int coldspots[NCOLDS][2] = {
    {ROWS - 1, COLS / 2}, {ROWS - 1, 1 + COLS / 3},
    {ROWS - 1, 3 + COLS / 3}, {ROWS - 1, 4 + COLS / 3}
};

int WIN_WIDTH = 800,
    WIN_HEIGHT = 600,
    WIN_HANDLER;


void init(void);
void display(void);
void reshape(int, int);
void idle(void);
void setColor(float t);
void iterationStep(void);

void
init(void)
{
    int i, j;

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.6, 0.6, 0.6, 1.0);

    for (i = 0;i < ROWS;i++)
        for (j = 0;j < COLS;j++)
            temps[i][j] = AMBIENT;
    for (i = 0;i < NHOTS;i++)
        temps[hotspots[i][0]][hotspots[i][1]] = HOT;
    for (i = 0;i < NCOLDS;i++)
        temps[coldspots[i][0]][coldspots[i][1]] = COLD;
}

void
cube(void)
{
    typedef GLfloat point[3];

    point v[8] = {
        {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}
    };

    glBegin(GL_QUAD_STRIP);
        glVertex3fv(v[4]);
        glVertex3fv(v[5]);
        glVertex3fv(v[0]);
        glVertex3fv(v[1]);
        glVertex3fv(v[2]);
        glVertex3fv(v[3]);
        glVertex3fv(v[6]);
        glVertex3fv(v[7]);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3fv(v[1]);
        glVertex3fv(v[3]);
        glVertex3fv(v[5]);
        glVertex3fv(v[7]);
        glVertex3fv(v[4]);
        glVertex3fv(v[6]);
        glVertex3fv(v[0]);
        glVertex3fv(v[2]);
    glEnd();
}

void
display(void)
{
    #define SCALE 10.0
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(vp, vp / 2, vp / 4, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(angle, 0, 0, 1.0);

    for (i = 0;i < ROWS;i++)
        for (j = 0;j < COLS;j++) {
            setColor(temps[i][j]);
            glPushMatrix();
            glTranslatef((float) i - (float) ROWS / 2.0,
                         (float) j - (float) COLS / 2.0, 0.0);
            glScalef(10, 1.0, 0.1 + 3.9 * temps[i][j] / HOT);
            cube();
            glPopMatrix();
        }

    glPopMatrix();
    glutSwapBuffers();
}

void
reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float) w / (float) h, 1.0, 300.0);
    glutPostRedisplay();
}

void
setColor(float t)
{
    float r, g, b;
    r = (t - COLD) / (HOT - COLD); g = 0.0; b = 1.0 - r;

    glColor3f(r, g, b);
}

void
animate(void)
{
    iterationStep();
    glutPostRedisplay();
}

void
iterationStep(void)
{
    int i, j, m, n;

    float filter[3][3] = {
        {0, 0.125, 0},
        {0.125, 0.5, 0.125},
        {0, 0.125, 0}
    };

    for (i = 0;i < ROWS;i++)
        for (j = 0;j < COLS;j++)
            back[i + 1][j + 1] = temps[i][j];

    for (i = 1;i < ROWS + 2;i++) {
        back[i][0] = back[i][1];
        back[i][COLS + 1] = back[i][COLS];
    }
    for (j = 0;j < COLS + 2;j++) {
        back[0][j] = back[1][j];
        back[ROWS + 1][j] = back[i][COLS];
    }
    for (i = 0;i < ROWS;i++)
        for (j = 0;j < COLS;j++) {
            temps[i][j] = 0.0;
            for (m = -1;m <= 1;m++)
                for (n = -1;n <= 1;n++)
                    temps[i][j] += back[i + 1 + m][j + 1 + n] *\
                                   filter[m + 1][n + 1];
        }
    for (i = 0;i < NHOTS;i++)
        temps[hotspots[i][0]][hotspots[i][1]] = HOT;
    for (i = 0;i < NCOLDS;i++)
        temps[coldspots[i][0]][coldspots[i][1]] = COLD;

    angle += 1.0;
}

int
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);

    WIN_HANDLER = glutCreateWindow("Temprature in bar");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(animate);

    glutMainLoop();

    return EXIT_SUCCESS;
}
