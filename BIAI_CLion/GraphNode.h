//
// Created by root on 05.04.18.
//

#ifndef BIAI_GRAPHNODE_H
#define BIAI_GRAPHNODE_H

#include <map>
#include <set>
typedef unsigned int uint;

class GraphNode;

typedef std::set<GraphNode>::iterator NeighboursIterator;
typedef std::map<int, double>::iterator EdgesIterator;

class GraphNode {
    uint m_index;
    std::map<int, double> m_Edges; //key is an index of neighbour, value - the weight of edge
    std::set<GraphNode> m_Neighbours;

public:
    explicit GraphNode(uint index=0);
	std::pair<NeighboursIterator, bool> putNeighbour(GraphNode node);
    std::pair<EdgesIterator, bool> putEdge(const uint index, const double weight);
    std::pair<EdgesIterator, bool> putEdge(const GraphNode& node, const double weight);
    uint GetIndex() const;
	bool operator > (const GraphNode& rhs) const;
	bool operator < (const GraphNode& rhs) const;

};


#endif //BIAI_GRAPHNODE_H
