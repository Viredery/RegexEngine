#include "EpsilonNFA.h"

namespace Regex {


NFA::Substate NFA::character(std::shared_ptr<ElementNode> node) {
	State* s1 = states.emplace_back();
	State* s2 = states.emplace_back();
	Edge* e = edges.emplace_back(node->getElementString());
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

NFA::Substate NFA::closureInfinite(NFA::Substate a) {
	State* s1 = states.emplace_back();
	State* s2 = states.emplace_back();
    Edge* e1 = edges.emplace_back();
    Edge* e2 = edges.emplace_back();
    Edge* e3 = edges.emplace_back();
    Edge* e4 = edges.emplace_back();
    s1->assignOut({e1, e2});
    s2->assignIn({e2, e3});
    getStartState(a)->assignIn({e1, e4});
    getEndState(a)->assignOut({e3, e4});
    e1->assign(s1, getStartState(a));
    e2->assign(s1, s2);
    e3->assign(getEndState(a), s2);
    e4->assign(getEndState(a), getStartState(a));
    return createSubstate(s1, s2);
}

NFA::Substate NFA::closureFinite(std::shared_ptr<ClosureNode> node, NFA::Substate a) {
    State* start = nullptr;
    State* end = states.emplace_back();

    NFA::Substate preState = createSubstate(nullptr, nullptr);
    
    for (int i = node->getMinRepetition(); i != node->getMaxRepetition(); i++) {
        NFA::Substate b = Thompson(node->getLeft());
        Edge *e = edges.emplace_back();
        getEndState(b)->assignOut(e);
        end->assignIn(e);
        e->assign(getEndState(b), end);
        if (nullptr == getStartState(preState)) {
        	preState = b;
            start = getStartState(b);
        } else {
        	Edge *e = edges.emplace_back();
        	getEndState(preState)->assignOut(e);
        	getStartState(b)->assignIn(e);
        	e->assign(getEndState(preState), getStartState(b));
        	preState = b;
        }
    }

    if (nullptr != getStartState(a)) {
        Edge *e1 = edges.emplace_back();
        Edge *e2 = edges.emplace_back();
        getEndState(a)->assignOut(e1);
        end->assignIn(e1);
        e1->assign(getEndState(a), end);
        getEndState(a)->assignOut(e2);
        start->assignIn(e2);
        e2->assign(getEndState(a), start);
        start = getStartState(a);
    } else {
        Edge *e1 = edges.emplace_back();
        start->assignOut(e1);
        end->assignIn(e1);
        e1->assign(start, end);
    }

    return createSubstate(start, end);
}

NFA::Substate NFA::Thompson(std::shared_ptr<Node> node) {
	if(typeid(*node) == typeid(OrNode)) {
		NFA::Substate a = Thompson(node->getLeft());
		NFA::Substate b = Thompson(node->getRight());
		NFA::Substate c = alt(a, b);
		return c;
	} else if(typeid(*node) == typeid(CombineNode)) {
		NFA::Substate a = Thompson(node->getLeft());
		NFA::Substate b = Thompson(node->getRight());
		NFA::Substate c = concat(a, b);
		return c;
	} else if(typeid(*node) == typeid(ClosureNode)) {
		std::shared_ptr<ClosureNode> cNode = dynamic_cast<ClosureNode*>(node.get())->shared_from_this();
		NFA::Substate curSubstate = createSubstate(nullptr, nullptr);
		if (0 != cNode->getMinRepetition()) {
            curSubstate = Thompson(cNode->getLeft());
		    for (int i = 1; i != cNode->getMinRepetition(); i++)
			    curSubstate = concat(curSubstate, Thompson(cNode->getLeft()));
        }
		if (-1 == cNode->getMaxRepetition()) {
		    NFA::Substate c = closureInfinite(Thompson(cNode->getLeft()));
		    if (nullptr != getStartState(curSubstate))
		        c = concat(curSubstate, c);
		    return c;
		} else {
			NFA::Substate c = closureFinite(cNode, curSubstate);
		    return c;
		}
	} else if(typeid(*node) == typeid(ElementNode)) {
		std::shared_ptr<ElementNode> eNode = dynamic_cast<ElementNode*>(node.get())->shared_from_this();
		NFA::Substate a = character(eNode);
		return a;
	} else
		throw -1;
}

State* NFA::getState(std::shared_ptr<Node> node) {
    return getStartState(Thompson(node));
}

State* getStartState(NFA::Substate s) {
    return std::get<0>(s);
}

State* getEndState(NFA::Substate s) {
    return std::get<1>(s);
}

NFA::Substate createSubstate(State *start, State *end) {
    return std::make_tuple(start, end);
}


} // namespace Regex