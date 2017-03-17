#ifndef EPSILON_NFA_H_
#define EPSILON_NFA_H_

#include <tuple>

#include "StateEdgePool.h"

namespace Regex {


class NFA {
public:
	NFA() = default;
	~NFA() = default;
    State* getState(std::shared_ptr<Node> node);
private:
	using Substate = std::tuple<State*, State*>;
    StateManagement states;
    EdgeManagement edges;
	
	NFA::Substate concat(NFA::Substate a, NFA::Substate b);
	NFA::Substate alt(NFA::Substate a, NFA::Substate b);
	NFA::Substate closureInfinite(NFA::Substate a);
    NFA::Substate closureFinite(std::shared_ptr<ClosureNode> node, NFA::Substate a);
    NFA::Substate character(std::shared_ptr<ElementNode> node);
    NFA::Substate Thompson(std::shared_ptr<Node> node);
        
    inline State* getStartState(NFA::Substate s);
	inline State* getEndState(NFA::Substate s);
	inline NFA::Substate createSubstate(State *start, State *end);
};


} // namespace Regex

#endif // EPSILON_NFA_H_