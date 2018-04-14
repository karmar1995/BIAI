#include "GraphManager.h"

GraphNode::GraphNode(uint index)
{
    m_index = index;
}

std::pair<WeightsIterator, bool> GraphNode::putEdge(const uint index, const double weight) 
{
    return m_Weights.insert(std::pair<int, double>(index, weight));
}

std::pair<WeightsIterator, bool> GraphNode::putEdge(const GraphNode &node, const double weight) 
{
    return putEdge(node.GetIndex(), weight);
}

double GraphNode::getEdgeWeight(const uint & index) const
{
	return m_Weights.at(index);
}

uint GraphNode::GetIndex() const 
{
    return m_index;
}

std::pair<GraphMapIterator, bool> GraphManager::putNode(GraphNode node)
{
	return m_NodesMap.insert(std::make_pair(node.GetIndex(), node));
}

void GraphManager::SetMap(GraphMap newMap)
{
	m_NodesMap = newMap;
}

double GraphManager::getCostForTrace(GenesVector trace) const
{
	double retVal = 0.0;
	for (GenesIterator it = trace.begin(); it < (trace.end()-1); ++it)
	{
		retVal += m_NodesMap.at(*it).getEdgeWeight(*(it+1));
	}
	return retVal;
}
