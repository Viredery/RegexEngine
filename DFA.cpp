#include "DFA.h"



DFA::DFA(set<char> e)
{
	element = e;
}

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
	for(;state != end; state++)
	{
		Edge *edge = (*state)->edge;
		while(edge != NULL)
		{
			if(edge->element == c)
				equal_state.insert(edge->next_state);
			edge = edge->next_edge;
		}
	}
}
void DFA::subset_construction(NFA_state *nfa)
{
	empty_closure(nfa->start);
	e_state_set.push_back(equal_state);
	worklist.push(equal_state);
	equal_state.clear();

	while(!worklist.empty())
	{
		set<State *> q = worklist.front();
		worklist.pop();

		int start = postion(q);
		map<char,int> transfer;
		dfa.push_back(transfer);
		if(q.find(nfa->end) != q.end())
			accepted_state.insert(start);
		set<char>::iterator character = element.begin();
		for(; character != element.end(); character++)
		{
			delta(q, *character);
			set<State *> tmp(equal_state);
			set<State *>::iterator tmp_p = tmp.begin();
			for(; tmp_p != tmp.end(); tmp_p++)
				empty_closure(*tmp_p);
			int pos;
			if(!equal_state.empty() && (pos = postion(equal_state)) == -1)
			{
				e_state_set.push_back(equal_state);
				worklist.push(equal_state);
				pos = e_state_set.size() - 1;
			}
			if(!equal_state.empty())
				dfa[start][*character] = pos;
			equal_state.clear();
		}
	}
}

int DFA::postion(set<State *> &p)
{
	vector< set<State *> >::iterator set_p = e_state_set.begin();
	while(set_p != e_state_set.end())
	{
		set<State *>::iterator p1 = set_p->begin();
		set<State *>::iterator p2 = p.begin();
		for(; p1 != set_p->end() && p2 != p.end(); p1++, p2++)
			if(*p1 != *p2)
				break;
		if(p1 == set_p->end() && p2 == p.end())
			return (int)(set_p - e_state_set.begin());
		set_p++;
	}
	return -1;
}


/*
int main()
{
	RE_tree re;
	Regex_node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);
	DFA dfa(nfa.get_element_set());
	dfa.subset_construction(regex_nfa);
	nfa.delete_state_edge(regex_nfa->start);
}
*/
