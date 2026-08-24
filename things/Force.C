#include "Force.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

namespace pba
{
   using std::cout;
   using std::endl;
   using std::string;
   using std::vector;

   Force::Force(const string nam) : PbaThingyDingy(nam)
   {

      cout << name << " constructed\n"
           << endl;
   }

   Force::~Force() {}

   void Force::Init(const vector<string> &args)
   {
      gravity = -1.0;
      strut_force = std::make_shared<AccumulatingStrutForce>(20.0f, 0.5f);
   }

   void Force::Keyboard(unsigned char key, int x, int y)
   {
      PbaThingyDingy::Keyboard(key, x, y);
      if (key == 's')
      {
         float force_strength = strut_force->get_spring();
         force_strength = std::max(0.0, force_strength - 5.0);
         strut_force->set_spring(force_strength);

         cout << "force strength decrease, now is: " << force_strength << endl;
      }
      else if (key == 'S')
      {
         float force_strength = strut_force->get_spring();
         force_strength += 5.0;
         strut_force->set_spring(force_strength);

         cout << "force strength increase, now is: " << force_strength << endl;
      }
      // the strut friction should decrease/increase using the 'v' and 'V' keys.
      else if (key == 'v')
      {
         float friction = strut_force->get_friction();
         friction = std::max(0.0, friction - 0.1);
         strut_force->set_friction(friction);

         cout << "friction decrease, now is: " << friction << endl;
      }
      else if (key == 'V')
      {
         float friction = strut_force->get_friction();
         friction += 0.1f;
         strut_force->set_friction(friction);

         cout << "friction increase, now is: " << friction << endl;
      }
   }

   void Force::solve()
   {
   }

   void Force::Reset()
   {
   }

   void Force::Compute(pba::SoftBodyState &state, double dt)
   {
      for (size_t i = 0; i < state->nb(); i++)
      {
         Vector g_accel(0, gravity, 0);
         state->set_accel(i, state->accel(i) + g_accel);
      }

      strut_force->compute(state, dt);
   }

   pba::PbaThing CreateForce() { return PbaThing(new Force()); }
}