/*
  实现一个由三型文法构成的正则表达式(经典正则表达式)的引擎
  文法：选择R|S；连接RS；闭包R*

0    Goal -> RegEx

1    RegEx -> A | RegEx
2          -> A

3    A -> B A
4      -> B

5    B -> C*
6      -> C

7    C -> ( RegEx )
8      -> e

  该正则表达式的字符包括a-z A-Z 0-9 和 _
*/
/*
	由于一开始没有选择好的数据结构，导致之后实现的复杂度高，仅仅实现了closure和goto。应选择set等，下次再修改

*/





/*
待修改：
	Goal_type从1开始排
	goto_func的返回值
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

enum {
	Goal_type = 1, RegEx_type, A_type, B_type, C_type, e_type
};

int sign_to_production[6][2] = {{0,0},{0,0},{1,2},{3,4},{5,6},{7,8}};

char finish_sign[6] = {'|','*','(',')',e_type,'\0'};

class LR1_project
{
/*
*	LR(1)项目，例如初始状态[Goal -> .RegEx, eof]表示为
*	hander[0] = Goal_type, handler[1] = RegEx,
*	next_sign_pos = 1, sign = '\0'
*/
public:
	vector<char> handler;
	int next_sign_pos;
	char sign;
	void print();
};
void LR1_project::print()
{
	cout << "[" << (int)handler[0] << " -> ";
	int i;
	for(i = 1; i != handler.size(); i++)
	{
		if( next_sign_pos == i)
			cout << ".";
		cout << (int)handler[i] << " ";
	}
	if(next_sign_pos == i)
		cout << ".";
	cout <<", "<<sign<< "]" << endl;
}

LR1_project production[9];




class RegularEngine
{
public:
	RegularEngine();
	void closure(vector<LR1_project *> &s);
	bool exist(LR1_project *p, vector<LR1_project *> s);
	void goto_func(vector<LR1_project *> &s, char x);
	vector< vector<LR1_project *> > project;
	void test();
	void create();
};
RegularEngine::RegularEngine()
{
	LR1_project *initial_status = new LR1_project(production[0]);
	initial_status->next_sign_pos = 1;
	initial_status->sign = '\0';

	vector<LR1_project *> status;
	status.push_back(initial_status);
	project.push_back(status);
}

bool RegularEngine::exist(LR1_project *p, vector<LR1_project *> s)
{
	int i;
	for(i = 0; i != s.size(); i++)
	{
		if(s[i]->sign == p->sign && s[i]->next_sign_pos == p->next_sign_pos && s[i]->handler.size() == p->handler.size() )
		{
			int n = p->handler.size();
			int j;
			for(j = 0; j != n; j++)
			{
				if(s[i]->handler[j] != p->handler[j])
					break;
			}
			if(j == n)
			{
				return true;
			}
		}
	}
	return false;
}
void RegularEngine::closure(vector<LR1_project *> &s)
{
	bool change = false;
	do{
		change = false;
		int i, j;
		for(i = 0; i != s.size(); i++)
		{
			if(s[i]->handler[s[i]->next_sign_pos] < 6 && s[i]->handler[s[i]->next_sign_pos] > 0)
			{
				int *num = sign_to_production[s[i]->handler[s[i]->next_sign_pos]];
				for(j = 0; j != 2; j++)
				{
					char s1[10];
					int k, l = 0;
					for(k = s[i]->next_sign_pos + 1; k != s[i]->handler.size(); k++)
					{
						if(!(s[i]->handler[k] < 6 && s[i]->handler[k] > 0))
						{
							s1[l] = s[i]->handler[k];
							l++;
						}
					}
					s1[l] = s[i]->sign;
					for(k = 0; k <= l; k++)
					{
							LR1_project *new_p = new LR1_project(production[num[j]]);
							new_p->next_sign_pos = 1;
							new_p->sign = s1[k];
							if(!exist(new_p, s))
							{
								s.push_back(new_p);
								change = true;
							}
					}
				}
			}
		}
	}while(change == true);
}
void RegularEngine::goto_func(vector<LR1_project *> &s, char x)
{
	vector<LR1_project *> new_s;
	int i, n = s.size();
	for(i = 0; i != n; i++)
	{
		if(s[i]->handler.size() != s[i]->next_sign_pos && s[i]->handler[s[i]->next_sign_pos] == x)
		{
			LR1_project *new_p = new LR1_project(*s[i]);
			new_p->next_sign_pos ++;
			new_s.push_back(new_p);
		}
	}
	closure(new_s);
cout << new_s.size() << endl;
	for(i = 0; i != new_s.size(); i++)
		new_s[i]->print();
}
void RegularEngine::test()
{
	closure(project[0]);
	int i;
	for(i = 0; i != project[0].size(); i++)
		project[0][i]->print();
}
void RegularEngine::create()
{
	
	do {

	}while()
}
int main()
{
	production[0].handler.push_back(Goal_type);
	production[0].handler.push_back(RegEx_type);
	production[1].handler.push_back(RegEx_type);
	production[1].handler.push_back(A_type);
	production[1].handler.push_back('|');
	production[1].handler.push_back(RegEx_type);
	production[2].handler.push_back(RegEx_type);
	production[2].handler.push_back(A_type);
	production[3].handler.push_back(A_type);
	production[3].handler.push_back(B_type);
	production[3].handler.push_back(A_type);
	production[4].handler.push_back(A_type);
	production[4].handler.push_back(B_type);
	production[5].handler.push_back(B_type);
	production[5].handler.push_back(C_type);
	production[5].handler.push_back('*');
	production[6].handler.push_back(B_type);
	production[6].handler.push_back(C_type);
	production[7].handler.push_back(C_type);
	production[7].handler.push_back('(');
	production[7].handler.push_back(RegEx_type);
	production[7].handler.push_back(')');
	production[8].handler.push_back(C_type);
	production[8].handler.push_back(e_type);
/*
	cout<<"s"<<endl;

	char s1[10];
	char s2[10];
	strcat(s1,"s");
	strcat(s2,"\0");
	const char *p = strstr(s1,s2);
	if(p==NULL) cout<<"no"<<endl;
	else cout<<"yes"<<endl;

*/

	RegularEngine RE;
	RE.test();
	RE.goto_func(RE.project[0],(char)'(');
}
