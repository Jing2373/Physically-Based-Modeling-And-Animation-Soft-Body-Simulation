#pragma once
#include <vector>

namespace pba
{
    class SoftEdgeData
    {
    public:
        SoftEdgeData(const size_t i, const size_t j, const double edgelength) : inode(i),
                                                                                jnode(j),
                                                                                edge_length(edgelength)
        {
        }
        ~SoftEdgeData() {}

        const size_t &get_first_node() const { return inode; }
        const size_t &get_second_node() const { return jnode; }
        const double get_edge_length() const { return edge_length; }

    private:
        size_t inode, jnode; // These are the indices of the two particles (i.e., a and b)
        double edge_length;  // This is Lab
    };
    typedef std::shared_ptr<SoftEdgeData> SoftEdge;
}