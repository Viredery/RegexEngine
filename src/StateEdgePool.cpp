#include "StateEdgePool.h"

#include <algorithm>
#include <exception>

namespace Regex {


State::State(bool sState, bool fState):
        startState(sState), finalState(fState) {}

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

void State::setVisited() {
    visited = true;
}

bool State::getVisited() {
    return visited;
}

void State::clearVisited() {
    visited = false;
}

void State::setStarted() {
    startState = true;
}

void State::setFinished() {
    finalState = true;
}

bool State::getStartState() {
    return startState;
}

bool State::getFinalState() {
    return finalState;
}

void State::setImage(State *s) {
    statePtr = s;
}

bool State::validState() {
    return nullptr != statePtr; 
}

void State::setLoopNode(bool ln) {
    loopNode = ln;
}

bool State::getLoopNode() {
    return loopNode;
}


Edge::Edge(const std::array<bool, 128>& arr):
        epsilon(false) {
    std::copy(arr.begin(), arr.end(), elementArr.begin()); 
}

Edge::Edge(const bool w):
        weighted(w) {}

Edge::Edge(const Type t, const bool w):
        type(t), weighted(w) {}

void Edge::assign(State* start, State* end) {
	this->start = start;
	this->end = end;
}

Edge *Edge::copyEdge(bool w) {
    Edge *res;
    if (Type::NORMAL == type && true == epsilon)
        res = new Edge();
    else if (Type::NORMAL == type && false == epsilon)
        res = new Edge(this->elementArr);
    else
        res = new Edge(this->type);
    res->setWeighted(w || this->weighted);
    return res;
}

void Edge::setWeighted(bool w) {
    weighted = w;
}

bool Edge::getWeighted() {
    return weighted;
}

bool Edge::epsilonEdge() {
    return Edge::Type::NORMAL == this->type && true == this->epsilon;
}

State *Edge::getStartState() {
    return start;
}

State *Edge::getEndState() {
    return end;
}

FunctionEdge::FunctionEdge(Type t, State *start):
    Edge(t), subStateStart(start) {}

Edge *FunctionEdge::copyEdge(bool w) {
    Edge *res;
    if (nullptr != this->subStateStart->statePtr)
        res = new FunctionEdge(this->type, this->subStateStart->statePtr);
    else
        throw std::logic_error("ERROR COPY");
    res->setWeighted(w);
    return res;
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

std::list<State*>& StateManagement::getStateList() {
    return stateList;
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

Edge* EdgeManagement::emplace_back(const bool weight) {
    Edge *e = new Edge(weight);
    edgeList.push_back(e);
    return e;   
}

Edge* EdgeManagement::emplace_back(const Edge::Type t, bool weighted) {
    Edge *e = new Edge(t, weighted);
    edgeList.push_back(e);
    return e;
}

Edge* EdgeManagement::emplace_back(const Edge::Type t, State *start) {
    Edge *e = new FunctionEdge(t, start);
    edgeList.push_back(e);
    return e;
}


} // namespace Regex