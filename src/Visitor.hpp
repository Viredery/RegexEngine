#ifndef VISITOR_H_
#define VISITOR_H_

#include <memory>

class ElementNode;
class OrNode;
class CombineNode;
class ClosureNode;
class FunctionNode;
class LeftBracket;
class RightBracket;

class Visitor {
public:
    virtual void visit(std::shared_ptr<ElementNode> node) = 0;
    virtual void visit(std::shared_ptr<OrNode> node) = 0;
    virtual void visit(std::shared_ptr<CombineNode> node) = 0;
    virtual void visit(std::shared_ptr<ClosureNode> node) = 0;
    virtual void visit(std::shared_ptr<FunctionNode> node) = 0;
    virtual void visit(std::shared_ptr<LeftBracket> node) = 0;
    virtual void visit(std::shared_ptr<RightBracket> node) = 0;
    virtual ~Visitor() = default;
};

#endif