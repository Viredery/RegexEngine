#ifndef STATE_EDGE_POOL_H_
#define STATE_EDGE_POOL_H_

#include <list>
#include <string>
#include <array>
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
    void assignIn(Edge *e);
    void assignOut(Edge *e);
    void assignIn(std::initializer_list<Edge*> el);
    void assignOut(std::initializer_list<Edge*> el);
    void setFinished();
};

class Edge {
public:
    explicit Edge(const std::array<bool, 128>& arr);
    explicit Edge(const int t);
    Edge() = default;
    std::array<bool, 128> elementArr;
    State* start;
    State* end;
    bool epsilon = true;
    int type = 0;
    void assign(State* start, State* end);
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
	Edge* emplace_back(const std::array<bool, 128>& arr);
    Edge* emplace_back(const int t);
private:
	std::list<Edge*> edgeList;
};


} // namespace Regex

#endif // STATE_EDGE_POOL_H_