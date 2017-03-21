#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <memory>
#include <array>
#include <iostream>

#include "Visitor.h"

namespace Regex {


class Node {
public:
	Node() = default;
	virtual ~Node() = default;
    void setChildNode(std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode);
    std::shared_ptr<Node> getLeft();
    std::shared_ptr<Node> getRight();
    virtual void accept(Visitor* visitor) = 0;

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Node> node);

private:
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    virtual std::string toString() = 0;
};

class LeafNode: public Node {
public:
    LeafNode() = default;
    virtual void accept(Visitor* visitor) = 0;
private:
    virtual std::string toString() = 0;
};

class BranchNode: public Node {
public:
    BranchNode() = default;
    virtual void accept(Visitor* visitor) = 0;
private:
    virtual std::string toString() = 0;
};

class ElementNode: public LeafNode, public std::enable_shared_from_this<ElementNode> {
public:
    ElementNode();
    void accept(Visitor* visitor) override;
    
    void setElement(char character);
    void setElement(int pos);
    void inverse();
    void handleEscapeCharacter(char escapeCharacter);
    std::array<bool, 128>& getElementArray();
	std::array<bool, 128> elementArr;
    bool inverseFlag = false;
private:
    std::string toString() override;
};

class OrNode: public BranchNode, public std::enable_shared_from_this<OrNode> {
public:
    OrNode() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};

class CombineNode: public BranchNode, public std::enable_shared_from_this<CombineNode> {
public:
    CombineNode() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};

class ClosureNode: public BranchNode, public std::enable_shared_from_this<ClosureNode> {
public:
    ClosureNode(int minRep, int maxRep, bool grd);
    void accept(Visitor* visitor) override;

    int getMinRepetition() const;
    int getMaxRepetition() const;
    bool getGreedy() const;
    int minRepetition;
    int maxRepetition;
    bool greedy;
private:
    std::string toString() override;
};

class LeftBracket: public Node {
public:
    LeftBracket() = default;
    void accept(Visitor* visitor) = 0;
private:
    std::string toString() override;
};

class RightBracket: public Node, public std::enable_shared_from_this<RightBracket> {
public:
    RightBracket() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};

// (pattern)
class CaptureNode: public LeftBracket, public std::enable_shared_from_this<CaptureNode> {
public:
    CaptureNode() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};

// (?:pattern)
class ExtensionNode: public LeftBracket, public std::enable_shared_from_this<ExtensionNode> {
public:
    ExtensionNode() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};

// (?=pattern)
class PositivePrecheckNode: public LeftBracket, public std::enable_shared_from_this<PositivePrecheckNode> {
public:
    PositivePrecheckNode() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};

// (?!pattern)
class NegativePrecheckNode: public LeftBracket, public std::enable_shared_from_this<NegativePrecheckNode> {
public:
    NegativePrecheckNode() = default;
    void accept(Visitor* visitor) override;
private:
    std::string toString() override;
};


} // namespace Regex

#endif // NODE_H_