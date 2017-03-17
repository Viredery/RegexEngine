#ifndef STATE_EDGE_POOL_H_
#define STATE_EDGE_POOL_H_

#include <list>
#include <string>
#include <bitset>
#include <initializer_list>

namespace Regex {


class State;
class Edge;

class State {
public:
	State() = default;
    std::list<Edge *> inEdges;
    std::list<Edge *> outEdges;
    bool finalState = false;
    inline void assignIn(Edge *e);
    inline void assignOut(Edge *e);
    inline void assignIn(std::initializer_list<Edge*> el);
    inline void assignOut(std::initializer_list<Edge*> el);
    inline void setFinished();
};

class Edge {
public:
    explicit Edge(const std::string& s);
    Edge() = default;
    std::bitset<128> elementSet;
    State* start;
    State* end;
    bool epsilon = true;
    inline void assign(State* start, State* end);
};

class StateManagement {
public:
	StateManagement() = default;
	~StateManagement();
    State* emplace_back();
private:
	std::list<State*> stateList;
};

class EdgeManagement {
public:
	EdgeManagement() = default;
	~EdgeManagement();
	Edge* emplace_back();
	Edge* emplace_back(const std::string& s);
private:
	std::list<Edge*> edgeList;
};


} // namespace Regex

#endif // STATE_EDGE_POOL_H_