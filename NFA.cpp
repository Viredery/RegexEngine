#include "NFA.h"

void Edge::assign(char a, State *s, Edge *e)
{
	element = a;
	next_state = s;
	next_edge = e;	
}

void State::assign(int s, bool f, Edge *e)
{
	state = s;
	end_state = f;
	edge = e;
}


int NFA::next_state_num = 0;
NFA::NFA() {}

NFA_state *NFA::one_char_nfa(char a)
{
	State *state_one = new State;
	State *state_two = new State;
	Edge *edge = new Edge;
	state_one->assign(next_state_num, false, edge);
	next_state_num++;
	state_two->assign(next_state_num, true, NULL);
	next_state_num++;
	edge->assign(a, state_two, NULL);

	NFA_state *result = new NFA_state;
	result->start = state_one;
	result->end = state_two;
	return result;
}
NFA_state *NFA::concat(NFA_state *a, NFA_state *b)
{
	a->end->end_state = false;
	Edge *edge = new Edge;
	//NFA中可接受状态没有从其出发的边，因此赋值前a->end->edge的值为NULL
	a->end->edge = edge;
	edge->assign(EMPTY, b->start, NULL);

	NFA_state *result = new NFA_state;
	result->start = a->start;
	result->end = b->end;
	return result;
}
NFA_state *NFA::alt(NFA_state *a, NFA_state *b)
{
	State *state_one = new State;
	State *state_two = new State;
	Edge *edge_one = new Edge;
	Edge *edge_two = new Edge;
	Edge *edge_three = new Edge;
	Edge *edge_four = new Edge;

	a->end->end_state = b->end->end_state = false;
	state_one->assign(next_state_num, false, edge_one);
	next_state_num++;
	state_two->assign(next_state_num, true, NULL);
	next_state_num++;
	edge_one->assign(EMPTY, a->start, edge_two);
	edge_two->assign(EMPTY, b->start, NULL);
	a->end->edge = edge_three;
	b->end->edge = edge_four;
	edge_three->assign(EMPTY, state_two, NULL);
	edge_four->assign(EMPTY, state_two, NULL);

	NFA_state *result = new NFA_state;
	result->start = state_one;
	result->end = state_two;
	return result;
}
NFA_state *NFA::closure(NFA_state *a)
{
	State *state_one = new State;
	State *state_two = new State;
	Edge *edge_one = new Edge;
	Edge *edge_two = new Edge;
	Edge *edge_three = new Edge;
	Edge *edge_four = new Edge;

	a->end->end_state = false;
	state_one->assign(next_state_num, false, edge_one);
	next_state_num++;
	state_two->assign(next_state_num, true, NULL);
	next_state_num++;
	edge_one->assign(EMPTY, a->start, edge_two);
	edge_two->assign(EMPTY, state_two, NULL);
	a->end->edge = edge_three;
	edge_three->assign(EMPTY, a->start, edge_four);
	edge_four->assign(EMPTY, state_two, NULL);

	NFA_state *result = new NFA_state;
	result->start = state_one;
	result->end = state_two;
	return result;
}
NFA_state *NFA::Thompson(Node *root)
{
	if(root->value == ALT)
	{
		NFA_state *a = Thompson(root->left);
		NFA_state *b = Thompson(root->right);
		NFA_state *c = alt(a,b);
		return c;
	}
	else if(root->value == CONCAT)
	{
		NFA_state *a = Thompson(root->left);
		NFA_state *b = Thompson(root->right);
		NFA_state *c = concat(a,b);
		return c;
	}
	else if(root->value == CLOSURE)
	{
		NFA_state *a = Thompson(root->left);
		NFA_state *c = closure(a);
		return c;
	}
	else
	{
		NFA_state *a = one_char_nfa(root->value);
		element.insert(root->value);
		return a;
	}
}
/*
int main()
{
	RE_tree re;
	Node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);

}
*/
