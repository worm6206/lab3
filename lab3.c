#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp> 

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

typedef struct
{
 float LL[4];
 float color[4];
} Vertex;
Vertex verts[6]; // triangle vertices
GLubyte tindices[6]; // triangle vertex indices
GLuint vboHandle; // a VBO that contains interleaved positions and colors
GLuint indexVBO;

int press_x, press_y; 
int release_x, release_y; 
float x_angle = 0.0; 
float y_angle = 0.0; 
float scale_size = 1; 
glm::mat4 modelM = glm::mat4(); 
int xform_mode = 0; 
float c1[4]={0.7,0,0,1};
float c2[4]={0,0.7,0,1};
float c3[4]={0,0,0.7,1};
float c4[4]={0.8,1,0,1};
float c5[4]={1,0,0.8,1};
float c6[4]={0,0.8,1,1};
float c7[4]={0.4,0.4,1,1};

float angle1=0;

#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE 2 
#define PI 3.14159265

void InitGeometry()
{
 verts[0].LL[0] = -0.5; verts[0].LL[1] = -0.5; verts[0].LL[2] = 0; verts[0].LL[3] = 1;
 verts[1].LL[0] = -0.5; verts[1].LL[1] =  0.5; verts[1].LL[2] = 0; verts[1].LL[3] = 1;
 verts[2].LL[0] =  0.5; verts[2].LL[1] =  0.5; verts[2].LL[2] = 0; verts[2].LL[3] = 1;
 verts[3].LL[0] =  0.5; verts[3].LL[1] =  0.5; verts[3].LL[2] = 0; verts[3].LL[3] = 1;
 verts[4].LL[0] =  0.5; verts[4].LL[1] = -0.5; verts[4].LL[2] = 0; verts[4].LL[3] = 1;
 verts[5].LL[0] = -0.5; verts[5].LL[1] = -0.5; verts[5].LL[2] = 0; verts[5].LL[3] = 1;

 verts[0].color[0] = 1; verts[0].color[1] = 1; verts[0].color[2] = 0; verts[0].color[3] = 1;
 verts[1].color[0] = 1; verts[1].color[1] = 1; verts[1].color[2] = 0; verts[1].color[3] = 1;
 verts[2].color[0] = 1; verts[2].color[1] = 1; verts[2].color[2] = 0; verts[2].color[3] = 1;
 verts[3].color[0] = 1; verts[3].color[1] = 0; verts[3].color[2] = 0; verts[3].color[3] = 1;
 verts[4].color[0] = 1; verts[4].color[1] = 0; verts[4].color[2] = 0; verts[4].color[3] = 1;
 verts[5].color[0] = 1; verts[5].color[1] = 0; verts[5].color[2] = 0; verts[5].color[3] = 1;
 // create triangle vertex indices.
 tindices[0] = 0; tindices[1] = 1; tindices[2] = 2;
 tindices[3] = 3; tindices[4] = 4; tindices[5] = 5;
}

void InitVBO()
{
 glGenBuffers(1, &vboHandle); // create two VBO handles, one position, one color handle
 glBindBuffer(GL_ARRAY_BUFFER, vboHandle); // bind the first handle
 glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*6, verts, GL_STATIC_DRAW); // allocate space and copy the
 // position data over
 glBindBuffer(GL_ARRAY_BUFFER, 0); // clean up

 glGenBuffers(1, &indexVBO);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*6, tindices, GL_STATIC_DRAW); // load the
 // index data
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); // clean up
 // by now, we moved the position and color data over to the graphics card. There will be no redundant data
 // copy at drawing time
} 

void draw_square(float color[3]){

  glColor3f(color[0],color[1],color[2]); 

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+0);
  
}

void draw_square2(glm::mat4 m,float color[3]){

  //glLoadMatrixf(&m[0][0]); 
  glColor3f(color[0],color[1],color[2]); 

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+0);
  
}

void draw_square3(float color[3]){

  glColor3f(color[0],color[1],color[2]); 

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+0);
  
}

void draw_circle (float r,float color[3]){
  glPushMatrix();
  glScalef(r*1.414,r*1.414,0);
  for (int i = 0; i < 360; ++i)
  {
    draw_square(color);
    glRotatef(1,0,0,1);
  }
  glPopMatrix();
}

void draw_triangle(float A1,float A2,float A3,float B1,float B2,float B3,float C1,float C2, float C3){
  glPushMatrix();
  verts[0].LL[0] = A1; verts[0].LL[1] = A2; verts[0].LL[2] = A3; verts[0].LL[3] = 1;
  verts[1].LL[0] = B1; verts[1].LL[1] = B2; verts[1].LL[2] = B3; verts[1].LL[3] = 1;
  verts[2].LL[0] = C1; verts[2].LL[1] = C2; verts[2].LL[2] = C3; verts[2].LL[3] = 1;
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*6, verts, GL_STATIC_DRAW);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (char*) NULL+0);
  InitGeometry();
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*6, verts, GL_STATIC_DRAW);
  glPopMatrix();
}

void draw_cylinder (float baser, float topr, float h, int slices, float color[3],bool center) 
{
  glPushMatrix();
  if(center) glTranslatef(0,0,h/2);

  glTranslatef(0,0,h/2);
  draw_circle(topr,color);
  glTranslatef(0,0,-h);
  draw_circle(baser,color);
  glTranslatef(0,0,h/2);
  for (int i = 0; i < slices; ++i)
  {
    //sida = 360/slices
    draw_triangle(baser*cos(i*2*PI/slices),baser*sin(i*2*PI/slices),-h/2,
                  baser*cos((i+1)*2*PI/slices),baser*sin((i+1)*2*PI/slices),-h/2,
                  topr*cos(i*2*PI/slices),topr*sin(i*2*PI/slices),h/2);

    draw_triangle(topr*cos(i*2*PI/slices),topr*sin(i*2*PI/slices),h/2,
                  topr*cos((i+1)*2*PI/slices),topr*sin((i+1)*2*PI/slices),h/2,
                  baser*cos((i+1)*2*PI/slices),baser*sin((i+1)*2*PI/slices),-h/2);
  }
  //draw_triangle(base,-1,-h/2, -1,-1,-h/2, -1,1,-h/2);



  glPopMatrix();
}

void draw_sphere(float r, int slices, int stacks, float color[3]){
  glPushMatrix();
  // glPushMatrix();

  for (int i = 0; i < stacks/2; ++i)
  {
    // std::cout<<r*sin((i+1)*(PI)/stacks)<<std::endl;
    draw_cylinder(r*cos(i*(PI)/stacks),r*cos((i+1)*(PI)/stacks),r*sin((i+1)*(PI)/stacks)-r*sin((i)*(PI)/stacks),slices,color,true);
    glTranslatef(0,0,r*sin((i+1)*(PI)/stacks)-r*sin((i)*(PI)/stacks));
  }
  glPopMatrix();
  glRotatef(180,1,0,0);
  for (int i = 0; i < stacks/2; ++i)
  {
    // std::cout<<r*sin((i+1)*(PI)/stacks)<<std::endl;
    draw_cylinder(r*cos(i*(PI)/stacks),r*cos((i+1)*(PI)/stacks),r*sin((i+1)*(PI)/stacks)-r*sin((i)*(PI)/stacks),slices,color,true);
    glTranslatef(0,0,r*sin((i+1)*(PI)/stacks)-r*sin((i)*(PI)/stacks));
  }
  glPopMatrix();
}

void draw_cube(float size, float color[3]){
  //glLoadMatrixf
  glPushMatrix();
  //glMultMatrixf(&modelM[0][0]);
  glPushMatrix();
  glPushMatrix();

  glTranslatef(0,0,-0.5);
  draw_square(color);
  glTranslatef(0,0,1);
  draw_square(color);

  glPopMatrix();
  glRotatef(90,1,0,0);
  glTranslatef(0,0,-0.5);
  draw_square(color);
  glTranslatef(0,0,1);
  draw_square(color);

  glPopMatrix();
  glRotatef(90,0,1,0);
  glTranslatef(0,0,-0.5);
  draw_square(color);
  glTranslatef(0,0,1);
  draw_square(color);

  glPopMatrix();
}

void draw_floor(){
  glPushMatrix();
  glTranslatef(0,0,-3);
  glScalef(10,10,1);
  draw_cube(1,c7);
  glPopMatrix();
}

void draw_man(){
  glPushMatrix();
    glTranslatef(0,0,4);
    draw_sphere(1.5,12,12,c1);//head
    glPushMatrix();
      glRotatef(90,1,0,0);
      glTranslatef(0,4,1.5);
      glRotatef(angle1,0,1,0);
      draw_cylinder(0.2,0.1,1,12,c4,true);//nose
      
    glPopMatrix();
    glTranslatef(0,0,1);
    draw_cylinder(2,1,4,12,c2,false);//body
    glTranslatef(1,0,-3);
    draw_cylinder(0.2,0.5,2,12,c3,false);//left foot
    glTranslatef(-2,0,0);
    draw_cylinder(0.2,0.5,2,12,c3,false);//right foot
    glTranslatef(-0.5,0,4);
    glPushMatrix();
      glRotatef(-90,0,1,0);
      draw_cylinder(0.5,0.2,1,12,c5,false);//left arm
      glTranslatef(0,0,1);
      draw_cylinder(0.2,0.2,1,12,c6,false);//left hand
    glPopMatrix();
    glTranslatef(3,0,0);
    glPushMatrix();
      glRotatef(90,0,1,0);
      draw_cylinder(0.5,0.2,1,12,c5,false);//right arm
      glTranslatef(0,0,1);
      draw_cylinder(0.2,0.2,1,12,c6,false);//right hand
    glPopMatrix();
  glPopMatrix();
}

void display()
{
  glEnable(GL_DEPTH_TEST); 
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  gluPerspective(60, 1, 0.1, 100); 

  // glLoadMatrixf(&modelM[0][0]);

  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity(); 
  gluLookAt(0,0,15 , 0,0,0, 0,1,0); 

  glRotatef(x_angle, 0,1,0);   
  glRotatef(y_angle, 1,0,0); 
  glScalef(scale_size, scale_size, scale_size); 

  glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glEnableClientState(GL_VERTEX_ARRAY); // enable the vertex array on the client side
  //glEnableClientState(GL_COLOR_ARRAY); // enable the color array on the client side
  // number of coordinates per vertex (4 here), type of the coordinates,
  // stride between consecutive vertices, and pointers to the first coordinate
  // glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ sizeof(float)*4);
  glVertexPointer(4,GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+0);

  //draw_cube(1,c1);

  //draw_cylinder(1.0f,3.0f,5.0f,12,c2);

  //draw_sphere(1,12,12,c3);

  draw_floor();

  draw_man();

  //draw_square2(modelM,cc);
  glDisableClientState(GL_VERTEX_ARRAY); 
  //glDisableClientState(GL_COLOR_ARRAY);
  glutSwapBuffers();
} 

void mymouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    press_x = x; press_y = y; 
    if (button == GLUT_LEFT_BUTTON)
      xform_mode = XFORM_ROTATE; 
   else if (button == GLUT_RIGHT_BUTTON) 
      xform_mode = XFORM_SCALE; 
  }
  else if (state == GLUT_UP) {
    xform_mode = XFORM_NONE; 
  }
}

/////////////////////////////////////////////////////////

void mymotion(int x, int y)
{
    if (xform_mode==XFORM_ROTATE) {
      x_angle += (x - press_x)/5.0; 
      if (x_angle > 180) x_angle -= 360; 
      else if (x_angle <-180) x_angle += 360; 
      press_x = x; 
     
      y_angle += (y - press_y)/5.0; 
      if (y_angle > 180) y_angle -= 360; 
      else if (y_angle <-180) y_angle += 360; 
      press_y = y; 
    }
  else if (xform_mode == XFORM_SCALE){
      float old_size = scale_size;
      scale_size *= (1+ (y - press_y)/60.0); 
      if (scale_size <0) scale_size = old_size; 
      press_y = y; 
    }
  glutPostRedisplay(); 
}

///////////////////////////////////////////////////////////////

void mykey(unsigned char key, int x, int y)
{
        switch(key) {
    case 'q': 
      exit(1);
      break;
    case 'w': 
      modelM = glm::translate(modelM, glm::vec3(0.1f, 0.0f, 0.0f)); 
      display();
      break; 
    case '1': 
      angle1+=1; 
      display();
      break; 
    case '2': 
      angle1-=1; 
      display();
      break; 
    }
}
///////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  InitGeometry();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutCreateWindow("Lab2");
  glutDisplayFunc(display);
  glutMouseFunc(mymouse); 
  glutMotionFunc(mymotion);
  glutKeyboardFunc(mykey); 
  #ifdef __APPLE__
  #else
    glewInit(); 
  #endif
  InitVBO(); 
  glutMainLoop();

}
