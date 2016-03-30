/*
  实现一个由三型文法构成的正则表达式(经典正则表达式)的引擎
  文法：选择R|S；连接RS；闭包R*



1    RegEx -> B A
2    A -> | B A
3      -> eof

4    B -> D C
5    C -> D C
6      -> eof

7    D -> E F

8    E -> ( RegEx )
9      -> element

10   F -> *
11     -> eof

  该正则表达式的字符包括a-z A-Z 0-9
*/

#ifndef RE_TREE_H
#define RE_TREE_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;
class Grammar_node;

enum Operation {
	ALT = 0, CONCAT, CLOSURE
};

struct Regex_node
{
	char value;
	Regex_node *left;
	Regex_node *right;
};


class RE_tree
{
public:
	RE_tree();
	~RE_tree();
	Regex_node *get_re_tree();
private:
	typedef void (*insert_func)(char type, Grammar_node *p, char num);
	void input_regex();
	void generate_tree();
	void simplification(Grammar_node *root, Regex_node *start);	
	Grammar_node *get_next_node(Grammar_node *p);
	char get_current_symbol(string::iterator pos_current);
	void print_tree(Regex_node *node);
	void delete_grammar_tree(Grammar_node *node);
	void delete_regex_tree(Regex_node *node);

	vector<insert_func> insert;
	set<char> terminator;
	string regex_string;
	Grammar_node *grammar_tree;
	Regex_node *regex_tree;
	
};

#endif
