#ifndef STATE_EDGE_POOL_H_
#define STATE_EDGE_POOL_H_

#include <list>
#include <string>
#include <array>
#include <initializer_list>

namespace Regex {

// copy construct function

class State;
class Edge;

class State {
public:
	State() = default;
    State(bool sState, bool fState);
    std::list<Edge *> inEdges;
    std::list<Edge *> outEdges;
    bool startState = false;
    bool finalState = false;
    bool visited = false;
    bool loopNode = false;
    void setLoopNode(bool loopNode);
    bool getLoopNode();
    State *statePtr = nullptr;
    void setVisited();
    bool getVisited();
    void clearVisited();
    void assignIn(Edge *e);
    void assignOut(Edge *e);
    void assignIn(std::initializer_list<Edge*> el);
    void assignOut(std::initializer_list<Edge*> el);
    void setStarted();
    void setFinished();
    bool getStartState();
    bool getFinalState();
    void setImage(State *s);
    bool validState();
};

class Edge {
public:
    enum class Type {
        LOOP, END, POSITIVE, NEGATIVE, CAPTURE, HEAD, TAIL, NORMAL
    };
    explicit Edge(const std::array<bool, 128>& arr);
    Edge() = default;
    Edge(const bool weight);
    Edge(const Type t, const bool w = false);
    virtual Edge *copyEdge(bool w = false);
    bool epsilonEdge();
    State* start;
    State* end;

    std::array<bool, 128> elementArr;
    bool epsilon = true;
    bool weighted = false;
    Type type = Type::NORMAL;
    
    void assign(State* start, State* end);
    State *getStartState();
    State *getEndState();

    void setWeighted(bool w);
    bool getWeighted();
};

class FunctionEdge: public Edge {
public:
    FunctionEdge(const Type t, State *start);
    State *subStateStart;
    Edge *copyEdge(bool w = false) override;
};

class StateManagement {
public:
	StateManagement() = default;
	~StateManagement();
    State* emplace_back();
    std::list<State*>& getStateList();
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
    Edge* emplace_back(const Edge::Type t, bool weighted = false);
    Edge* emplace_back(const Edge::Type t, State *start);
private:
	std::list<Edge*> edgeList;
};


} // namespace Regex

#endif // STATE_EDGE_POOL_H_