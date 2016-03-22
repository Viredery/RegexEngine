/*
  实现一个由三型文法构成的正则表达式(经典正则表达式)的引擎
  文法：选择R|S；连接RS；闭包R*


1    RegEx -> RegEx | A
2          -> A

3    A -> A B
4      -> B

5    B -> C*
6      -> C

7    C -> ( RegEx )
8      -> e

  该正则表达式的字符包括a-z A-Z 0-9 和 _
*/


#ifndef RE_TREE_H
#define RE_TREE_H


#include <iostream>
#include <set>
#include <vector>
using namespace std;

//以下可以组织成一个类


/*新的结构栈
用于回溯*/

struct RE_tree_node
{
	int type;
	char value;
	RE_tree_node *lch_node;
	RE_tree_node *bro_node;
	RE_tree_node *prt_node;
};

static void insert_production_one(int type, RE_tree_node *p, char num = '\0');
static void insert_production_two(int type, RE_tree_node *p, char num = '\0');
static void insert_production_three(int type, RE_tree_node *p, char num = '\0');
static void insert_production_four(int type, RE_tree_node *p, char num = '\0');

class RE_tree
{
public:
	enum {
		Regex_type = 0, A_type, B_type, C_type, e_type, sign_type
	};
	RE_tree();
	set<char> terminator;
	vector<char> regularExpression;
	RE_tree_node *root;
	typedef void (*insert_func)(int type, RE_tree_node *p, char num);
	vector<insert_func> insert;
private:

};



#endif
