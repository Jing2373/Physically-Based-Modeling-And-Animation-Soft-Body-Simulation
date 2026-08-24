#include <array>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include "MyMainBody.h"
#include "PhysicsSystem.h"
#include "Force.h"
namespace pba
{
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;

    MyMainBody::MyMainBody(const string nam) : PbaThingyDingy(nam)
    {
        Reset();
        cout << name << " constructed\n"
             << endl;
    }

    MyMainBody::~MyMainBody() {}

    void MyMainBody::Init(const vector<string> &args)
    {
        dt = 0.01;
        softbody = SoftBodyState(new SoftBodyStateData("bunny"));

        for (size_t i = 0; i < vertices.size(); i++)
        {
            float random_x = ((float)rand() / RAND_MAX - 0.5) * 2;
            float random_y = ((float)rand() / RAND_MAX - 0.5) * 2;
            float random_z = ((float)rand() / RAND_MAX - 0.5) * 2;
            softbody->add(vertices[i], Vector(random_x, random_y, random_z), 1.0);
            initial_positions.push_back(vertices[i]);
        }
        for (size_t i = 0; i < vertices.size(); i++)
        {
            for (size_t j = i + 1; j < vertices.size(); j++)
            {
                softbody->add_pair(i, j);
            }
        }

        physics_ptr->Init(softbody, force_ptr, dt);
    }

    void MyMainBody::Display()
    {
        glPushMatrix();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1.0f);
        glColor4f(1.0f, 0.7f, 0.7f, 0.6f);

        glBegin(GL_TRIANGLES);
        for (auto &face : faces)
        {
            Vector v0 = softbody->pos(face[0]);
            Vector v1 = softbody->pos(face[1]);
            Vector v2 = softbody->pos(face[2]);

            glVertex3f(v0.X(), v0.Y(), v0.Z());
            glVertex3f(v1.X(), v1.Y(), v1.Z());
            glVertex3f(v2.X(), v2.Y(), v2.Z());
        }
        glEnd();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
    }

    void MyMainBody::Keyboard(unsigned char key, int x, int y)
    {
        PbaThingyDingy::Keyboard(key, x, y);
    }

    void MyMainBody::solve()
    {
        if (physics_ptr)
            physics_ptr->Solve();

        float radius = 0.0f;
        for (const auto &v : collision_vertices)
        {
            radius = std::max(radius, (float)v.magnitude());
        }

        float restitution = 0.8f;
        for (size_t i = 0; i < softbody->nb(); i++)
        {
            Vector p = softbody->pos(i);
            float dist = p.magnitude();

            if (dist > radius)
            {
                Vector n = p.unitvector();
                softbody->set_pos(i, n * radius);

                Vector v = softbody->vel(i);
                double v_dot_n = v * n;

                if (v_dot_n > 0)
                {
                    Vector v_reflected = v - n * (v_dot_n * (1.0f + restitution));
                    softbody->set_vel(i, v_reflected * 0.95);
                }
            }
        }
    }

    void MyMainBody::Reset()
    {
        if (!softbody || initial_positions.empty())
        {
            return;
        }

        for (size_t i = 0; i < softbody->nb(); i++)
        {
            softbody->set_pos(i, initial_positions[i]);

            float random_x = ((float)rand() / RAND_MAX - 0.5) * 2;
            float random_y = ((float)rand() / RAND_MAX - 0.5) * 2;
            float random_z = ((float)rand() / RAND_MAX - 0.5) * 2;
            softbody->set_vel(i, Vector(random_x, random_y, random_z));
            softbody->set_accel(i, pba::Vector(0, 0, 0));
        }
        physics_ptr->Reset();
    }

    PbaThing CreateMyMainBody()
    {
        return PbaThing(new MyMainBody());
    }
}
