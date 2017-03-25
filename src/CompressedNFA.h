#ifndef COMPRESSED_NFA_H_
#define COMPRESSED_NFA_H_

#include <list>
#include <tuple>

#include "StateEdgePool.h"

namespace Regex {


class CompressedNFA {
public:
	CompressedNFA() = default;
	~CompressedNFA() = default;


    void handle(std::list<State *> &stateList);

private:
    std::list<State *> states;
    std::list<Edge *> edges;

    bool emptyClosure(State *state, std::list<std::tuple<Edge*, bool>> &nonEpsilonEdges, bool weight = false);
    void constructEdge(State *state, std::list<std::tuple<Edge*, bool>> &nonEpsilonEdges);
};


} // namespace Regex

#endif // COMPRESSED_NFA_H_