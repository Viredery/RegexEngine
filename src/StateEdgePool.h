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
    enum class Type {
        LOOP, END, POSITIVE, NEGATIVE, CAPTURE, HEAD, TAIL, WEIGHTED, NORMAL
    };
    explicit Edge(const std::array<bool, 128>& arr);
    Edge() = default;
    Edge(const bool weight);
    Edge(const Type t);
    std::array<bool, 128> elementArr;
    State* start;
    State* end;
    bool epsilon = true;
    bool weighted = false;
    Type type = Type::NORMAL;
    
    void assign(State* start, State* end);

};

class FunctionEdge: public Edge {
public:
    FunctionEdge(const Type t, State *start);
    State *subStateStart;
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
    Edge* emplace_back(const bool weight);
    Edge* emplace_back(const Edge::Type t);
    Edge* emplace_back(const Edge::Type t, State *start);
private:
	std::list<Edge*> edgeList;
};


} // namespace Regex

#endif // STATE_EDGE_POOL_H_