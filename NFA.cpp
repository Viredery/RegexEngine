#include "NFA.h"
/*
     设置Edge的值
*/
void Edge::assign(char a, State *s, Edge *e)
{
	element = a;
	next_state = s;
	next_edge = e;	
}
/*
    设置State的值
*/
void State::assign(int s,  Edge *e)
{
	state = s;
	edge = e;
}


int NFA::next_state_num = 0;
NFA::NFA() {}

/*
    释放动态分配的内存,需要调用
*/
void NFA::delete_state_edge(State *state)
{
	if(state == NULL)
		return;
	Edge *p = state->edge;
	delete state;
	while(p != NULL)
	{
		delete_state_edge(p->next_state);
		Edge *p_next = p->next_edge;
		delete p;
		p = p_next;
	}
}
/*
    a
*/
NFA_state *NFA::one_char_nfa(char a)
{
	State *state_one = new State;
	State *state_two = new State;
	Edge *edge = new Edge;
	state_one->assign(next_state_num, edge);
	next_state_num++;
	state_two->assign(next_state_num, NULL);
	next_state_num++;
	edge->assign(a, state_two, NULL);

	NFA_state *result = new NFA_state;
	result->start = state_one;
	result->end = state_two;
	return result;
}
/*
    ab
*/
NFA_state *NFA::concat(NFA_state *a, NFA_state *b)
{
	Edge *edge = new Edge;
	//NFA中可接受状态没有从其出发的边，因此赋值前a->end->edge的值为NULL
	a->end->edge = edge;
	edge->assign(EMPTY, b->start, NULL);

	NFA_state *result = new NFA_state;
	result->start = a->start;
	result->end = b->end;
	return result;
}
/*
    a|b
*/
NFA_state *NFA::alt(NFA_state *a, NFA_state *b)
{
	State *state_one = new State;
	State *state_two = new State;
	Edge *edge_one = new Edge;
	Edge *edge_two = new Edge;
	Edge *edge_three = new Edge;
	Edge *edge_four = new Edge;

	state_one->assign(next_state_num, edge_one);
	next_state_num++;
	state_two->assign(next_state_num, NULL);
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
/*
    a*
*/
NFA_state *NFA::closure(NFA_state *a)
{
	State *state_one = new State;
	State *state_two = new State;
	Edge *edge_one = new Edge;
	Edge *edge_two = new Edge;
	Edge *edge_three = new Edge;
	Edge *edge_four = new Edge;

	state_one->assign(next_state_num, edge_one);
	next_state_num++;
	state_two->assign(next_state_num, NULL);
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
/*
    根据RE构造NFA
*/
NFA_state *NFA::Thompson(Regex_node *node)
{
	if(node->value == ALT)
	{
		NFA_state *a = Thompson(node->left);
		NFA_state *b = Thompson(node->right);
		NFA_state *c = alt(a,b);
		return c;
	}
	else if(node->value == CONCAT)
	{
		NFA_state *a = Thompson(node->left);
		NFA_state *b = Thompson(node->right);
		NFA_state *c = concat(a,b);
		return c;
	}
	else if(node->value == CLOSURE)
	{
		NFA_state *a = Thompson(node->left);
		NFA_state *c = closure(a);
		return c;
	}
	else
	{
		NFA_state *a = one_char_nfa(node->value);
		element.insert(node->value);
		return a;
	}
}
/*
int main()
{
	RE_tree re;
	Regex_node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);
}
*/
