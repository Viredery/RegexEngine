#include "Judge.h"

void Judge::input_string()
{
	cout<<"输入字符串："<<endl;
	cin>>input_judge;
}
bool Judge::judge_string(vector< map<char,int> > &dfa, set<int> &accepted_state)
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
