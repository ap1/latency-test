

#pragma comment (lib, "freeglut.lib")

#include <iostream>
#include <cstdio>

#include <GL/glut.h>

#include "FPSMeter.h"

using namespace std;

// ----------------------------------------
// function prototypes
// ----------------------------------------
void init(int argc, char* argv[]);
void display();
void keypress(unsigned char key, int x, int y);
void idle();
void resize(int width, int height);

int W = 1280, H = 800;

Stopwatch sw;

int main(int argc, char* argv[])
{
  init(argc, argv);

  resize(W, H);

  sw.Reset();
  glutMainLoop();
}

void init(int argc, char* argv[])
{
    // initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(W, H);
    
    glutIdleFunc(idle);

    // create ref window
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Latency test");

    glutDisplayFunc  (display);
    glutReshapeFunc  (resize);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 1.0f, 1.0f);


  sw.GetTime();
  __int64 curtime = ((sw.cur_tick) * 1000) / sw.ticks_per_sec;

  int nbits = 16;

  float quadwidth = (float)W / (float)nbits;

  glBegin(GL_QUADS);
  for (int bit = nbits - 1; bit >= 0; bit--)
  {
    if ((curtime & (1ll << bit)) != 0)
    {
      int loc_id = nbits - 1 - bit;

      float x1 = quadwidth * (float) (loc_id + 0);
      float x2 = quadwidth * (float) (loc_id + 1);

      //printf("bit = %d, x = %f %f\n", bit, x1, x2);

      glVertex2f(x1, 0.0f);
      glVertex2f(x2, 0.0f);
      glVertex2f(x2, (float)H);
      glVertex2f(x1, (float)H);
    }
  }
  glEnd();

  //glFlush();
  glutSwapBuffers();
}

void keypress(unsigned char key, int x, int y)
{

}

void idle()
{
  glutPostRedisplay();
}

void resize(int width, int height)
{
  W=width;
  H=height;
  glViewport(0,0,W,H);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0f, (float)W, 0.0f, (float)H);
}
