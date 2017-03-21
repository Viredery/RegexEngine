#include "EpsilonNFA.h"
#include "iostream"

#include "Node.h"

namespace Regex {


NFA::Substate NFA::character(std::shared_ptr<ElementNode> node) {
	State* s1 = states.emplace_back();
	State* s2 = states.emplace_back();
	Edge* e = edges.emplace_back(node->getElementArray());
	e->assign(s1, s2);
	s1->assignOut(e);
	s2->assignIn(e);
	return createSubstate(s1, s2);
}

NFA::Substate NFA::concat(NFA::Substate a, NFA::Substate b) {
	Edge* e = edges.emplace_back();
	e->assign(getEndState(a), getStartState(b));
	getStartState(b)->assignIn(e);
	getEndState(a)->assignOut(e);
	return createSubstate(getStartState(a), getEndState(b));
}

NFA::Substate NFA::alt(NFA::Substate a, NFA::Substate b) {
	State* s1 = states.emplace_back();
	State* s2 = states.emplace_back();
    Edge* e1 = edges.emplace_back();
    Edge* e2 = edges.emplace_back();
    Edge* e3 = edges.emplace_back();
    Edge* e4 = edges.emplace_back();
    s1->assignOut({e1, e2});
    s2->assignIn({e3, e4});
    getStartState(a)->assignIn(e1);
    getStartState(b)->assignIn(e2);
    getEndState(a)->assignOut(e3);
    getEndState(b)->assignOut(e4);
    e1->assign(s1, getStartState(a));
    e2->assign(s1, getStartState(b));
    e3->assign(getEndState(a), s2);
    e4->assign(getEndState(b), s2);
    return createSubstate(s1, s2);
}

NFA::Substate NFA::repeat(std::shared_ptr<Node> node, int repetition) {
    NFA::Substate curSubState = Thompson(node->getLeft());
    for (int i = 1; i < repetition; i++)
        curSubState = concat(curSubState, Thompson(node->getLeft()));
    if (nullptr == getStartState(curSubState)) {
        State* s1 = states.emplace_back();
        State* s2 = states.emplace_back();
        Edge* e = edges.emplace_back();
        e->assign(s1, s2);
        s1->assignOut(e);
        s2->assignIn(e);
        curSubState = createSubstate(s1, s2);
    }
    return curSubState;
}

NFA::Substate NFA::closureInfinite(std::shared_ptr<Node> node) {
    NFA::Substate a = Thompson(node->getLeft());
	State* s = states.emplace_back();
    Edge* e1 = edges.emplace_back();
    Edge* e2 = edges.emplace_back();
    s->assignOut(e1);
    s->assignIn(e2);
    getStartState(a)->assignIn(e1);
    getEndState(a)->assignOut(e2);
    e1->assign(s, getStartState(a));
    e2->assign(getEndState(a), s);
    return createSubstate(s, s);
}

NFA::Substate NFA::closureFinite(std::shared_ptr<Node> node, int repetition) {
    State *startState = nullptr, *endState = states.emplace_back(), *preEndState = nullptr;
    for (int i = 0; i != repetition; i++) {
        NFA::Substate a = Thompson(node->getLeft());
        Edge *e = edges.emplace_back();
        getEndState(a)->assignOut(e);
        endState->assignIn(e);
        e->assign(getEndState(a), endState);
        if (nullptr == startState) {
            startState = getStartState(a);
        	preEndState = getEndState(a);
        } else {
        	Edge *e = edges.emplace_back();
        	preEndState->assignOut(e);
        	getStartState(a)->assignIn(e);
        	e->assign(preEndState, getStartState(a));
        	preEndState = getEndState(a);
        }
    }
    return createSubstate(startState, endState);
}

NFA::Substate NFA::Thompson(std::shared_ptr<Node> node) {
	if(typeid(*node) == typeid(OrNode)) {
		NFA::Substate a = Thompson(node->getLeft());
		NFA::Substate b = Thompson(node->getRight());
		return alt(a, b);
	} else if(typeid(*node) == typeid(CombineNode)) {
		NFA::Substate a = Thompson(node->getLeft());
		NFA::Substate b = Thompson(node->getRight());
		return concat(a, b);
	} else if(typeid(*node) == typeid(ClosureNode)) {
		std::shared_ptr<ClosureNode> cNode = dynamic_cast<ClosureNode*>(node.get())->shared_from_this();
        int minRepetition = cNode->getMinRepetition(), maxRepetition = cNode->getMaxRepetition();
        NFA::Substate a = repeat(node, minRepetition);
        if (minRepetition == maxRepetition)
            return a;
        NFA::Substate b = (maxRepetition == -1) ? closureInfinite(node) : 
                closureFinite(node, maxRepetition - minRepetition);
        NFA::Substate c = concat(a, b);
        if (maxRepetition != -1) {
            Edge *e = edges.emplace_back();
            e->assign(getEndState(a), getEndState(b));
            getEndState(a)->assignOut(e);
            getEndState(b)->assignIn(e);
        }
        return setLoopFlag(c);
	} else if(typeid(*node) == typeid(ElementNode)) {
		std::shared_ptr<ElementNode> eNode = dynamic_cast<ElementNode*>(node.get())->shared_from_this();
		return character(eNode);
	} else
		throw -1;
}

State* NFA::getState(std::shared_ptr<Node> node) {
    return getStartState(Thompson(node));
}

State* NFA::getStartState(NFA::Substate s) {
    return std::get<0>(s);
}

State* NFA::getEndState(NFA::Substate s) {
    return std::get<1>(s);
}

NFA::Substate NFA::createSubstate(State *start, State *end) {
    return std::make_tuple(start, end);
}

NFA::Substate NFA::setLoopFlag(NFA::Substate a) {
    State* s1 = states.emplace_back();
    State* s2 = states.emplace_back();
    Edge* e1 = edges.emplace_back(Edge::Type::LOOP);
    Edge* e2 = edges.emplace_back(Edge::Type::END);
    s1->assignOut(e1);
    s2->assignIn(e2);
    getStartState(a)->assignIn(e1);
    getEndState(a)->assignOut(e2);
    e1->assign(s1, getStartState(a));
    e2->assign(getEndState(a), s2);
    return createSubstate(s1, s2);
}


} // namespace Regex