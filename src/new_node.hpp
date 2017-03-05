#include <vector>
#include <string>
#include <tuple>
#include <cstdio>
class Visitor {};

class Node {
public:
	Node() = default;
	virtual ~Node() = default;
    void setChildNode(Node *leftNode, Node *rightNode) {
    	this->left = leftNode;
    	this->right = rightNode;
    }
    virtual void accept(Visitor visitor) = 0;
    virtual std::string toString() = 0;

    Node *left = nullptr;
    Node *right = nullptr;
};

class LeafNode: public Node {
public:
    LeafNode() = default;
    virtual void accept(Visitor visitor) = 0;
    virtual std::string toString() = 0;
};

class BranchNode: public Node {
public:
    BranchNode() = default;
    virtual void accept(Visitor visitor) = 0;
    virtual std::string toString() = 0;
};

class ElementNode: public LeafNode {
public:
	ElementNode(bool in, char s, char e): 
        included(in), eleRange(s, e) {}
    void accept(Visitor visitor) override {}
    std::string toString() override {
        std::string res("");
        res = res + "ElementNode: " + (included ? "true " : "false ") + 
            std::string{std::get<0>(eleRange)} + "-" + std::string{std::get<1>(eleRange)};
        return res;
    }
	bool included;
	std::tuple<char, char> eleRange;
};

class EmptyNode: public LeafNode {
public:
    EmptyNode() = default;
    void accept(Visitor visitor) override {}
    std::string toString() override {
        return "EmptyNode";
    }
};

class OrNode: public BranchNode {
public:
	OrNode() = default;
    void accept(Visitor visitor) override {}
    std::string toString() override {
        return "OrNode";
    }
};

class CombineNode: public BranchNode {
public:
	CombineNode() = default;
    void accept(Visitor visitor) override {}
    std::string toString() override {
        return "CombineNode";
    }
};

// Only greedy matches currently.
class ClosureNode: public BranchNode {
public:
	ClosureNode(int minRep, int maxRep, bool inf):
        minRepetition(minRep), maxRepetition(maxRep), infinite(inf) {}
    void accept(Visitor visitor) override {}
    std::string toString() override {
        std::string res("");
        res = res + "ClosureNode: " + std::to_string(minRepetition) + " " + std::to_string(maxRepetition);
        return res;
    }

    int minRepetition;
    int maxRepetition;
    bool infinite;
};

// We will handle this node later.
class FunctionNode: public BranchNode {
public:
    FunctionNode() = default;
    void accept(Visitor visitor) override {}
    std::string toString() override {
        return "FunctionNode";
    }
};

class LeftBracket: public Node {
public:
    LeftBracket() = default;
    void accept(Visitor visitor) override {}
    std::string toString() override {
        return "LeftBracket";
    }
};

class RightBracket: public Node {
public:
    RightBracket() = default;
    void accept(Visitor visitor) override {}
    std::string toString() override {
        return "RightBracket";
    }
};