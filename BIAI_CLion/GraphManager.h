//
// Created by root on 05.04.18.
//

#ifndef BIAI_GRAPHNODE_H
#define BIAI_GRAPHNODE_H

#include <map>
#include <set>
#include "IGeneticOperator.h"
typedef unsigned int uint;


class GraphNode;
class GraphManager;

typedef std::map<uint, double> WeightMap; //key is an index of neighbour, value - the weight of edge
typedef WeightMap::iterator WeightsIterator;
typedef std::map<uint, GraphNode> GraphMap; 
typedef GraphMap::iterator GraphMapIterator;

class GraphFileParser
{
	std::string m_filepath;
public:
	explicit GraphFileParser(std::string filepath) : m_filepath(filepath) {}
	GraphMap ParseFile();
};

class GraphNode {
    uint m_index;
	WeightMap m_Weights; //key is an index of neighbour, value - the weight of edge
public:
	GraphNode();
	explicit GraphNode(uint index);
    std::pair<WeightsIterator, bool> putEdge(const uint index, const double weight);
    std::pair<WeightsIterator, bool> putEdge(const GraphNode& node, const double weight);
	double getEdgeWeight(const uint& index) const;
    uint GetIndex() const;
	void SetIndex(uint index);
};

class GraphManager{
	GraphMap m_NodesMap;
public:
	std::pair<GraphMapIterator, bool> putNode(GraphNode node);
	void SetMap(GraphMap newMap);
	double getCostForTrace(GenesVector trace) const;
};

#endif //BIAI_GRAPHNODE_H