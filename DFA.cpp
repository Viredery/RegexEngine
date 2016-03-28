#include "DFA.h"

Transfer::Transfer(int e, char ele)
{
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
		map<char,int> transfer;
		dfa.push_back(transfer);
		if(q.find(nfa->end) != q.end())
			accepted_state.insert(start);
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
				dfa[start][*character] = pos;
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
void DFA::Hopcroft()
{
	int size = e_state_set.size();
	vector< set<int> > group;
	group.push_back(accepted_state);
	int i;
	set<int> unaccepted;
	for(i = 0; i != size; i++)
	{
		if(accepted_state.find(i) == accepted_state.end())
			unaccepted.insert(i);
	}
	group.push_back(unaccepted);
	bool changed = false;
	do
	{
		changed = false;
		vector< set<int> > tmp;
		vector< set<int> >::iterator set_p = group.begin();
		for(;set_p != group.end(); set_p++)
		{
			vector< set<int> > result = split(set_p);
			vector< set<int> >::iterator p = result.begin();
			for(; p != result.end(); p++)
			{
				changed = true;
				tmp.push_back(*p);
			}
		}
		group = tmp;
	}while(changed == true);
}
vector< set<int> > DFA::split(vector< set<int> >::iterator p)
{
	vector< set<int> > result;

	set<char>::iterator character = element.begin();
	for(; character != element.end(); character++)
	{
		set<int>::iterator tmp = p->begin();
		for(; tmp != p->end(); tmp++)
		{
			multimap<int, Transfer *>::iterator iter = dfa.lower_bound(*tmp);
			multimap<int, Transfer *>::iterator iter_end = dfa.upper_bound(*tmp);
			while(iter != iter_end)
			{
				if(iter->second->element == *character)
				{
					if(p->find(iter->second->end) == p->end())
					{
						分成两个set
					}
					break:
				}
				iter++;
			}
			
		}
	}

}
*/
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
