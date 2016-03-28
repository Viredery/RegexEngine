//#ifndef DFA_H
//#define DFA_H
//#endif

#include "NFA.h"
#include <set>
#include <queue>
using namespace std;

class DFA
{
public:
	void empty_closure(State *s);
	vector< set<State *> > e_state_set;
	queue< set<State *> > worklist;
	set<char> element;
	DFA(set<char> e) {
		element = e;
	}
	set<State *> equal_state;
	void delta(set<State *> es, char c);
	void subset_construction(State *s);
	bool contain();
};



void DFA::empty_closure(State *s)
{
	equal_state.insert(s);
	Edge *edge = s->edge;
	while(edge != NULL)
	{
		if(edge->element == EMPTY)
			empty_closure(edge->next_state);
		edge = edge->next_edge;
	}
}
void DFA::delta(set<State *> es, char c)
{
	set<State *>::iterator state = es.begin();
	set<State *>::iterator end = es.end();
	while(state != end)
	{
		Edge *edge = (*state)->edge;
		while(edge != NULL)
		{
			if(edge->element == c)
				equal_state.insert(edge->next_state);
			edge = edge->next_edge;
		}
		state++;
	}
}
void DFA::subset_construction(State *s)
{
	empty_closure(s);
	e_state_set.push_back(equal_state);
	worklist.push(equal_state);
	equal_state.clear();
	while(!worklist.empty())
	{
		set<State *> q = worklist.front();
/*
set<State *>::iterator tmp_iter = q.begin();
while(tmp_iter != q.end())
{
cout<<(*tmp_iter)->state<<" ";
tmp_iter++;
}
cout<<endl;
*/
		worklist.pop();
		set<char>::iterator character = element.begin();
		while(character != element.end())
		{
			delta(q, *character);
			set<State *> tmp(equal_state);
			equal_state.clear();
			set<State *>::iterator tmp_p = tmp.begin();
			while(tmp_p != tmp.end())
			{
				empty_closure(*tmp_p);
				tmp_p++;
			}

			//T[q, character] <- equal_state;
			if(contain() == false && !equal_state.empty())
			{
				e_state_set.push_back(equal_state);
				worklist.push(equal_state);
			}
			equal_state.clear();

			character++;
		}
	}
}
bool DFA::contain()
{
	vector< set<State *> >::iterator set_p = e_state_set.begin();
	while(set_p != e_state_set.end())
	{
		set<State *>::iterator p1 = set_p->begin();
		set<State *>::iterator p2 = equal_state.begin();
		while(p1 != set_p->end() && p2 != equal_state.end())
		{
			if(*p1 != *p2)
				break;
			p1++;
			p2++;
		}
		if(p1 == set_p->end() && p2 == equal_state.end())
			return true;
		set_p++;
	}
	return false;
}
int main()
{
	RE_tree re;
	Node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);
	DFA dfa(nfa.element);
	dfa.subset_construction(regex_nfa->start);

}

