#include "RE_tree.h"

enum {
	Regex_symbol = 0, A_symbol, B_symbol, C_symbol, D_symbol, E_symbol, F_symbol, e_symbol, sign_symbol, eof_symbol
};

class Grammar_node
{
public:
	int symbol;
	char value;
	Grammar_node *prt_node;
	Grammar_node *lch_node;
	Grammar_node *bro_node;
	Grammar_node(int s, Grammar_node *p, char v = '\0', Grammar_node *l = NULL, Grammar_node *b = NULL);
};

Grammar_node::Grammar_node(int s, Grammar_node *p, char v, Grammar_node *l, Grammar_node *b)
{
	symbol = s;
	prt_node = p;
	lch_node = l;
	bro_node = b;
	value = v;
}
void insert_production_one_child(Grammar_node *p, char child_symbol, char num = '\0')
{
	Grammar_node *p_child = new Grammar_node(child_symbol, p, num);
	p->lch_node = p_child;
}
void insert_production_two_child(Grammar_node *p, char lchild_symbol, char rchild_symbol)
{
	Grammar_node *p_left = new Grammar_node(lchild_symbol, p);
	Grammar_node *p_right = new Grammar_node(rchild_symbol, p);
	p->lch_node = p_left;
	p_left->bro_node = p_right;
}
void insert_production_three_child(Grammar_node *p, char lchild_symbol, char mchild_symbol, char rchild_symbol)
{
	Grammar_node *p_left = new Grammar_node(lchild_symbol, p);
	Grammar_node *p_middle = new Grammar_node(mchild_symbol, p);
	Grammar_node *p_right = new Grammar_node(rchild_symbol, p);
	p->lch_node = p_left;
	p_left->bro_node = p_middle;
	p_middle->bro_node = p_right;
}
/*
      RegEx -> B A
*/
void insert_production_Regex(char symbol, Grammar_node *p, char num)
{
	insert_production_two_child(p, B_symbol, A_symbol);
}
/*
      A -> | B A
        -> eof
*/
void insert_production_A(char symbol, Grammar_node *p, char num)
{
	if(symbol =='|')
		insert_production_three_child(p, '|', B_symbol, A_symbol);
	else
		insert_production_one_child(p, eof_symbol);
}
/*
      B -> D C
*/
void insert_production_B(char symbol, Grammar_node *p, char num)
{
	insert_production_two_child(p, D_symbol, C_symbol);
}
/*
      C -> D C
        -> eof
*/
void insert_production_C(char symbol, Grammar_node *p, char num)
{
	if(symbol == '(' || symbol == e_symbol)
		insert_production_two_child(p, B_symbol, A_symbol);
	else
		insert_production_one_child(p, eof_symbol);
}
/*
      D -> E F
*/
void insert_production_D(char symbol, Grammar_node *p, char num)
{
	insert_production_two_child(p, E_symbol, F_symbol);
}
/*
      E -> ( RegEx )
        -> element
*/
void insert_production_E(char symbol, Grammar_node *p, char num)
{
	if(symbol == '(')
		insert_production_three_child(p, '(', Regex_symbol, ')');
	else
		insert_production_one_child(p, e_symbol, num);
}
/*
     F -> *
       -> eof
*/
void insert_production_F(char symbol, Grammar_node *p, char num)
{
	if(symbol == '*')
		insert_production_one_child(p, '*');
	else
		insert_production_one_child(p, eof_symbol);
}



/*
    初始化终结符集合terminator,以及产生式数组insert
*/
RE_tree::RE_tree()
{
	terminator.insert('*');
	terminator.insert('|');
	terminator.insert('(');
	terminator.insert(')');
	terminator.insert(e_symbol);
	terminator.insert(eof_symbol);


	insert.push_back(insert_production_Regex);
	insert.push_back(insert_production_A);
	insert.push_back(insert_production_B);
	insert.push_back(insert_production_C);
	insert.push_back(insert_production_D);
	insert.push_back(insert_production_E);
	insert.push_back(insert_production_F);

	grammar_tree = new Grammar_node(Regex_symbol, NULL);

	regex_tree = new Regex_node;
}
/*
    析构函数,释放new表达式所分配的内存
*/
RE_tree::~RE_tree()
{
	delete_grammar_tree(grammar_tree);
	delete_regex_tree(regex_tree);
}
void RE_tree::delete_grammar_tree(Grammar_node *node)
{
	if(node == NULL)
		return;
	delete_grammar_tree(node->lch_node);
	delete_grammar_tree(node->bro_node);
	delete node;
}
void RE_tree::delete_regex_tree(Regex_node *node)
{
	if(node == NULL)
		return;
	delete_regex_tree(node->left);
	delete_regex_tree(node->right);
	delete node;
}
/*
    读入用户输入的正则表达式
*/
void RE_tree::input_regex()
{
	cout << "请输入正则表达式：" << endl;
	cin >> regex_string;
}
/*
    构建文法分析树
*/
void RE_tree::generate_tree()
{
	string::iterator pos_current = regex_string.begin();
	string::iterator pos_end = regex_string.end();
	Grammar_node * node = grammar_tree;
	char symbol_current = get_current_symbol(pos_current);
	while(true)
	{
		if(terminator.find(node->symbol) != terminator.end() && node->symbol == eof_symbol)
			node = get_next_node(node);
		else if(terminator.find(node->symbol) != terminator.end() && symbol_current == node->symbol)
		{
			node = get_next_node(node);
			pos_current++;	//这里不需要先判断是否pos_current != pos_end
			if(pos_current != pos_end)
				symbol_current = get_current_symbol(pos_current);
			else
				symbol_current = eof_symbol;

		}
		else if(terminator.find(node->symbol) == terminator.end())
		{
			insert[node->symbol](symbol_current, node, *pos_current);
			node = node->lch_node;
		}
		if(node == NULL && pos_current == pos_end)
			return;
	}
}
/*
    构建文法分析树辅助函数,获取下一个符号信息
*/
char RE_tree::get_current_symbol(string::iterator pos_current)
{
	if(terminator.find(*pos_current) != terminator.end())
		return *pos_current;
	else
		return e_symbol;
}
/*
    构建文法分析树辅助函数,获取下一个符号信息
*/
Grammar_node *RE_tree::get_next_node(Grammar_node *p)
{
	if(p == NULL)
		return NULL;
	if(p->bro_node != NULL)
		return p->bro_node;
	return get_next_node(p->prt_node);
}

/*
    简化分析树作为输出,之后用该树来构造NFA
*/
void RE_tree::simplification(Grammar_node *root, Regex_node *node)
{
	if(root->symbol == B_symbol)
	{
		if(root->bro_node->lch_node->symbol == eof_symbol)
			simplification(root->lch_node, node);
		else
		{
			node->value = ALT;
			Regex_node *left = new Regex_node;
			Regex_node *right = new Regex_node;
			node->left = left;
			node->right = right;
			simplification(root->lch_node, left);
			simplification(root->bro_node->lch_node->bro_node, right);
		}
	}
	else if(root->symbol == D_symbol)
	{
		if(root->bro_node->lch_node->symbol == eof_symbol)
			simplification(root->lch_node, node);
		else
		{
			node->value = CONCAT;
			Regex_node *left = new Regex_node;
			Regex_node *right = new Regex_node;
			node->left = left;
			node->right = right;
			simplification(root->lch_node, left);
			simplification(root->bro_node->lch_node, right);
		}
	}
	else if(root->symbol == E_symbol)
	{
		if(root->bro_node->lch_node->symbol == eof_symbol)
			simplification(root->lch_node, node);
		else
		{
			node->value = CLOSURE;
			Regex_node *left = new Regex_node;
			node->left = left;
			node->right = NULL;
			simplification(root->lch_node, left);
		}
	}
	else if(root->symbol == '(')
		simplification(root->bro_node, node);
	else if(root->symbol == e_symbol)
	{
		node->value = root->value;
		node->left = node->right = NULL;
	}
	else
		simplification(root->lch_node, node);
}
/*
    打印RE树,检查是否得到正确结果
*/
void RE_tree::print_tree(Regex_node *node)
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
/*
    执行输入的正则表达式到RE树的转换
*/
Regex_node *RE_tree::get_re_tree()
{
	input_regex();
	generate_tree();
	simplification(grammar_tree, regex_tree);
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
