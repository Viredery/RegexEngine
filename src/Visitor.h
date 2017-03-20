#ifndef VISITOR_H_
#define VISITOR_H_

#include <memory>

namespace Regex {

class ElementNode;
class OrNode;
class CombineNode;
class ClosureNode;
class CaptureNode;
class ExtensionNode;
class PositivePrecheckNode;
class NegativePrecheckNode;
class LeftBracket;
class RightBracket;

class Visitor {
public:
    virtual void visit(std::shared_ptr<ElementNode> node) = 0;
    virtual void visit(std::shared_ptr<OrNode> node) = 0;
    virtual void visit(std::shared_ptr<CombineNode> node) = 0;
    virtual void visit(std::shared_ptr<ClosureNode> node) = 0;
    virtual void visit(std::shared_ptr<CaptureNode> node) = 0;
    virtual void visit(std::shared_ptr<ExtensionNode> node) = 0;
    virtual void visit(std::shared_ptr<PositivePrecheckNode> node) = 0;
    virtual void visit(std::shared_ptr<NegativePrecheckNode> node) = 0;
    virtual void visit(std::shared_ptr<LeftBracket> node) = 0;
    virtual void visit(std::shared_ptr<RightBracket> node) = 0;
    virtual ~Visitor() = default;
};


} //namespace Regex

#endif // VISITOR_H_