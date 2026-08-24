#include "SoftBodyStateData.h"
#include "SoftEdgeData.h"
#include "ForceBase.h"
#include "Vector.h"

namespace pba
{
    class AccumulatingStrutForce : public pba::ForceBase
    {
    public:
        AccumulatingStrutForce(const float g, const float f) : spring(g), friction(f) {}
        ~AccumulatingStrutForce() {};

        void compute(pba::SoftBodyState &pq, const float dt)
        {
            for (size_t i = 0; i < pq->nb_pairs(); i++)
            {
                const pba::SoftEdge &se = pq->get_connected_pair(i);
                const size_t &inode = se->get_first_node();
                const size_t &jnode = se->get_second_node();
                Vector dx = pq->pos(inode) - pq->pos(jnode);
                Vector ff = pq->vel(inode) - pq->vel(jnode);
                Vector F;
                float separation = dx.magnitude() - se->get_edge_length();
                dx.normalize();
                F = dx * (separation * spring);
                F += dx * (dx * ff) * friction;
                pq->set_accel(jnode, pq->accel(jnode) + F / pq->mass(jnode));
                pq->set_accel(inode, pq->accel(inode) - F / pq->mass(inode));
            }
        };

        void set_spring(float s)
        {
            spring = s;
        }
        float get_spring()
        {
            return spring;
        }
        void set_friction(float f)
        {
            friction = f;
        }
        float get_friction()
        {
            return friction;
        }

    private:
        float spring;
        float friction;
    };
}
