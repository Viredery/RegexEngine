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
	{
		RE_tree_node *p_child = new RE_tree_node(eof_type, p);
		p->lch_node = p_child;
	}
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
	{
		RE_tree_node *p_child = new RE_tree_node(eof_type, p);
		p->lch_node = p_child;
	}
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
	terminator.insert(eof_type);

	insert.push_back(insert_production_one);
	insert.push_back(insert_production_two);
	insert.push_back(insert_production_three);
	insert.push_back(insert_production_four);
	insert.push_back(insert_production_five);
	insert.push_back(insert_production_six);

	root = new RE_tree_node(Regex_start, NULL);

	regex_tree = new Node;
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
	char type_current;
	if(terminator.find(*pos_current) != terminator.end())
		type_current = *pos_current;
	else
		type_current = e_type;
	while(true)
	{
		if(terminator.find(node->type) != terminator.end() && node->type == eof_type)
			node = get_next_node(node);
		else if(terminator.find(node->type) != terminator.end() && type_current == node->type)
		{
			record.top()->num_inserted++;
			node = get_next_node(node);
			if(pos_current != pos_end)
			{
				pos_current++;
				if(pos_current != pos_end)
				{
					if(terminator.find(*pos_current) != terminator.end())
						type_current = *pos_current;
					else
						type_current = e_type;
				}
				else
					type_current = eof_type;
			}
			else
				type_current = eof_type;
		}
		else if(terminator.find(node->type) != terminator.end() && type_current != node->type)
			node = backtrack(node, pos_current, type_current);
		else if(terminator.find(node->type) == terminator.end())
		{
			int type = push_element(node, pos_current, type_current);
			insert[node->type](type, node, *pos_current);
			node = node->lch_node;
		}
		if(node == NULL && pos_current == pos_end)
			return;
		else if(node == NULL && pos_current != pos_end)
			node = backtrack(node, pos_current, type_current);
	}
}

int RE_tree::push_element(RE_tree_node *p, string::iterator &s, char &type_current)
{
	stack_element *element = new stack_element;
	if((!record.empty()) && record.top()->node_inserted == p && record.top()->type == 1)
	{
		while(record.top()->num_inserted > 0)
		{
			s--;
			if(terminator.find(*s) != terminator.end())
				type_current = *s;
			else
				type_current = e_type;
			record.top()->num_inserted--;
		}
		record.top()->type = 2;
		return 2;
	}
	else
	{
		element->node_inserted = p;
		element->type = 1;
		element->num_inserted = 0;
		record.push(element);
		return 1;
	}
}
//目前没有delete
RE_tree_node *RE_tree::backtrack(RE_tree_node *p, string::iterator &s, char &type_current)
{
	while((!record.empty()) && record.top()->type == 2)
	{
		while((!record.empty()) && record.top()->type == 2)
		{
			while(record.top()->num_inserted > 0)
			{
				s--;
				if(terminator.find(*s) != terminator.end())
					type_current = *s;

				else
					type_current = e_type;
				record.top()->num_inserted--;
			}
			record.pop();
		}
		while((!record.empty()) && (record.top()->node_inserted->type == A_start || record.top()->node_inserted->type == Regex_start))
			record.pop();
	}

	if(record.empty())
		return NULL;
	else
		return record.top()->node_inserted;
}
RE_tree_node *RE_tree::get_next_node(RE_tree_node *p)
{
	if(p == NULL)
		return NULL;
	if(p->bro_node != NULL)
		return p->bro_node;
	return get_next_node(p->prt_node);
}
/*
void RE_tree::print_tree(RE_tree_node *p)
{
	if(p == NULL)
		cout<<endl;
	else
	{
		cout<<p->type<<" ";
		print_tree(p->lch_node);
		print_tree(p->bro_node);
	}
}
*/
void RE_tree::simplification(RE_tree_node *root, Node *node)
{
	if(root->type == A_start)
	{
		if(root->bro_node->lch_node->type == eof_type)
			simplification(root->lch_node, node);
		else
		{
			node->value = ALT;
			Node *left = new Node;
			Node *right = new Node;
			node->left = left;
			node->right = right;
			simplification(root->lch_node, left);
			simplification(root->bro_node->lch_node->bro_node, right);
		}
	}
	else if(root->type == B_type)
	{
		if(root->bro_node->lch_node->type == eof_type)
			simplification(root->lch_node, node);
		else
		{
			node->value = CONCAT;
			Node *left = new Node;
			Node *right = new Node;
			node->left = left;
			node->right = right;
			simplification(root->lch_node, left);
			simplification(root->bro_node->lch_node, right);
		}
	}
	else if(root->type == C_type)
	{
		if(root->bro_node == NULL)
			simplification(root->lch_node, node);
		else
		{
			node->value = CLOSURE;
			Node *left = new Node;
			node->left = left;
			node->right = NULL;
			simplification(root->lch_node, left);
		}
	}
	else if(root->type == '(')
		simplification(root->bro_node, node);
	else if(root->type == e_type)
	{
		node->value = root->value;
		node->left = node->right = NULL;
	}
	else
		simplification(root->lch_node, node);
}
/*
void RE_tree::print_tree(Node *node)
{
	if(node == NULL)
		cout<<"NULL ";
	else
	{
		cout<<(int)node->value<<" ";
		print_tree(node->left);
		print_tree(node->right);
	}
}
*/
Node *RE_tree::get_re_tree()
{
	input_regex();
	generate_tree();
	simplification(root, regex_tree);
//	print_tree(regex_tree);
	return regex_tree;
}
/*
int main()
{
	RE_tree re;
	re.get_re_tree();
}
*/
