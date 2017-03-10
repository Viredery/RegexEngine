#ifndef SYNTACTIC_TREE_CPP_
#define SYNTACTIC_TREE_CPP_

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Node.hpp"
#include "PostfixExpressionVisitor.hpp"

class SyntacticTree
{
public:
	SyntacticTree(std::string pattern): 
	    pattern(pattern) {}
	~SyntacticTree() = default;
    void toString() {
    	for (auto node : nodeList)
    		std::cout << node->toString() << " ";
    	std::cout <<std::endl;
    }
    void scan();
    void constructTree();

	std::string pattern;

	std::vector<std::shared_ptr<Node>> nodeList;
	std::shared_ptr<Node> root = nullptr;

	bool startRestriction = false;
	bool endRestriction = true;

	SyntacticTree(SyntacticTree&) = delete;
	SyntacticTree &operator=(const SyntacticTree&) = delete;

private:
    void handleCombiner(bool flag);
    int handleElementSet(int index);
    int handleQuantifier(int index);
};


/* first, we handle these input:
 *   [^abcd],|,*,+,?,(),^,$,.,{n,m}
 * next:
 *   Grouping Construct
 * not:
 *   \s == [\f\n\r\t\v], \S, \d, \w, \D, \W
 *   Character Escapes, Anchor
 * No Syntax Inspection.
 */
void SyntacticTree::scan() {
	bool itemTerminated = false;
	std::size_t index = 0;
	while (index != pattern.size()) {
		switch (pattern[index]) {
			case '[':
				handleCombiner(itemTerminated);
                index = handleElementSet(index);
			    itemTerminated = true;
			    break;
			case '|':
			    nodeList.push_back(std::make_shared<OrNode>());
			    itemTerminated = false;
			    break;
			case '+':
			    nodeList.push_back(std::make_shared<ClosureNode>(1, -1, true));
			    itemTerminated = true;
			    break;
			case '?':
			    nodeList.push_back(std::make_shared<ClosureNode>(0, 1, false));
			    itemTerminated = true;
			    break;
			case '*':
			    nodeList.push_back(std::make_shared<ClosureNode>(0, -1, true));
			    itemTerminated = true;
			    break;
			case '{':
			    //{m,} {,n} {m,n} {,}
			    index = handleQuantifier(index);
                itemTerminated = true;
			    break;
			case '(':
			    handleCombiner(itemTerminated);
			    nodeList.push_back(std::make_shared<LeftBracket>());
			    itemTerminated = false;
			    break;
			case ')':
			    nodeList.push_back(std::make_shared<RightBracket>());
			    itemTerminated = true;
			    break;
			case '^':
			    startRestriction = true;
			    break;
			case '$':
			    endRestriction = false;
			    break;
			case '.': {
			    handleCombiner(itemTerminated);
			    auto elementSet = std::make_shared<ElementNode>();
                elementSet->inverse();
			    nodeList.push_back(elementSet);
			    itemTerminated = true;
			    break;
			}
			default: {
			    handleCombiner(itemTerminated);
			    auto elementSet = std::make_shared<ElementNode>();
                elementSet->setElement(pattern[index]);
			    nodeList.push_back(elementSet);
			    itemTerminated = true;
			    break;
			}
		}
		index++;
	}
}

/*
  construct syntactic tree

  method one:
    1    RegEx -> B A
    2    A -> OrNode B A
    3      -> EmptyNode

    4    B -> D C
    5    C -> CombineNode D C
    6      -> EmptyNode

    7    D -> E F

    8    E -> LeftBracket RegEx RightBracket
    9      -> ElementNode

    10   F -> ClosureNode
    11     -> EmptyNode

  method two: (USED)
    visited pattern (stack)
*/

void SyntacticTree::constructTree()
{
    PostfixExpressionVisitor pev;
    for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++) {
    	(*iter)->accept(&pev);
    }
    auto peList = pev.getPostExpr();
    nodeList = std::move(peList);

    //TreeConstructionVisitor tcv;
}


void SyntacticTree::handleCombiner(bool flag) {
    if (true == flag)
        nodeList.push_back(std::make_shared<CombineNode>());
}

int SyntacticTree::handleElementSet(int index) {
	auto elementSet = std::make_shared<ElementNode>();
    if (pattern[++index] == '^') {
    	elementSet->inverse();
    	++index;
    }
    while (pattern[index] != ']') {
    	if (pattern[index + 1] == '-') {
    		char character = pattern[index];
    		while (character <= pattern[index + 2]) {
    		    elementSet->setElement(character);
    		    character++;
    		}
    	    index += 3;
    	} else {
    		elementSet->setElement(pattern[index]);
    		index += 1;
    	}
    }
    nodeList.push_back(elementSet);
    return index;
}
int SyntacticTree::handleQuantifier(int index) {
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
    nodeList.push_back(std::make_shared<ClosureNode>(minRepetition, maxRepetition, infinite));
    return index;
}

int main() {
	//SyntacticTree st("[aeiou]{,4}[0-9]?");
	SyntacticTree st("[aeiou]{,4}|[0-9]?(com|.?)a*");
	st.scan();
    st.constructTree();
    st.toString();
}

#endif