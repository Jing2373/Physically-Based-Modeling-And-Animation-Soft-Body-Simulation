#pragma once
#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"
#include "SoftBodyStateData.h"
#include "AccumulatingStrutForce.h"

namespace pba
{
    class Force : public PbaThingyDingy
    {
    public:
        Force(const std::string nam = "Force");
        ~Force();

        void Init(const std::vector<std::string> &args);
        void Keyboard(unsigned char key, int x, int y);
        void solve();
        void Reset();

        float GetGravity() { return gravity; }
        void Compute(SoftBodyState &state, double dt);

    private:
        float gravity = -1.0;
        float dt = 0.0;

        std::shared_ptr<AccumulatingStrutForce> strut_force;
    };

    pba::PbaThing CreateForce();
}
