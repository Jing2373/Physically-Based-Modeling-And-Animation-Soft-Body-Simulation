#pragma once
#include <memory>
#include "Vector.h"
#include <vector>

namespace pba
{

    class DynamicalStateData
    {
    public:
        // count
        std::size_t nb() const { return positions.size(); }

        // position
        const Vector &pos(std::size_t i) const { return positions[i]; }
        void set_pos(std::size_t i, const Vector &p) { positions[i] = p; }

        // velocity
        const Vector &vel(std::size_t i) const { return velocities[i]; }
        void set_vel(std::size_t i, const Vector &v) { velocities[i] = v; }

        // acceleration
        const Vector &accel(std::size_t i) const { return accelerations[i]; }
        void set_accel(std::size_t i, const Vector &a) { accelerations[i] = a; }

        // mass
        float mass(size_t i) const { return masses[i]; }
        void set_mass(size_t i, float m) { masses[i] = m; }

        void add(const Vector &p, const Vector &v, float m)
        {
            positions.push_back(p);
            velocities.push_back(v);
            accelerations.push_back(Vector(0.0, 0.0, 0.0));
            masses.push_back(m);
        }

        void clear()
        {
            positions.clear();
            velocities.clear();
            accelerations.clear();
            masses.clear();
        }

    private:
        std::vector<Vector> positions;
        std::vector<Vector> velocities;
        std::vector<Vector> accelerations;
        std::vector<float> masses;
    };

    using ParticleState = std::shared_ptr<DynamicalStateData>;

}
