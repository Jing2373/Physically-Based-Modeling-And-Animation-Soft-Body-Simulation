#include "MyScene.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

namespace pba
{
   using std::string;
   using std::vector;

   MyScene::MyScene(const string nam) : PbaThingyDingy(nam)
   {
      Reset();
      std::cout << name << " constructed\n"
                << std::endl;
   }

   MyScene::~MyScene() {}

   void MyScene::Init(const vector<string> &args)
   {
   }

   void MyScene::Display()
   {
      glPushMatrix();

      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glLineWidth(2.0f);
      glColor4f(0.5f, 0.5f, 0.5f, 0.5f);

      glBegin(GL_TRIANGLES);
      for (auto &face : faces)
      {
         Vector v0 = vertices[face[0]];
         Vector v1 = vertices[face[1]];
         Vector v2 = vertices[face[2]];

         glVertex3f(v0.X(), v0.Y(), v0.Z());
         glVertex3f(v1.X(), v1.Y(), v1.Z());
         glVertex3f(v2.X(), v2.Y(), v2.Z());
      }
      glEnd();

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glPopMatrix();
   }

   void MyScene::Reset() {}

   PbaThing CreateMyScene()
   {
      return PbaThing(new MyScene());
   }
}