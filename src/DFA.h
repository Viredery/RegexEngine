#ifndef DFA_H
#define DFA_H

#include "NFA.h"
#include <set>
#include <queue>
#include <map>
using namespace std;

class DFA
{
public:
	DFA(set<char> e);
	vector< map<char,int> > dfa;
	set<int> accepted_state;

	void subset_construction(NFA_state *nfa);
private:
	void empty_closure(State *s);
	void delta(set<State *> es, char c);
	int postion(set<State *> &p);
	vector< set<State *> > e_state_set;
	set<char> element;
	queue< set<State *> > worklist;
	set<State *> equal_state;
};




#endif
