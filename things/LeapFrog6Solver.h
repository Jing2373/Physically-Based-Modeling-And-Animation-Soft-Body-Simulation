#pragma once
#include "GISolverBase.h"

namespace pba
{
    class LeapFrog6Solver : public GISolverBase
    {
    public:
        LeapFrog6Solver(GISolver pos, GISolver vel) : position(pos), velocity(vel) {}

        void init() override
        {
            position->init();
            velocity->init();
        }

        void solve(const double dt) override
        {
            double a = 1.0 / (4.0 - std::pow(4.0, 1.0 / 3.0));
            double b = 1.0 - 4.0 * a;

            double steps[] = {a, a, b, a, a};
            for (double s : steps)
            {
                double sub_dt = s * dt;
                double dtd2 = 0.5 * sub_dt;
                position->solve(dtd2);
                velocity->solve(sub_dt);
                position->solve(dtd2);
            }
        }

    private:
        GISolver position;
        GISolver velocity;
    };
}
