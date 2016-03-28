#include "DFA.h"

Transfer::Transfer(int s, int e, char ele)
{
	start = s;
	end = e;
	element = ele;
}

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
		if(q.find(nfa->end) != q.end())
			accepted_state.push_back(start);
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

			int pos;
			if((pos = postion(equal_state)) == -1 && !equal_state.empty())
			{
				e_state_set.push_back(equal_state);
				worklist.push(equal_state);
				pos = e_state_set.size() - 1;
			}
			if(!equal_state.empty())
			{
				Transfer *t = new Transfer(start, pos, *character);
				record.push_back(t);
			}

			equal_state.clear();

			character++;
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
		while(p1 != set_p->end() && p2 != p.end())
		{
			if(*p1 != *p2)
				break;
			p1++;
			p2++;
		}
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
	Node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);
	DFA dfa(nfa.element);
	dfa.subset_construction(regex_nfa);

}
*/
