#include "AdvancePosition.h"
#include <iostream>

namespace pba
{
    AdvancePosition::AdvancePosition(SoftBodyState pq) : PQ(pq) {}

    void AdvancePosition::solve(const double dt)
    {

#pragma omp parallel for
        for (std::size_t i = 0; i < PQ->nb(); i++)
        {
            PQ->set_pos(i, PQ->pos(i) + PQ->vel(i) * dt);
        }
    }

    GISolver make_advance_position(SoftBodyState pq)
    {
        return std::make_shared<AdvancePosition>(pq);
    }
}
