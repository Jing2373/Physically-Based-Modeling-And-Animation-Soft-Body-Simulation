#include "AdvanceVelocity.h"
#include <memory>
#include <iostream>

namespace pba
{
    AdvanceVelocity::AdvanceVelocity(SoftBodyState pq, std::shared_ptr<pba::Force> f) : PQ(pq), force(f)
    {
    }

    void AdvanceVelocity::solve(const double dt)
    {
        for (size_t i = 0; i < PQ->nb(); i++)
        {
            PQ->set_accel(i, Vector(0, 0, 0));
        }

        force->Compute(PQ, dt);

        for (size_t i = 0; i < PQ->nb(); i++)
        {
            PQ->set_vel(i, PQ->vel(i) + PQ->accel(i) * dt);
        }
    }

    GISolver make_advance_velocity(SoftBodyState pq, std::shared_ptr<Force> f)
    {
        return std::make_shared<AdvanceVelocity>(pq, f);
    }
}
