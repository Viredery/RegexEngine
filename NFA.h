#ifndef NFA_H
#define NFA_H

#include "RE_tree.h"
#define EMPTY 0

class Edge;
class State;
class Edge
{
public:
	char element;
	State *next_state;
	Edge *next_edge;
	void assign(char a, State *s, Edge *e);
};

class State
{
public:
	int state;
	Edge *edge;
	void assign(int s, Edge *e);
};

struct NFA_state
{
	State *start;
	State *end;
};

class NFA
{
public:
	NFA();
	NFA_state *Thompson(Regex_node *regex_tree);
	set<char> element;

	void delete_state_edge(State *state);
private:
	NFA_state *one_char_nfa(char a);
	NFA_state *concat(NFA_state *a, NFA_state *b);
	NFA_state *alt(NFA_state *a, NFA_state *b);
	NFA_state *closure(NFA_state *a);
	static int next_state_num;
};

#endif
