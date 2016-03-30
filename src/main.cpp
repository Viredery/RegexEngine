#include "Judge.h"
#include "DFA.h"
#include "NFA.h"
#include "RE_tree.h"
#include <iostream>
using namespace std;

int main()
{
	RE_tree re;
	Regex_node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);
	DFA dfa(nfa.get_element_set());
	dfa.subset_construction(regex_nfa);
	Judge judge;
	judge.input_string();
	bool ok = judge.judge_string(dfa.dfa, dfa.accepted_state);
	if(ok)
		cout<<"ok"<<endl;
	else
		cout<<"fail"<<endl;

}
