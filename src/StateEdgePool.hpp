#ifndef STATE_EDGE_POOL_H_
#define STATE_EDGE_POOL_H_

#include <list>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <initializer_list>
class State;
class Edge;

class State {
public:
	State() = default;
    std::list<Edge *> inEdges;
    std::list<Edge *> outEdges;
    bool finalState = false;
    void assignIn(Edge *e) {
        inEdges.push_back(e);
    }
    void assignOut(Edge *e) {
        outEdges.push_back(e);
    }
    void assignIn(std::initializer_list<Edge*> el) {
        for (auto e : el)
            inEdges.push_back(e);
    }
    void assignOut(std::initializer_list<Edge*> el) {
        for (auto e : el)
            outEdges.push_back(e);
    }
    void setFinished() {
        finalState = true;
    }
};

class Edge {
public:
    explicit Edge(const std::string& s): elementSet(s), empty(false) {}
    Edge() = default;
    std::bitset<128> elementSet;
    State* start;
    State* end;
    bool epsilon = true;

    void assign(State* start, State* end) {
    	this->start = start;
    	this->end = end;
    }
};

class StateManagement {
public:
	StateManagement() = default;
	~StateManagement() {
		std::for_each(stateList.begin(), stateList.end(), 
		        [](State* s){delete s;});
		stateList.clear();
	}
    State* emplace_back() {
    	State *s = new State();
    	stateList.push_back(s);
    	return s;
    }
private:
	std::list<State*> stateList;
};


class EdgeManagement {
public:
	EdgeManagement() = default;
	~EdgeManagement() {
		std::for_each(edgeList.begin(), edgeList.end(), 
		        [](Edge* e){delete e;});
		edgeList.clear();
	}
	Edge* emplace_back() {
        Edge *e = new Edge();
        edgeList.push_back(e);
        return e;
	}
	Edge* emplace_back(const std::string& s) {
        Edge *e = new Edge(s);
        edgeList.push_back(e);
        return e;
	}
private:
	std::list<Edge*> edgeList;
};


#endif

