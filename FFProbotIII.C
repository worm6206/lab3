
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack> 
#include <math.h> 

using namespace std; 

#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h> 
#else 
#include <GL/glew.h> 
#include <GL/glut.h> 
#include <GL/gl.h> 
#endif

#include<glm/glm.hpp> 
#include<glm/gtx/transform.hpp> 

float vertices[] = {-.5, -0.5, 0,  
		    0.5, -0.5, 0, 
		    0.5, 0.5, 0, 
		    -0.5, 0.5, 0}; 

float Langle1, Langle2, Langle3; 
float Rangle1, Rangle2, Rangle3; 

glm::mat4 modelM = glm::mat4(1.0f); 

vector<glm::mat4> mat_list; 

/////////////////////////////////
// glut mouse control 
// 
int xform_mode = 0; 
#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE 2 

int press_x, press_y; 
int release_x, release_y; 
float z_angle = 0.0; 
float x_angle = 0.0; 
float scale_size = 1; 


/////////////////////////////////////////////////////////////////

float* transform(glm::mat4 m, float v[4]){
  float* out = new float[4]; 
  for (int i=0; i<4; i++) {
    out[i] = 0; 
    for (int k=0; k<4; k++) 
      out[i]+= m[k][i] * v[k]; 
  }
  return(out); 
}


//////////////////////////////////////////////////////////////////////////////////////////

void draw_square(glm::mat4 m, float color[3]) {

  float v_in[4]; 
  float *v_out; 

  // draw local axes 

  /*
  glBegin(GL_LINES);  //glBegin/End have been deprecated in OpenGL 3
  glColor3f(1, 0, 0); 

  v_in[0] = 0; v_in[1] = 0; v_in[2] = 0; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = 0.2; v_in[1] = 0; v_in[2] = 0; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  glColor3f(0, 0, 1); 

  v_in[0] = 0; v_in[1] = 0; v_in[2] = 0; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = 0; v_in[1] = 0.2; v_in[2] = 0; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  glEnd(); 
  */

  // now draw the square 

  glBegin(GL_TRIANGLES);  //glBegin/End have been deprecated in OpenGL 3
  glColor3f(color[0],color[1],color[2]); 
  

  v_in[0] = vertices[0]; v_in[1] = vertices[1]; v_in[2] = vertices[2]; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = vertices[3]; v_in[1] = vertices[4]; v_in[2] = vertices[5]; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = vertices[6]; v_in[1] = vertices[7]; v_in[2] = vertices[8]; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = vertices[0]; v_in[1] = vertices[1]; v_in[2] = vertices[2]; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = vertices[6]; v_in[1] = vertices[7]; v_in[2] = vertices[8]; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  v_in[0] = vertices[9]; v_in[1] = vertices[10]; v_in[2] = vertices[11]; v_in[3] = 1.0; 
  v_out = transform(m, v_in); 
  glVertex4f(v_out[0], v_out[1], v_out[2], v_out[3]); 

  glEnd(); 
} 


/////////////////////////////////////////////////////////////////

void draw_cube(glm::mat4 m, float color[3]) {

  glm::mat4 m0 = glm::translate(m, glm::vec3(0.0, 0.0, -0.5)); 
  draw_square(m0, color); 
  glm::mat4 m1 = glm::translate(m, glm::vec3(0.0, 0.0, 0.5)); 
  draw_square(m1, color); 
  glm::mat4 m2 = glm::translate(m, glm::vec3(0.0, -0.5, 0.0));
  float angle = 90; 
  m2 = glm::rotate(m2, angle, glm::vec3(1.0f,0.0f,0.0f));   
  draw_square(m2, color); 
  glm::mat4 m3 = glm::translate(m, glm::vec3(0.0, 0.5, 0.));
  m3 = glm::rotate(m3, angle, glm::vec3(1.0f,0.0f,0.0f));   
  draw_square(m3, color); 

  glm::mat4 m4= glm::translate(m, glm::vec3(-0.5, 0.0, 0.0));
  m4 = glm::rotate(m4, angle, glm::vec3(0.0f,1.0f,0.0f));   
  draw_square(m4, color); 
  glm::mat4 m5 = glm::translate(m, glm::vec3(0.5, 0.0, 0.));
  m5 = glm::rotate(m5, angle, glm::vec3(0.0f,1.0f,0.0f));   
  draw_square(m5, color); 
  
} 


void draw_robot(glm::mat4 m, float* color) {

  glm::mat4 m1; 

  //  draw_square(m, color); 
  draw_cube(m, color); 

  m1 = glm::translate(m, glm::vec3(0.5, 0.0, 0.0)); 
  m1 = glm::rotate(m1, Langle1, glm::vec3(0.0f,0.0f,1.0f));   
  m1 = glm::translate(m1, glm::vec3(0.5, 0.0, 0.0)); 
  m1 = glm::scale(m1, glm::vec3(0.9, 0.9, 0.9)); 
  m1 = glm::scale(m1, glm::vec3(1.0, 0.5, 1.0)); 

  float color1[3] = {1,1,0}; 
  //  draw_square(m1, color1); 
  draw_cube(m1, color1); 

  m1 = glm::scale(m1, glm::vec3(1.0, 2, 1.0)); 


  m1 = glm::translate(m1, glm::vec3(0.5, 0.0, 0.0)); 
  m1 = glm::rotate(m1, Langle2, glm::vec3(0.0f,0.0f,1.0f));   
  m1 = glm::translate(m1, glm::vec3(0.5, 0.0, 0.0)); 
  m1 = glm::scale(m1, glm::vec3(0.9, 0.9, 0.9)); 
  m1 = glm::scale(m1, glm::vec3(1.0, 0.5, 1.0)); 

  //  draw_square(m1, color1); 
  draw_cube(m1, color1); 

}

/////////////////////////////////////////////////////////////
void display() 
{ 

  glEnable(GL_DEPTH_TEST); 
  glClearColor(0,0,0,1); 
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

  vector <glm::mat4>::const_iterator mi;

  float color[3]; 

  // define/get the projection matrix 
  glm::mat4 projection = glm::perspective(60.0f,1.0f,.01f,100.0f); 

  // define/get the viewing matrix 
  glm::mat4 view = glm::lookAt(glm::vec3(5, 5, .2), 
                               glm::vec3(0.0, 0.0, 0.0), 
                               glm::vec3(0.0, 0.0, 1.0)); 

  // define the modeling matrix 
  glm::mat4 model = glm::mat4(1.0f); 
  model = glm::rotate(model, z_angle, glm::vec3(0.0f, 0.0f, 1.0f)); 
  model = glm::rotate(model, x_angle, glm::vec3(1.0f, 0.0f, 0.0f)); 
  model = glm::scale(model, glm::vec3(scale_size, scale_size, scale_size)); 

  // draw the floor 
  color[0] = 0.2; color[1] = 0.5; color[2] = 0.2; 
  glm::mat4 floorM = glm::translate(model, glm::vec3(0.0, 0.0, -0.55)); 
  floorM = glm::scale(floorM, glm::vec3(15.0, 15.0, 15.0)); 
  draw_square(projection*view*floorM, color); 

  // draw the robot 
  glm::mat4 modelV = model * modelM; 
  color[0] = 0; color[1] = 0; color[2] = 1; 
  draw_robot(projection*view*modelV, color); 

  // draw the squre eggs 
  color[0] = 0.5; color[1] = 0; color[2] = 0; 
  for (mi=mat_list.begin(); mi!=mat_list.end(); mi++) {
    printf(" hello!\n"); 
    modelV = model * (*mi); 
    draw_cube(projection*view*modelV, color); 
  } 
  glutSwapBuffers(); 

} 

///////////////////////////////////////////////////////////////

void mymotion(int x, int y)
{
    if (xform_mode==XFORM_ROTATE) {
      z_angle += (x - press_x)/5.0; 
      if (z_angle > 180) z_angle -= 360; 
      else if (z_angle <-180) z_angle += 360; 
      press_x = x; 
           
      x_angle -= (y - press_y)/5.0; 
      if (x_angle > 180) x_angle -= 360; 
      else if (x_angle <-180) x_angle += 360; 
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

///////////////////////////////////////////////////////////////

void mykey(unsigned char key, int x, int y)
{
        float d_angle = 10; 
	if (key == 'q') exit(1); 
	if (key == 'R') 
	  modelM = glm::rotate(modelM, d_angle, glm::vec3(0.0f, 0.0f, 1.0f)); 
	//  modelM =  rotatez(modelM, d_angle);
	if (key == 'r') 
	  modelM = glm::translate(modelM, glm::vec3(0.1f, 0.0f, 0.0f)); 
	//  modelM =  translate(modelM, .1,0,0);
	if (key == 'l') 
	  modelM = glm::translate(modelM, glm::vec3(-0.1f, 0.0f, 0.0f)); 
	//modelM =  translate(modelM, -.1,0,0);
	if (key == 'f') 
	  modelM = glm::translate(modelM, glm::vec3(0.0f, 0.1f, 0.0f)); 
	//modelM =  translate(modelM, 0,.1,0);
	if (key == 'b') 
	  modelM = glm::translate(modelM, glm::vec3(0.0f, -0.1f, 0.0f)); 
	//modelM =  translate(modelM, 0,-.1,0);
	if (key == 'c') 
	  modelM =  glm::mat4(1.0f); 

	if (key == '1') {
	  Langle1 += 5; 
	  printf(" hello!\n"); 
	}
	if (key == '2') 
	  Langle2 += 5; 
	if (key == '3') 
	  Langle3 += 5; 

	if (key == '4') 
	  Langle1 += 5; 
	if (key == '5') 
	  Langle2 += 5; 
	if (key == '6') 
	  Langle3 += 5; 

	if (key == 'p')  {
	  glm::mat4 pm = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 1.0f)); 
	  // mat4 pm = scale(modelM, 0.5, 0.5, 1.0); 
	  mat_list.push_back(pm); 
	} 

	glutPostRedisplay(); 
}

int main(int argc, char** argv) 
{ 

  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH); 
  glutInitWindowSize(600,600); 

  glutCreateWindow("fixed function pipeline: simple"); 
  glutDisplayFunc(display); 
  glutMouseFunc(mymouse); 
  glutMotionFunc(mymotion);
  glutKeyboardFunc(mykey); 

  //glewInit(); 

  Langle1 = Langle2 = Langle3 = 0; 
  Rangle1 = Rangle2 = Rangle3 = 0; 

  mat_list.clear(); 

  glutMainLoop(); 

} 
