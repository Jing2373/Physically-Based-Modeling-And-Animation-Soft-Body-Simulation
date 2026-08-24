#pragma once
#include "GISolverBase.h"
#include "SoftBodyStateData.h"

namespace pba
{
    class AdvancePosition : public GISolverBase
    {
    public:
        AdvancePosition(SoftBodyState pq);
        ~AdvancePosition() {}

        void init() override {}
        void solve(const double dt);

    private:
        SoftBodyState PQ;
    };

    GISolver make_advance_position(SoftBodyState pq);
}
