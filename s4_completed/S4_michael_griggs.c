//s4
//Michael Griggs
//computer graphics

#include <GL/glut.h>
#include <GL/gl.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>



GLfloat a = 0.0;
GLfloat thet = 0.0;

GLboolean rotate_1 = false;
GLboolean rotate_2 = false;

float angle = 1.5  * 3.1415926535;

float eye_x = 2.0;
float view_x = 2.0;
float eye_y = 2.0;
float view_y = 2.0;
float eye_z = 9.0;
float view_z = 8.0;

struct img{
    int h;
    int w;
    int channels;
    unsigned char* pix;
};

class tex{
    public:
    tex();
    void prep(int NthTex);
    void readPPM(const char *n);
    img image;
    GLuint name;
};

tex triangle_texture;
tex square_texture;
tex hexagon_texture;
tex cube_texture;
tex cylinder_texture;
tex sphere_texture;
tex room_texture;

tex::tex(){
}

void tex::readPPM(const char *n){
    char string[100];
    int fileType;
    FILE* input_file = fopen(n, "r");

    if(input_file == NULL){
        printf("\nfile does not exist\n");
        exit(1);
    }
    fscanf(input_file, "P%d", &fileType);
    if(fileType != 6){
        printf("\nfile is not ppm format\n");
        exit(1);
    }
    fgets(string, 100, input_file);
    while(string[0] == '#'){
        fgets(string, 100, input_file);
    }

    sscanf(string, "%d", &fileType);
    fgets(string, 100, input_file);
    sscanf(string, "%d %d", &image.w, &image.h);

    if(fileType != 255){
        printf("\nwrong size file dimensions");
    }
    image.channels = 4;
    image.pix = (unsigned char*)malloc(sizeof(unsigned char) * image.channels * image.w * image.h);
    if(image.pix == NULL){
        printf("cannot malloc for the dimensions of ppm");
        exit(1);
    }
    else{
        printf("image is locked and loaded");
    }
    fread(image.pix, sizeof(unsigned char), image.channels * image.h * image.w, input_file);
    fclose(input_file);
}

void tex::prep(int NthTex){
    name = NthTex;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, name);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.w, image.h, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pix);
}


void texture_setup(){

    glGenTextures(30, &triangle_texture.name);
    triangle_texture.readPPM("building.ppm");
    triangle_texture.prep(30);

    glGenTextures(20, &square_texture.name);
    square_texture.readPPM("eyes.ppm");
    square_texture.prep(20);

    glGenTextures(10, &hexagon_texture.name);
    hexagon_texture.readPPM("girl.ppm");
    hexagon_texture.prep(10);
    
    glGenTextures(40, &cube_texture.name);
    cube_texture.readPPM("s128.ppm");
    cube_texture.prep(40);

    glGenTextures(50, &cylinder_texture.name);
    cylinder_texture.readPPM("statue.ppm");
    cylinder_texture.prep(50);

    glGenTextures(6, &sphere_texture.name);
    sphere_texture.readPPM("tile.ppm");
    sphere_texture.prep(6);

    glGenTextures(7, &room_texture.name);
    room_texture.readPPM("tree.ppm");
    room_texture.prep(7);
}

void triangle(){
    glPushMatrix();
    glTranslatef(-2.0, -1.39, 2.3);
    glBindTexture(GL_TEXTURE_2D, triangle_texture.name);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(1, 0);
    glTexCoord2f(0, 1);
    glVertex2f(0, 1);
    glEnd();
    glPopMatrix();
}

void square(){
    glPushMatrix();
    glTranslatef(-2.0, 1.3, 2.0);
    glBindTexture(GL_TEXTURE_2D, square_texture.name);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(0.0, 0.0, 1.0);
    glTexCoord2f(0,1);
    glVertex3f(0.0, 1.0, 1.0);
    glTexCoord2f(1,1);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1,0);
    glVertex3f(1.0, 0.0, 1.0);
    glEnd(); 
    glPopMatrix();
}

void hexagon(){
    glPushMatrix();
    glTranslatef(1.6, 0.7, 1.5);
    glBindTexture(GL_TEXTURE_2D, hexagon_texture.name);
    glBegin(GL_POLYGON);
    for(int h = 0; h <= 360; h+=60){
        double hx = cos(h* (M_PI/180))/2;
        double hy = sin(h* (M_PI/180))/2;
	glTexCoord2f(hx, hy);
        glVertex3d(hx,hy,0.0);
    }
    glEnd();
    glPopMatrix();
}

void cylinder(){
	glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, cylinder_texture.name);
	glRotatef(45.0, 1.0, 1.0, 1.0);
	const int numMajor = 8;
	const int numMinor = 32;
	const float height = 1.2F;
	const float radius = 0.6F;
	float majorStep = height/numMajor;
	float minorStep = 2.0F*3.14159F/numMinor;
	int i, j;
	for(i = 0; i < numMajor; i++){
		GLfloat z0 = 0.5F*height - i * majorStep;
		GLfloat z1 = z0 - majorStep;
		glBegin(GL_TRIANGLE_STRIP);
		for(j = 0; j <= numMinor; j++){
			double a = j * minorStep;
			GLfloat nx = (GLfloat) cos(a);
			GLfloat ny = (GLfloat) sin(a);
			GLfloat x = radius * nx;
			GLfloat y = radius * ny;
			glTranslatef(-1.0, 1.52, -0.75);
			glNormal3f(nx, ny, 0.0F);
			glTexCoord2f(x, y);
			glVertex3f(x, y, z0);
			glNormal3f(nx, ny, 0.0F);
			glTexCoord2f(x, y);
			glVertex3f(x, y, z1);
		}
		glEnd();
	}
	glNormal3f(0.0F, 0.0F, 1.0F);
	glBegin(GL_TRIANGLE_FAN);
	for(i = 0; i < numMinor; i++){
		float a = i * minorStep;
		GLfloat x = radius * (GLfloat) cos(a);
		GLfloat y = radius * (GLfloat) sin(a);
		glTexCoord2f(x, y);
		glVertex3f(x, y, 0.5F * height);
	}
	glEnd();

	glNormal3f(0.0F, 0.0F, -1.0F);
	glBegin(GL_TRIANGLE_FAN);
	for(i = 0; i < numMinor; i++){
		float a = i * minorStep;
		GLfloat x = radius * (GLfloat) cos(a);
		GLfloat y = radius * (GLfloat) sin(a);
		glTexCoord2f(-x, y);
		glVertex3f(-x, y, -0.5F * height);
	}
	glEnd();
	glPopMatrix();
}

void sphere(){
    glPushMatrix();
    glTranslatef(1.0, 1.52, -0.75);
    glScalef(0.5,0.5,0.5);
    glBindTexture(GL_TEXTURE_2D, sphere_texture.name);
    int i, j;
    for(i = 0; i <= 20; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / 20);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / 20);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= 15; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / 15;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glTexCoord2f(x * zr0 , y * zr0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glTexCoord2f(x * zr1, y * zr1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
	glEnd();
    }
    glPopMatrix();  
}


void room(){
	
	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.75);
	glScalef(3.0, 3.0, 3.0);
	glBindTexture(GL_TEXTURE_2D, room_texture.name);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1,1,-1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);

	
	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1,-1,-1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1,1);
	glVertex3f(-1, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(-1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, -1);
	glEnd();
	glPopMatrix();
}

void cubed(){
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1.2, -2.5, 0.75);
    glBindTexture (GL_TEXTURE_2D, cube_texture.name);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1,1,-1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);
	
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1,-1,-1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1,1);
	glVertex3f(-1, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(-1,-1,1);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, -1);
	glEnd();
	glPopMatrix();


}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(90,1,1,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye_x,eye_y,eye_z, view_x,view_y,view_z, 0,1,0);
  room();
  cubed();
  square();
  cylinder();
  triangle();
  hexagon();
  sphere();
  glutSwapBuffers();
}

void animate(){
    if(rotate_1 == true){
        thet += 0.2;
        if(thet > 360.0){
            thet -= 360.0 *floor(thet/360.0);
        }
    }

    if(rotate_2 == true){
        a += 0.2;
        if(a > 360.0){
            a -= 360.0 * floor(a/360.0);
        }
    }

    glutPostRedisplay();
}

void controller( unsigned char control, int x, int y )
{
  switch (control)
  {
    //controls the camera
  case 'a':
      angle = angle - 0.01f;
      view_x = eye_x + cos(angle);
      view_y = eye_y;
      view_z = eye_z + sin(angle);

      break;
  case 'd':
      angle = angle + 0.01f;
      view_x = eye_x + cos(angle);
      view_y = eye_y;
      view_z = eye_z + sin(angle);

      break;
  case 'w':
      eye_x = eye_x + cos(angle) * 0.5f;
      eye_z = eye_z + sin(angle) * 0.5f;
      view_x = eye_x + cos(angle);
      view_y = eye_y;
      view_z = eye_z + sin(angle);
      break;
  case 's':
      eye_x = eye_x - cos(angle) * 0.5f;
      eye_z = eye_z - sin(angle) * 0.5f;
      view_x = eye_x + cos(angle);
      view_y = eye_y;
      view_z = eye_z + sin(angle);
      break;

  case 'q':	
      exit(1);
  }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 1200);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("controls: W, A, S, D; q = quit");
    texture_setup();
    glutKeyboardFunc(controller); 
    glutDisplayFunc(display); 
    glutIdleFunc(animate);
    glutMainLoop();  
    return 0;

}

