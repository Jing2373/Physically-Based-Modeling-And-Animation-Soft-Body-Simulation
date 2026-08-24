#ifndef __SOFT_BODY_STATE_DATA_H__
#define __SOFT_BODY_STATE_DATA_H__

#include <vector>
#include "DynamicalStateData.h"
#include "SoftEdgeData.h"
#include "PbaThing.h"
namespace pba
{
    class SoftBodyStateData : public DynamicalStateData
    {
    public:
        SoftBodyStateData(const std::string &nam = "SoftBodyDataNoName");
        ~SoftBodyStateData();

        // copy constructor and assignment
        SoftBodyStateData(const SoftBodyStateData &d);
        SoftBodyStateData &operator=(const SoftBodyStateData &d);

        const SoftEdge &get_connected_pair(size_t p) const { return connected_pairs[p]; }

        size_t nb_pairs() const { return connected_pairs.size(); }
        bool empty() const { return connected_pairs.empty(); }

        void clear_pairs() { connected_pairs.clear(); }
        void add_pair(size_t i, size_t j);

    private:
        std::vector<SoftEdge> connected_pairs;
    };
    typedef std::shared_ptr<SoftBodyStateData> SoftBodyState;
}

#endif