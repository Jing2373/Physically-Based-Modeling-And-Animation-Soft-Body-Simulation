#pragma once
#include <array>
#include <vector>
#include <memory>
#include "Vector.h"
#include "PbaThing.h"
#include "SoftBodyStateData.h"

namespace pba
{
    class PhysicsSystem;
    class Force;
    class MyMainBody : public PbaThingyDingy
    {

    public:
        MyMainBody(const std::string nam = "MainBody");
        ~MyMainBody();

        void Init(const std::vector<std::string> &args);
        void Display();
        void Keyboard(unsigned char key, int x, int y);
        void solve();
        void Reset();

        void SetData(const std::vector<pba::Vector> &v, const std::vector<std::array<int, 3>> &f)
        {
            vertices = v;
            faces = f;
        }
        void SetCollisionData(const std::vector<pba::Vector> &v, const std::vector<std::array<int, 3>> &f)
        {
            collision_vertices = v;
            collision_faces = f;
        }

        void SetPhysicsSystem(std::shared_ptr<PhysicsSystem> ps) { physics_ptr = ps; }
        void SetForce(std::shared_ptr<Force> f) { force_ptr = f; }
        pba::SoftBodyState &GetSoftBodyRef() { return softbody; }

    private:
        pba::SoftBodyState softbody;

        vector<Vector> vertices;
        vector<std::array<int, 3>> faces;

        vector<Vector> collision_vertices;
        vector<std::array<int, 3>> collision_faces;

        std::shared_ptr<PhysicsSystem> physics_ptr;
        std::shared_ptr<Force> force_ptr;

        std::vector<pba::Vector> initial_positions;
    };
    pba::PbaThing CreateMyMainBody();
}