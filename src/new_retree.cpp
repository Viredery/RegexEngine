#include <vector>
#include <string>
#include <iostream>
#include "new_node.hpp"

class SyntacticTree
{
public:
	SyntacticTree(std::string pattern);
	~SyntacticTree();
    void toString() {
    	for (auto node : nodeList)
    		std::cout << node->toString() << std::endl;
    }
    void scan();
    void tryCombine(bool flag) {
    	if (true == flag)
    		nodeList.push_back(new CombineNode());
    }
	std::string pattern;
	

	std::vector<Node *> nodeList;
	Node *root = nullptr;

	bool startRestriction = false;
	bool endRestriction = true;

};


SyntacticTree::SyntacticTree(std::string pattern): pattern(pattern) {}

SyntacticTree::~SyntacticTree() {}


/* first, we handle these input:
 *   [^abcd],|,*,+,?,(),^,$,.,{n,m}
 * not:
 *   \d,\W,or other \,\(,\),or other ().
 * No Syntax Inspection.
 */
void SyntacticTree::scan() {
	bool itemTerminated = false;
	std::size_t index = 0;
	while (index != pattern.size()) {
		switch (pattern[index]) {
			case '[': {
				tryCombine(itemTerminated);
			    bool included = true;
			    if (pattern[++index] == '^') {
			    	included = false;
			    	++index;
			    }
			    nodeList.push_back(new LeftBracket());
			    while (pattern[index] != ']') {
			    	if (pattern[index + 1] == '-') {
			    		nodeList.push_back(new ElementNode(included, pattern[index], pattern[index + 2]));
			    	    index += 3;
			    	} else {
			    		nodeList.push_back(new ElementNode(included, pattern[index], pattern[index]));
			    		index += 1;
			    	}
			    	nodeList.push_back(new OrNode());
			    }
			    // forgot delete
			    nodeList.pop_back();
			    nodeList.push_back(new RightBracket());

			    itemTerminated = true;
			    break;
			}
			case '|':
			    nodeList.push_back(new OrNode());
			    itemTerminated = false;
			    break;
			case '+':
			    nodeList.push_back(new ClosureNode(1, -1, true));
			    itemTerminated = true;
			    break;
			case '?':
			    nodeList.push_back(new ClosureNode(0, 1, false));
			    itemTerminated = true;
			    break;
			case '*':
			    nodeList.push_back(new ClosureNode(0, -1, true));
			    itemTerminated = true;
			    break;
			case '{': {
			    //{m,} {,n} {m,n} {,}
			    int minRepetition, maxRepetition;
                bool infinite = false;
                index = index + 1;
                std::size_t leftEnd = pattern.find_first_of(',', index);
                std::string strMinRepetition = pattern.substr(index, leftEnd - index);
                minRepetition = strMinRepetition == "" ? 0 : std::stoi(strMinRepetition);
                index = leftEnd + 1;
                std::size_t rightEnd = pattern.find_first_of('}', index);
                std::string strMaxRepetition = pattern.substr(index, rightEnd - index);
                maxRepetition = strMaxRepetition == "" ? -1 : std::stoi(strMaxRepetition);
                if (maxRepetition == -1)
                	infinite = true;
                index = rightEnd;
                nodeList.push_back(new ClosureNode(minRepetition, maxRepetition, infinite));
                itemTerminated = true;
			    break;
			}
			case '(':
			    tryCombine(itemTerminated);
			    nodeList.push_back(new LeftBracket());
			    itemTerminated = false;
			    break;
			case ')':
			    nodeList.push_back(new RightBracket());
			    itemTerminated = true;
			    break;
			case '^':
			    startRestriction = true;
			    break;
			case '$':
			    endRestriction = false;
			    break;
			case '.':
			    tryCombine(itemTerminated);
			    nodeList.push_back(new ElementNode(true, char(0), char(127)));
			    itemTerminated = true;
			    break;
			default:
			    tryCombine(itemTerminated);
			    nodeList.push_back(new ElementNode(true, pattern[index], pattern[index]));
			    itemTerminated = true;
			    break;
		}
		index++;
	}
}

int main() {
	SyntacticTree st("[aeiou]{,4}[0-9]?");
	st.scan();
	st.toString();

}