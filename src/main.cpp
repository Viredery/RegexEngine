#include "SyntacticTree.h"
#include "EpsilonNFA.h"


#include "Node.h"
#include <iostream>
int main() {
	Regex::SyntacticTree st("d{2,4}[0-9]");
	st.scan();
	st.toString();
	
    st.constructTree();
    st.printTree(st.getTree());
    std::cout << std::endl;
	Regex::NFA nfa;
	nfa.getState(st.getTree());
}