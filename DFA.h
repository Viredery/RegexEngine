#ifndef DFA_H
#define DFA_H

#include "NFA.h"
#include <set>
#include <queue>
using namespace std;

class Transfer
{
public:
	Transfer(int s, int e, char ele);
	int start;
	int end;
	char element;
};


class DFA
{
public:
	


	vector<Transfer *> record;
	vector<int> accepted_state;
	set<char> element;
	DFA(set<char> e);
	void subset_construction(NFA_state *nfa);
	
private:
	void empty_closure(State *s);
	void delta(set<State *> es, char c);
	int postion(set<State *> &p);
	vector< set<State *> > e_state_set;
	queue< set<State *> > worklist;
	set<State *> equal_state;
};




#endif
