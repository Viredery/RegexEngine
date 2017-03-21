#include "StateEdgePool.h"

#include <algorithm>

namespace Regex {


void State::assignIn(Edge *e) {
    inEdges.push_back(e);
}

void State::assignOut(Edge *e) {
    outEdges.push_back(e);
}

void State::assignIn(std::initializer_list<Edge*> el) {
    for (auto e : el)
        inEdges.push_back(e);
}

void State::assignOut(std::initializer_list<Edge*> el) {
    for (auto e : el)
        outEdges.push_back(e);
}

void State::setFinished() {
    finalState = true;
}

Edge::Edge(const std::array<bool, 128>& arr):
        epsilon(false) {
    std::copy(arr.begin(), arr.end(), elementArr.begin()); 
}

Edge::Edge(Type t):
        type(t) {}

void Edge::assign(State* start, State* end) {
	this->start = start;
	this->end = end;
}

StateManagement::~StateManagement() {
	std::for_each(stateList.begin(), stateList.end(), 
	        [](State* s){delete s;});
	stateList.clear();
}

State* StateManagement::emplace_back() {
   	State *s = new State();
   	stateList.push_back(s);
   	return s;
}

EdgeManagement::~EdgeManagement() {
	std::for_each(edgeList.begin(), edgeList.end(), 
	        [](Edge* e){delete e;});
	edgeList.clear();
}

Edge* EdgeManagement::emplace_back() {
    Edge *e = new Edge();
    edgeList.push_back(e);
    return e;
}

Edge* EdgeManagement::emplace_back(const std::array<bool, 128>& arr) {
    Edge *e = new Edge(arr);
    edgeList.push_back(e);
    return e;
}

Edge* EdgeManagement::emplace_back(Edge::Type t) {
    Edge *e = new Edge(t);
    edgeList.push_back(e);
    return e;
}


} // namespace Regex