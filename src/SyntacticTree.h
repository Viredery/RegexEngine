#ifndef SYNTACTIC_TREE_H_
#define SYNTACTIC_TREE_H_

#include <vector>
#include <string>
#include <memory>

#include "Node.h"

namespace Regex {


class SyntacticTree
{
public:
	SyntacticTree(std::string pattern);
	~SyntacticTree() = default;
    void toString();
    void scan();
    void constructTree();

    std::shared_ptr<Node> getTree();

	SyntacticTree(SyntacticTree&) = delete;
	SyntacticTree &operator=(const SyntacticTree&) = delete;

    void printTree(std::shared_ptr<Node> root);
private:
    void handleCombiner(bool flag);
    std::size_t handleElementArr(std::size_t index);
    std::size_t handleQuantifier(std::size_t index);
    std::size_t handleLeftBracket(std::size_t index);
    std::string pattern;
    std::vector<std::shared_ptr<Node>> nodeList;
    std::shared_ptr<Node> root = nullptr;
};


} // namespace Regex

#endif // SYNTACTIC_TREE_H_