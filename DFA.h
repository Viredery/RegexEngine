#ifndef DFA_H
#define DFA_H

#include "NFA.h"
#include <set>
#include <queue>
#include <map>
using namespace std;

class Transfer
{
public:
	Transfer(int e, char ele);
	int end;
	char element;
};


class DFA
{
public:
	vector< map<char,int> > dfa;
	set<int> accepted_state;
	vector< set<State *> > e_state_set;
	set<char> element;
	DFA(set<char> e);
	void subset_construction(NFA_state *nfa);
	
/*最小化DFA
	void Hopcroft();
	vector< set<int> > split(vector< set<int> >::iterator p);
*/
private:
	void empty_closure(State *s);
	void delta(set<State *> es, char c);
	int postion(set<State *> &p);

	queue< set<State *> > worklist;
	set<State *> equal_state;
};




#endif
