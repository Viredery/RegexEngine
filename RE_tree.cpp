#include "RE_tree.h"



void insert_production_one(int type, RE_tree_node *p, char num)
{
}
void insert_production_two(int type, RE_tree_node *p, char num)
{
}
void insert_production_three(int type, RE_tree_node *p, char num)
{
}
void insert_production_four(int type, RE_tree_node *p, char num)
{
}
RE_tree::RE_tree()
{
	terminator.insert('*');
	terminator.insert('|');
	terminator.insert('(');
	terminator.insert(')');
	terminator.insert(e_type);

	insert.push_back(insert_production_one);
	insert.push_back(insert_production_two);
	insert.push_back(insert_production_three);
	insert.push_back(insert_production_four);

	root = new RE_tree_node;
	root->type = Regex_type;
	root->prt_node = root->bro_node = root->lch_node = NULL;
}

int main()
{}
