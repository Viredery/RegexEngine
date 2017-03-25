#ifndef EPSILON_NFA_H_
#define EPSILON_NFA_H_

#include <tuple>
#include <memory>

#include "StateEdgePool.h"
#include "Node.h"

namespace Regex {


class NFA {
public:
	NFA() = default;
	~NFA() = default;
    std::list<State*>& getStateList();
    State* getState(std::shared_ptr<Node> node);
private:
	using Substate = std::tuple<State*, State*>;
    StateManagement states;
    EdgeManagement edges;
	
	NFA::Substate concat(NFA::Substate a, NFA::Substate b);
	NFA::Substate alt(NFA::Substate a, NFA::Substate b);
	NFA::Substate repeat(std::shared_ptr<Node> node, int repetition);
	NFA::Substate closureInfinite(std::shared_ptr<Node> node, bool greedy);
    NFA::Substate closureFinite(std::shared_ptr<Node> node, int repetition, bool greedy);
    NFA::Substate character(std::shared_ptr<ElementNode> node);
    NFA::Substate Thompson(std::shared_ptr<Node> node);

    State* getStartState(NFA::Substate s);
	State* getEndState(NFA::Substate s);
	NFA::Substate createSubstate(State *start, State *end);

    NFA::Substate setLoopFlag(NFA::Substate a);
    NFA::Substate setCaptureFlag(NFA::Substate a);
    NFA::Substate setPositivePrecheckFlag(NFA::Substate a);
    NFA::Substate setNegativePrecheckFlag(NFA::Substate a);
};


} // namespace Regex

#endif // EPSILON_NFA_H_