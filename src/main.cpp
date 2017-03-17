#include "SyntacticTree.h"
#include "EpsilonNFA.h"

int main() {
	Regex::SyntacticTree st("d{242}f{431,533}f{431,}f{,533}f{,}");
	st.scan();
	st.toString();
}