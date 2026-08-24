#pragma once
#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"
#include "Force.h"
#include "GISolverBase.h"
#include <memory>
namespace pba
{
    class PhysicsSystem
    {
    public:
        PhysicsSystem();
        ~PhysicsSystem();

        void Init(SoftBodyState pq, std::shared_ptr<pba::Force> f, double _dt);
        void Reset();
        void Solve();

    private:
        pba::SoftBodyState softbody;
        double dt;
        GISolver leap_frog_6;
        std::shared_ptr<pba::Force> force_ptr;
    };
}
