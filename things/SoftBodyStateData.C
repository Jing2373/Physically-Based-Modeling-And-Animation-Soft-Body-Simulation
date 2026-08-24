
#include "SoftBodyStateData.h"

namespace pba
{

    SoftBodyStateData::SoftBodyStateData(const std::string &nam)
        : DynamicalStateData()
    {
    }

    SoftBodyStateData::~SoftBodyStateData()
    {
    }

    SoftBodyStateData::SoftBodyStateData(const SoftBodyStateData &d)
        : DynamicalStateData(d),
          connected_pairs(d.connected_pairs)
    {
    }

    // copy
    SoftBodyStateData &SoftBodyStateData::operator=(const SoftBodyStateData &d)
    {
        if (this != &d)
        {
            DynamicalStateData::operator=(d);
            connected_pairs = d.connected_pairs;
        }
        return *this;
    }

    void SoftBodyStateData::add_pair(size_t i, size_t j)
    {
        Vector dx = pos(i) - pos(j);
        double L = dx.magnitude();

        connected_pairs.push_back(
            SoftEdge(new SoftEdgeData(i, j, L)));
    }

}
