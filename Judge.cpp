#include "NFA.h"
#include "RE_tree.h"
#include "DFA.h"
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
class Judge
{
public:
	string input_judge;
	void input_string();
	bool judge_string(vector< map<char,int> > dfa, set<int> accepted_state);
};
int main()
{
	RE_tree re;
	Node *result = re.get_re_tree();
	NFA nfa;
	NFA_state *regex_nfa = nfa.Thompson(result);
	DFA dfa(nfa.element);
	dfa.subset_construction(regex_nfa);
	Judge judge;
	judge.input_string();
	bool ok = judge.judge_string(dfa.dfa, dfa.accepted_state);
	if(ok)
		cout<<"ok"<<endl;
	else
		cout<<"fail"<<endl;
}
void Judge::input_string()
{
	cout<<"输入字符串："<<endl;
	cin>>input_judge;
}
bool Judge::judge_string(vector< map<char,int> > dfa, set<int> accepted_state)
{
	string::iterator char_p = input_judge.begin();
	int state = 0;
	while(char_p != input_judge.end())
	{
		if(dfa[state].find(*char_p) == dfa[state].end())
			return false;
		state = dfa[state][*char_p];
		char_p++;
	}
	if(accepted_state.find(state) != accepted_state.end())
		return true;
	return false;
}
