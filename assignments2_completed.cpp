/*
  name: Michael Griggs
  class: computer graphics
  assignmentS2
*/
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
//all shapes will be yellow accross a black background so that they can easily be viewed

void point(void){ //generate a point 
  glPushMatrix();
  glPointSize(3.0);
  glTranslatef(0, -0.7, 0);
  glScalef(1.75, 1.75, 0);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(.15,.075);
  glEnd();
  glPopMatrix();
}

void line(void){ //generate a diagonal line
  glPushMatrix();
  glTranslatef(0, -1, 0);
  glScalef(.75, .75, 0);
  glRotatef(80, 0, -1, 0);
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  //line coords for x and y
  float lxy[2] = {-.15, .15};
  for(int l = 0; l < 2; l++){
    glVertex3f(lxy[l], lxy[l],0);
  }
  glEnd();
  glPopMatrix();
}

void square(void) { //generate a square
  glPushMatrix();
  glTranslatef(-1, 1, 0);
  glScalef(.75, .75, .75);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_POLYGON);
  //coords for square as it relates to x and y
  float sx[] = {0.15, -0.15,-0.15,0.15};
  float sy[]={0.15,0.15, -0.15,-0.15};
  for(int s = 0; s < 4 ; s++){
    glVertex3f(sx[s]/2,sy[s],0);
  }
  glEnd();
  glPopMatrix();
}


void triangle(void) { //generate an equilateral triangle
  glPushMatrix();
  glTranslatef(-1, -1, 0);
  glScalef(.75, .75, 0);
  glRotatef(60, -1, -1, 1);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_TRIANGLES);
  //triangle coords as it realtes to x and y
  float tx[3] = {-0.15, 0.15, 0.0};
  float ty[3] = {-0.15, -0.15, 0.15};
  for(int t = 0; t < 3; t++){
    glVertex3f(tx[t], ty[t], 0);
  }
  glEnd();
  glPopMatrix();
}

void octagon(void){ //generate a octagon 
  glPushMatrix();
  glTranslatef(-1.0, 0.0, 0.0);
  glScalef(1.0, 1.0, 0.0);
  glRotatef(90.0, -1.0,-.5, 1.0);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_POLYGON);
  //coordinates of a hexagon as it realtes to x and y
  float hy[8] = {-0.15 , -0.075 , 0.075 , 0.15 , 0.15 , 0.075 , -0.075 , -0.15};
  float hx[8] = {-0.0375 , -0.075 , -0.075 , -0.0375 , 0.0375 , 0.075 , 0.075 , 0.0375};
  for(int h = 0; h < 8; h++){
    glVertex3f(hx[h],hy[h], 0);
  }
  glEnd();
  glPopMatrix();
}

void cube1(void) {//generate a cube using a bunch of well placed lines (very difficult)
  glPushMatrix();
  glTranslatef(1.0, 1.0, 0.0);
  glScalef(.2, .2, 0.0);
  //glRotatef(90.0, -1.0,-.5, 1.0);
  glBegin(GL_LINES);  
  //1st set of lines
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(-2.5,-1.25);
  glVertex2f(0.0,1.25);
  glVertex2f(2.5,-1.25);
  glVertex2f(0.0,-3.75);
  glEnd();
  //2nd set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,1.25);
  glVertex2f(0.0,3.75);
  glVertex2f(-2.5,1.25);
  glVertex2f(-2.5,-1.25);
  glEnd();
  //3rd set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,3.75);
  glVertex2f(-2.5,1.25);
  glVertex2f(0.0,-1.25);
  glVertex2f(2.5,1.25);
  glEnd();
  //4th set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,3.75);
  glVertex2f(2.5,1.25);
  glVertex2f(0.0,-3.75);
  glVertex2f(-2.5,-1.25);
  glEnd();
  //5th set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,-1.25);
  glVertex2f(-2.5,1.25);
  glVertex2f(2.5,-1.25);
  glVertex2f(0.0, 1.25);
  glEnd();
  //6th set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(2.50,-1.25);
  glVertex2f(2.50,1.25);
  glVertex2f(0.0,-1.25);
  glVertex2f(0.0,-3.75);
  glEnd();

  glPopMatrix();
}

void cube2(void) {//generate a cube using a bunch of well placed lines (very difficult)
  glPushMatrix();
  glTranslatef(1.0, -1.0, 0.0);
  glScalef(.2, .2, 0.0);
  glRotatef(45.0, 1.0,1.0, 1.0);
  glBegin(GL_LINES);  
  //1st set of lines
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(-2.5,-1.25);
  glVertex2f(0.0,1.25);
  glVertex2f(2.5,-1.25);
  glVertex2f(0.0,-3.75);
  glEnd();
  //2nd set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,1.25);
  glVertex2f(0.0,3.75);
  glVertex2f(-2.5,1.25);
  glVertex2f(-2.5,-1.25);
  glEnd();
  //3rd set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,3.75);
  glVertex2f(-2.5,1.25);
  glVertex2f(0.0,-1.25);
  glVertex2f(2.5,1.25);
  glEnd();
  //4th set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,3.75);
  glVertex2f(2.5,1.25);
  glVertex2f(0.0,-3.75);
  glVertex2f(-2.5,-1.25);
  glEnd();
  //5th set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(0.0,-1.25);
  glVertex2f(-2.5,1.25);
  glVertex2f(2.5,-1.25);
  glVertex2f(0.0, 1.25);
  glEnd();
  //6th set of lines
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(2.50,-1.25);
  glVertex2f(2.50,1.25);
  glVertex2f(0.0,-1.25);
  glVertex2f(0.0,-3.75);
  glEnd();

  glPopMatrix();
}


void circle(void){ //generate a circle
  glPushMatrix();
  glTranslatef(0, 1, 0 );
  glScalef(.75, .75, .75);
  glRotatef(360, 0, 1, 0);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_POLYGON);
  float rad = 0.15;
  //loop to generate circle from 40 polygons
  for(int c = 0; c < 40.0; c++){
    //angle_of_cric is a number that is used to generate the proper polygon based on the current polygon index
    float angle_of_circ = (2.0f * 3.14159 * float(c))/40.0;
    //current polygon as it realtes to x and y
    float xc = rad*cosf(angle_of_circ);
    float yc = rad*sinf(angle_of_circ);
    glVertex3f(xc/2,yc, 0);
  }
  glEnd();
  glPopMatrix();
}

void init_background(void){// this function creates the initial conditions (background) upon which all the shapes will be generated
  glClearColor(0.0,0.0,0.0,0.0); //black
  //glPointSize(1.0);
 // glLineWidth(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-2.0 , 2.0 , -2.0 , 2.0 , 2.0 , 6.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, -2.0, 0.0, 1.0, 0.0);

  glEnable(GL_DEPTH_TEST);
}

void reset(void){ //reset buffer so that all shapes may be loaded
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void inputs(unsigned char input, int q, int p){//input logic
  switch (input){
    case 'p':
    case 'P':
      point();
      line();
      triangle();
      square();
      octagon();
      circle();
      cube1();
      cube2();
      break;/*
    case 'l':
    case 'L':
      line();
      break;
    case 't':
    case 'T':
      triangle();
      break;
    case 's':
    case 'S':
      square();
      break;
    case 'o':
    case 'O':
      octagon();
      break;
    case 'c':
    case 'C':
      circle();
      break;
    case 'u':
    case 'U':
      cube1();
      cube2();
      break;*/
    case 'Q':
    case 'q':
      exit(-1);
    default:
      break;
  }
}



int main(int argc,char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1024,1024);
  glutInitWindowPosition(300,200);
  glutCreateWindow("press P or p to start, and q or Q to quit");
  glutDisplayFunc(reset);
  glutKeyboardFunc(inputs);
  init_background();
  glViewport(40, 40 ,512,512);
  glutMainLoop();
}
