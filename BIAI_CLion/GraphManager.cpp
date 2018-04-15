#include "GraphManager.h"

#include <fstream>
#include <sstream>
#include <string>

GraphNode::GraphNode()
{

}
GraphNode::GraphNode(uint index):m_index(index)
{

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

void GraphNode::SetIndex(uint index)
{
	m_index=index;
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

GraphMap GraphFileParser::ParseFile()
{
	std::fstream tsf(m_filepath, std::ios::in);
	GraphMap map;//KOLUMNY
	std::string data;
	uint index = 1;
	uint node = 1;
	if (tsf.good()) {
		std::string item;
		float weight;
		while (!tsf.eof()) {
			std::getline(tsf, data);
			std::stringstream ss(data);
			if (map.size()==0) {
				uint nodes = std::count(data.begin(), data.end(), '\t')+1;
				for(;nodes>0;nodes--)
					map[nodes] = GraphNode(nodes);
			}
			while (std::getline(ss, item, '\t')) {
				weight = std::stof(item);
				map[node].putEdge(index,weight);
				node++;
			}
			node = 1;
			index++;
		}
	}
	tsf.close();
	return map;
}
