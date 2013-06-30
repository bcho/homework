/*
 * # NOTES
 *
 * ## compile
 *
 * gcc chapter1.c -o chapter1 -L/usr/X11R6/lib -lglut -lGLU -lGL -lGLEW\
 *  -lX11 -lXmu -lXi
 *
 * ## check infomation
 *
 * `glxinfo`
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define WINDOW_TITLE_PREFIX "Chapter 1"

int CURRENT_WIDTH = 800,
    CURRENT_HEIGHT = 600,
    WINDOW_HANDLE = 0;

unsigned FRAME_COUNT = 0;

void init(int, char *[]);
void init_window(int, char *[]);
void resize_cb(int, int);
void render_cb(void);
void timer_cb(int);
void idle_cb(void);

int
main(int argc, char *argv[])
{
    init(argc, argv);

    glutMainLoop();

    return EXIT_SUCCESS;
}

void
init(int argc, char *argv[])
{
    GLenum glew_init_ret;

    init_window(argc, argv);

    glew_init_ret = glewInit();

    if (glew_init_ret != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(glew_init_ret));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void
init_window(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitContextVersion(3, 1);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(CURRENT_WIDTH, CURRENT_HEIGHT);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    WINDOW_HANDLE = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if (WINDOW_HANDLE < 1) {
        fprintf(stderr, "ERROR: Could not create a new redering window.\n");
        exit(EXIT_FAILURE);
    }

    // register callback
    glutReshapeFunc(resize_cb);
    glutDisplayFunc(render_cb);
    glutIdleFunc(idle_cb);
    glutTimerFunc(0, timer_cb, 0);
}

void
resize_cb(int width, int height)
{
    CURRENT_WIDTH = width;
    CURRENT_HEIGHT = height;
    glViewport(0, 0, CURRENT_WIDTH, CURRENT_HEIGHT);

    fprintf(stderr, "DEBUG: width: %d, height: %d\n", width, height);
}

void
render_cb(void)
{
    FRAME_COUNT += 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
    glutPostRedisplay();
}

void
idle_cb(void)
{
    glutPostRedisplay();
}

void
timer_cb(int value)
{
    if (value != 0) {
        char *temp = malloc(512 + strlen(WINDOW_TITLE_PREFIX));

        sprintf(temp, "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FRAME_COUNT * 4,
                CURRENT_WIDTH,
                CURRENT_HEIGHT);

        glutSetWindowTitle(temp);
        free(temp);
    }

    FRAME_COUNT = 0;
    glutTimerFunc(250, timer_cb, 1);
}
