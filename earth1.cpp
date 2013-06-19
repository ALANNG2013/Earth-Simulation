/* modify by NG WING KIN , OUHK , 26 JAN 2012 */
#include <cstdlib> 
#include <cstdio>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>
#include <iostream>

GLuint texture[1];   // hold texture
double angle = 15;   // angle of rotation
typedef struct 
 {
 int X;      // texture coordinates
 int Y;
 int Z;
 double U;    // texture coordinate of current vertex
 double V;
 }VERTICES;

const double PI = 3.1415926535897;
const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;   // total amount of vertices
VERTICES VERTEX[VertexCount];								// vertices going to use
GLuint LoadTextureRAW( const char *filename );

void DisplaySphere(double R, GLuint texture)
{
 int b;											// This variable will control which vertex we are currently working with
 glScalef(0.0125 * R, 0.0125 * R, 0.0125 * R);  // have chosen to scale it here to 0.0125 times its original size, and then increase it by R as the original sphere is rather large
 glRotatef(90, 1, 0, 0);                      // rotating it 
 glBindTexture(GL_TEXTURE_2D, texture);     // bind the texure 

 glBegin(GL_TRIANGLE_STRIP);				//  to begin drawing the sphere itself

 // looping through each vertex
 for ( b = 0; b <= VertexCount; b++)
 {
// Assigning the texture coordinates of the current vertex, And the drawing the specified vertex with the Z coordinate inverted. Because the creation code only draws half a sphere, 
 glTexCoord2f(VERTEX[b].U, VERTEX[b].V);
 glVertex3f(VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);   // this loop again for the other half below
 }
// invert the V(y) texture coordinate.

  for ( b = 0; b <= VertexCount; b++)
 {
  glTexCoord2f(VERTEX[b].U, -VERTEX[b].V);
  glVertex3f(VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
  }
   glEnd();   // Then end the shape
 }
//  inpu R as the number of subdivisions, H as the translation on the horizontal axis, 
// K as the translation on the vertical axis, and Z as the translation on the Z axis
void CreateSphere(double R, double H, double K, double Z) 
{
 int n = 0;  // Set n to 0 to start off with the first vertex
 double a;  //  While a and b are used to control our loops.
 double b;
 // Assign  b loop to go through 90 degrees in intervals of the variable space
 for( b = 0; b <= 90 - space; b+=space)
 {
	 // Assign  a loop to go through 360 degrees in intervals of the variable space
      for( a = 0; a <= 360 - space; a+=space)
	 {
             
 VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
// used (2*b) as the texture is twice as wide as it is high. Hence 2:1. You can remove the (2*) to use a texture with the same width and height, or increase it accordingly 
 VERTEX[n].V = (2 * b) / 360;    
 VERTEX[n].U = (a) / 360;
 n++;
 VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
 VERTEX[n].V = (2 * (b + space)) / 360;
 VERTEX[n].U = (a) / 360;
 n++;
 VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
 VERTEX[n].V = (2 * b) / 360;
 VERTEX[n].U = (a + space) / 360;
 n++;
 VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
 VERTEX[n].V = (2 * (b + space)) / 360;
 VERTEX[n].U = (a + space) / 360;
 n++;
   }
  }
 }
 void display(void)
{
     glClearDepth(1);
     glClearColor(0.0,0.0,0.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity(); 
     glTranslatef(0,0,-10);
     glRotatef(angle,0,1,0);
     DisplaySphere(5, texture[0]);   // To display the sphere funtion which will set the size of it to 5 and assign the texture specified. it inputs the radius and texture

     glutSwapBuffers();
	 angle ++;
 }
void init(void) 
{
 glEnable(GL_DEPTH_TEST);          // enabling depth testing, texturing and face culling
 glEnable(GL_TEXTURE_2D);          // set the front face for culling to Counter Clock Wise, as triangle strips cull the opposite face to most other shapes.
 glDepthFunc(GL_LEQUAL);
 glCullFace(GL_BACK);
 glFrontFace(GL_CCW);
 glEnable(GL_CULL_FACE);
 texture[0] = LoadTextureRAW( "earth2004.raw" );   // load our texture to be used. It will be stored in texture[0]
 CreateSphere(70,0,0,0);
 }
 void reshape(int w, int h)
 {
      glViewport(0, 0, (GLsizei)w, (GLsizei)h);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
      glMatrixMode(GL_MODELVIEW);
 }
 int main(int argc, char **argv) 
{
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
      glutInitWindowSize(500, 500);
      glutInitWindowPosition(100, 100);
      glutCreateWindow("OpenGL Earth 2004 ");
      init();
      glutDisplayFunc(display);
      glutIdleFunc(display);
      glutReshapeFunc(reshape);
      glutMainLoop();
      return 0;
 }
GLuint LoadTextureRAW( const char *filename )
 {
   GLuint texture;
   int width, height;
   unsigned char *data;
   FILE *file;
   file = fopen( filename, "rb" );
    if ( file == NULL ) 
	   return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *) malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );
    glGenTextures( 1, &texture ); 
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data );
   return texture;
   } 
