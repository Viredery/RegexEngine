#include "SyntacticTree.h"
#include "EpsilonNFA.h"

int main() {
	Regex::SyntacticTree st("d{2}f{1,2}f{2,}ff{,}");
	st.scan();
	st.toString();
    st.constructTree();
	Regex::NFA nfa;
	nfa.getState(st.getTree());
}