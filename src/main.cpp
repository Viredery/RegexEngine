#include "SyntacticTree.h"
#include "EpsilonNFA.h"


#include "Node.h"
#include <iostream>
int main() {
	Regex::SyntacticTree st("d{2}[0-9](?!au)");
	st.scan();
	st.toString();
	
    st.constructTree();
    st.printTree(st.getTree());

	//Regex::NFA nfa;
	//nfa.getState(st.getTree());
}