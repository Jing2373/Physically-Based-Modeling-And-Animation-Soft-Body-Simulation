#pragma once
#include "GISolverBase.h"
#include "SoftBodyStateData.h"
#include "PbaThing.h"
#include "Force.h"

namespace pba
{
    class Force;
    class AdvanceVelocity : public GISolverBase
    {
    public:
        AdvanceVelocity(SoftBodyState pq, std::shared_ptr<pba::Force> f);
        ~AdvanceVelocity() {}

        void init() override {}
        void solve(const double dt);

    private:
        SoftBodyState PQ;
        std::shared_ptr<pba::Force> force;

        void compute_forces(std::shared_ptr<pba::Force> f_ptr, const float dt);
    };

    GISolver make_advance_velocity(SoftBodyState pq, std::shared_ptr<Force> f);

}
