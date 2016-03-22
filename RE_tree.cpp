#include "RE_tree.h"


void insert_production_one(int type, RE_tree_node *p, char num)
{
	if(type == 1)
	{
		RE_tree_node *p_left = new RE_tree_node('|', p);
		RE_tree_node *p_middle = new RE_tree_node(A_start, p);
		RE_tree_node *p_right = new RE_tree_node(Regex_type, p);
		p->lch_node = p_left;
		p_left->bro_node = p_middle;
		p_middle->bro_node = p_right;
	}
	else if(type == 2)
		;
	else
		throw -1;
}
void insert_production_two(int type, RE_tree_node *p, char num)
{
	if(type == 1)
	{
		RE_tree_node *p_left = new RE_tree_node(B_type, p);
		RE_tree_node *p_right = new RE_tree_node(A_type, p);
		p->lch_node = p_left;
		p_left->bro_node = p_right;
	}
	else if(type == 2)
		;
	else
		throw -1;
}
void insert_production_three(int type, RE_tree_node *p, char num)
{
	if(type == 1)
	{
		RE_tree_node *p_left = new RE_tree_node(C_type, p);
		RE_tree_node *p_right = new RE_tree_node('*', p);
		p->lch_node = p_left;
		p_left->bro_node = p_right;		
	}
	else if(type == 2)
	{
		RE_tree_node *p_new = new RE_tree_node(C_type, p);
		p->lch_node = p_new;		
	}
	else
		throw -1;
}
void insert_production_four(int type, RE_tree_node *p, char num)
{
	if(type == 1)
	{
		RE_tree_node *p_left = new RE_tree_node('(', p);
		RE_tree_node *p_middle = new RE_tree_node(Regex_start, p);
		RE_tree_node *p_right = new RE_tree_node(')', p);
		p->lch_node = p_left;
		p_left->bro_node = p_middle;
		p_middle->bro_node = p_right;
	}
	else if(type == 2)
	{
		RE_tree_node *p_new = new RE_tree_node(e_type, p);
		p_new->value = num;
		p->lch_node = p_new;
	}
	else
		throw -1;
}
void insert_production_five(int type, RE_tree_node *p, char num)
{
	RE_tree_node *p_left = new RE_tree_node(A_start, p);
	RE_tree_node *p_right = new RE_tree_node(Regex_type, p);
	p->lch_node = p_left;
	p_left->bro_node = p_right;
}
void insert_production_six(int type, RE_tree_node *p, char num)
{
	RE_tree_node *p_left = new RE_tree_node(B_type, p);
	RE_tree_node *p_right = new RE_tree_node(A_type, p);
	p->lch_node = p_left;
	p_left->bro_node = p_right;	
}

RE_tree_node::RE_tree_node(int t, RE_tree_node *p, char v, RE_tree_node *l, RE_tree_node *b)
{
	type = t;
	prt_node = p;
	lch_node = l;
	bro_node = b;
	value = v;
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

	root = new RE_tree_node(Regex_start, NULL);
}

void RE_tree::input_regex()
{
	cout <<"请输入正则表达式："<<endl;
	cin>> regex;
}
void RE_tree::generate_tree()
{
	string::iterator pos_current = regex.begin();
	string::iterator pos_end = regex.end();
	RE_tree_node * node = root;
	while(true)
	{

	}
}

void RE_tree::push_element()
{
}
void RE_tree::backtrack()
{
}
int main()
{
	RE_tree re;
	re.input_regex();
	cout << re.regex << endl;
}
