#include "SyntacticTree.h"
#include "EpsilonNFA.h"
#include "Node.h"
#include "CompressedNFA.h"


#include <iostream>

int main() {
	try {
	    //Regex::SyntacticTree st("d{2,4}?(0-9)*?[\\w]+");
        Regex::SyntacticTree st("(?:ab|cd)*?");
	    st.scan();
	    st.toString();
	
        st.constructTree();
        st.printTree(st.getTree());
        std::cout << std::endl;
	    Regex::NFA nfa;
	    nfa.getState(st.getTree());

        Regex::CompressedNFA cnfa;
        cnfa.handle(nfa.getStateList());

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}