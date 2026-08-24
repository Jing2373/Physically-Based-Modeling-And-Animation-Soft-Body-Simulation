#include <fstream>
#include <array>
#include <sstream>
#include "PbaViewer.h"
#include "MyScene.h"
#include "MyMainBody.h"
#include "Force.h"
#include "PhysicsSystem.h"

using namespace std;

//==============================================
void LoadObj(pba::PbaThing mainBody,
             pba::PbaThing scene);

void ParseObj(const string &path,
              vector<pba::Vector> &out_vertices,
              vector<array<int, 3>> &out_faces);
//===============================================

int main(int argc, char **argv)
{
   vector<string> args;
   for (int i = 0; i < argc; i++)
   {
      args.push_back(argv[i]);
   }

   pba::PbaViewer *viewer = pba::CreateViewer();

   // Physics System
   auto physics_system = std::make_shared<pba::PhysicsSystem>();
   // Force
   pba::PbaThing force = pba::CreateForce();
   auto force_ptr = std::static_pointer_cast<pba::Force>(force);
   viewer->AddThing(force);

   // Soft Body
   pba::PbaThing mainBody = pba::CreateMyMainBody();
   auto mainbody_ptr = std::static_pointer_cast<pba::MyMainBody>(mainBody);
   mainbody_ptr->SetPhysicsSystem(physics_system);
   mainbody_ptr->SetForce(force_ptr);
   viewer->AddThing(mainBody);

   // Sphere
   pba::PbaThing myscene = pba::CreateMyScene();
   viewer->AddThing(myscene);

   LoadObj(mainBody, myscene);

   viewer->Init(args);
   viewer->MainLoop();
}

void LoadObj(pba::PbaThing mainBody, pba::PbaThing scene)
{
   // Sphere
   vector<pba::Vector> sphere_vertices;
   vector<array<int, 3>> sphere_face;
   ParseObj("models/bigsphere.obj", sphere_vertices, sphere_face);
   for (auto &v : sphere_vertices)
   {
      v *= 0.3;
   }
   auto scene_ptr = static_pointer_cast<pba::MyScene>(scene);
   scene_ptr->SetData(sphere_vertices, sphere_face);

   // Bunny
   vector<pba::Vector> bunny_vertices;
   vector<array<int, 3>> bunny_face;
   ParseObj("models/bunny_superlo_scaled.obj", bunny_vertices, bunny_face);
   for (auto &v : bunny_vertices)
   {
      v *= 5.0;
   }
   auto mainbody_ptr = static_pointer_cast<pba::MyMainBody>(mainBody);

   mainbody_ptr->SetData(bunny_vertices, bunny_face);
   mainbody_ptr->SetCollisionData(sphere_vertices, sphere_face);
}

void ParseObj(const string &path,
              vector<pba::Vector> &out_vertices,
              vector<array<int, 3>> &out_faces)
{
   ifstream in(path);
   string line;

   while (getline(in, line))
   {
      stringstream stream(line);
      string type;
      stream >> type;

      if (type == "v")
      {
         float x, y, z;
         stream >> x >> y >> z;
         out_vertices.push_back(pba::Vector(x, y, z));
      }
      else if (type == "f")
      {
         int a, b, c;
         stream >> a >> b >> c;
         out_faces.push_back({a - 1, b - 1, c - 1});
      }
   }
}
