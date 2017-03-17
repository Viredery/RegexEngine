#include "SyntacticTree.h"

#include <iostream>

#include "PostfixExpressionVisitor.h"
#include "TreeConstructionVisitor.h"

namespace Regex {


SyntacticTree::SyntacticTree(std::string pattern): 
        pattern(pattern) {}

std::shared_ptr<Node> SyntacticTree::getTree() {
    return root;
}

void SyntacticTree::toString() {
	for (auto node : nodeList)
		std::cout << node->toString() << " ";
	std::cout << std::endl;
}

void SyntacticTree::printTree(std::shared_ptr<Node> root) {
    if (root == nullptr)
        std::cout << "nullptr ";
    else {
        std::cout << root->toString() << " ";
        printTree(root->getLeft());
        printTree(root->getRight());
    }
}

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
			    nodeList.push_back(std::make_shared<ClosureNode>(1, -1));
			    itemTerminated = true;
			    break;
			case '?':
			    nodeList.push_back(std::make_shared<ClosureNode>(0, 1));
			    itemTerminated = true;
			    break;
			case '*':
			    nodeList.push_back(std::make_shared<ClosureNode>(0, -1));
			    itemTerminated = true;
			    break;
			case '{':
			    //{m,} {,n} {m,n} {,} {m}
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

void SyntacticTree::constructTree()
{
    PostfixExpressionVisitor pev;
    for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++) {
    	(*iter)->accept(&pev);
    }
    nodeList = std::move(pev.getPostExpr());
    TreeConstructionVisitor tcv;
    for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++) {
    	(*iter)->accept(&tcv);
    }
    root = tcv.getTree();
    nodeList.clear();
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
    index = index + 1;
    std::size_t leftEnd = pattern.find_first_of(',', index);
    std::size_t rightEnd = pattern.find_first_of('}', index);
    if (leftEnd == std::string::npos || leftEnd > rightEnd) {
        minRepetition = maxRepetition = std::stoi(pattern.substr(index, rightEnd - index));
        nodeList.push_back(std::make_shared<ClosureNode>(minRepetition, maxRepetition));
        return rightEnd;
    }
    std::string strMinRepetition = pattern.substr(index, leftEnd - index);
    minRepetition = strMinRepetition == "" ? 0 : std::stoi(strMinRepetition);
    index = leftEnd + 1;
    std::string strMaxRepetition = pattern.substr(index, rightEnd - index);
    maxRepetition = strMaxRepetition == "" ? -1 : std::stoi(strMaxRepetition);
    nodeList.push_back(std::make_shared<ClosureNode>(minRepetition, maxRepetition));
    return rightEnd;
}


} // namespace Regex