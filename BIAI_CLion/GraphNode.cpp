#include "GraphNode.h"

GraphNode::GraphNode(uint index) {
    if(index==0)
        index = ++m_numberOfNodes;
    m_index = index;
}

std::pair<bool, auto> GraphNode::putNeighbour(const GraphNode &node) {
    return m_Neighbours.insert(node);
}

std::pair<bool, auto> GraphNode::putEdge(const uint index, const double weight) {
    return m_Edges.insert(std::pair<int, double>(index, weight));
}

std::pair<bool, auto> GraphNode::putEdge(const GraphNode &node, const double weight) {
    return std::pair<bool, auto>(node.GetIndex(), weight);
}

uint GraphNode::GetIndex() const {
    return m_index;
}
