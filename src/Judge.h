#ifndef JUDGE_H
#define JUDGE_H

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
	bool judge_string(vector< map<char,int> > &dfa, set<int> &accepted_state);
};


#endif
