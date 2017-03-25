#include "CompressedNFA.h"

#include <algorithm>
#include <set>
#include <iostream>

namespace Regex {


void CompressedNFA::handle(std::list<State *> &stateList) {
	std::cout << stateList.size() << std::endl;
    for (auto st : stateList) {
    	if (st->getStartState()) 
    	{
    		State *s = new State(st->getStartState(), st->getFinalState());
    		st->setImage(s);
    		states.push_back(s);
    		continue;
    	}

    	for (auto edge : st->inEdges) {
    		if (edge->epsilonEdge())
    			continue;
    		State *s = new State();
    		st->setImage(s);
    		states.push_back(s);
            break;
    	}
    }

    for (auto st : stateList) {
    	if (!st->validState())
            continue;
        std::list<std::tuple<Edge*, bool>> nonEpsilonEdges;
        bool finalFlag = emptyClosure(st, nonEpsilonEdges);
        if (true == finalFlag)
        	st->statePtr->setFinished();
        std::for_each(stateList.begin(), stateList.end(),
        	    [](State* s){s->clearVisited();});
        constructEdge(st, nonEpsilonEdges);
    }
    std::cout << states.size() << std::endl;
    int num = 0;
    for (auto s : states) {
    	for (auto edge : s->outEdges)
    		if (edge->getWeighted())
    			num++;
    }
    std::cout << num << std::endl;
}

bool CompressedNFA::emptyClosure(State *state,  std::list<std::tuple<Edge*, bool>> &nonEpsilonEdges, bool weight) {
	bool finalFlag = false;
	if (state->getVisited())
		return finalFlag;
	state->setVisited();
	if (state->getFinalState())
		finalFlag = true;
    for (auto edge : state->outEdges) {
        if (edge->epsilonEdge()) {
        	if (true == weight || edge->getWeighted()) {
                if(true == emptyClosure(edge->getEndState(), nonEpsilonEdges, true))
                    finalFlag = true;
            } else {
                if(true == emptyClosure(edge->getEndState(), nonEpsilonEdges, false))
                    finalFlag = true;
            }
        } else
    		nonEpsilonEdges.push_back(std::make_tuple(edge, weight));
    }
    return finalFlag;
}

void CompressedNFA::constructEdge(State *state,  std::list<std::tuple<Edge*, bool>> &nonEpsilonEdges) {
    State *startState = state->statePtr;
    for (auto ne : nonEpsilonEdges) {
        Edge *e = (std::get<0>(ne))->copyEdge(std::get<1>(ne));
        startState->assignOut(e);
        (std::get<0>(ne))->getEndState()->statePtr->assignIn(e);
    	e->assign(startState, (std::get<0>(ne))->getEndState()->statePtr);
    }
}


} // namespace Regex