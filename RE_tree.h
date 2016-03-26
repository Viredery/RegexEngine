/*
  实现一个由三型文法构成的正则表达式(经典正则表达式)的引擎
  文法：选择R|S；连接RS；闭包R*




     Regex' -> A' Regex
1    Regex -> | A' Regex
2           -> eof

     A' -> B A
3    A -> B A
4      -> eof

5    B -> C*
6      -> C

7    C -> ( RegEx' )
8      -> e

  该正则表达式的字符包括a-z A-Z 0-9 和 _
*/


#ifndef RE_TREE_H
#define RE_TREE_H


#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
using namespace std;

enum {
	Regex_type = 0, A_type, B_type, C_type, Regex_start, A_start, e_type, sign_type, eof_type
};
enum NodeKind {
	ALT = 0, CONCAT, CLOSURE
};

struct Node
{
	char value;
	Node *left;
	Node *right;
};


class RE_tree_node
{
public:
	int type;
	char value;
	RE_tree_node *prt_node;
	RE_tree_node *lch_node;
	RE_tree_node *bro_node;
	RE_tree_node(int t, RE_tree_node *p, char v = '\0', RE_tree_node *l = NULL, RE_tree_node *b = NULL);
};

struct stack_element
{
	RE_tree_node *node_inserted;
	int type;
	bool num_inserted;
};


static void insert_production_one(int type, RE_tree_node *p, char num = '\0');
static void insert_production_two(int type, RE_tree_node *p, char num = '\0');
static void insert_production_three(int type, RE_tree_node *p, char num = '\0');
static void insert_production_four(int type, RE_tree_node *p, char num = '\0');
static void insert_production_five(int type, RE_tree_node *p, char num = '\0');
static void insert_production_six(int type, RE_tree_node *p, char num = '\0');
class RE_tree
{
public:
	RE_tree();
	Node *get_re_tree();
private:
	typedef void (*insert_func)(int type, RE_tree_node *p, char num);
	void input_regex();
	void generate_tree();
	void simplification(RE_tree_node *root, Node *start);	
	RE_tree_node *get_next_node(RE_tree_node *p);
	RE_tree_node *backtrack(RE_tree_node *p, string::iterator &s, char &type_current);
	int push_element(RE_tree_node *p, string::iterator &s, char &type_current);

	vector<insert_func> insert;
	string regex;
	RE_tree_node *root;
	stack<stack_element *> record;
	Node *regex_tree;
	set<char> terminator;
};



#endif
