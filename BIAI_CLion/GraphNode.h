//
// Created by root on 05.04.18.
//

#ifndef BIAI_GRAPHNODE_H
#define BIAI_GRAPHNODE_H

#include <map>
#include <set>
typedef unsigned int uint;

class GraphNode {
    static long long m_numberOfNodes=0;
    uint m_index;
    std::map<int, double> m_Edges; //key is an index of neighbour, value - the weight of edge
    std::set<GraphNode> m_Neighbours;

public:
    explicit GraphNode(uint index=0);
    std::pair<bool, auto> putNeighbour(const GraphNode& node);
    std::pair<bool, auto> putEdge(const uint index, const double weight);
    std::pair<bool, auto> putEdge(const GraphNode& node, const double weight);
    uint GetIndex() const;



};


#endif //BIAI_GRAPHNODE_H
