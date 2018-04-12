#include "GraphNode.h"

GraphNode::GraphNode(uint index)
{
    m_index = index;
}

std::pair<NeighboursIterator, bool> GraphNode::putNeighbour(GraphNode node) 
{
    return m_Neighbours.insert(node);
}

std::pair<EdgesIterator, bool> GraphNode::putEdge(const uint index, const double weight) 
{
    return m_Edges.insert(std::pair<int, double>(index, weight));
}

std::pair<EdgesIterator, bool> GraphNode::putEdge(const GraphNode &node, const double weight) 
{
    return putEdge(node.GetIndex(), weight);
}

uint GraphNode::GetIndex() const 
{
    return m_index;
}

bool GraphNode::operator>(const GraphNode & rhs) const
{
	return m_index>rhs.GetIndex();
}

bool GraphNode::operator<(const GraphNode & rhs) const
{
	return m_index<rhs.GetIndex();
}
