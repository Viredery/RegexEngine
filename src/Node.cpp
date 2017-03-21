#include "Node.h"

#include "SyntacticTree.h"
#include "StateEdgePool.h"

namespace Regex {


void Node::setChildNode(std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode) {
	left = leftNode;
	right = rightNode;
}

std::shared_ptr<Node> Node::getLeft() {
    return left;
}

std::shared_ptr<Node> Node::getRight() {
    return right;
}

ElementNode::ElementNode() {
    elementArr.fill(false);
}

void ElementNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string ElementNode::toString() {
    return "ElementNode";
}

void ElementNode::setElement(char character) {
    elementArr[static_cast<std::array<bool, 128>::size_type>(character)] = inverseFlag ? false : true;
}

void ElementNode::setElement(int pos) {
    elementArr[static_cast<std::array<bool, 128>::size_type>(pos)] = inverseFlag ? false : true;
}

void ElementNode::inverse() {
    elementArr.fill(true);
    inverseFlag = true;
}

std::array<bool, 128>& ElementNode::getElementArray() {
    return elementArr;
}

void OrNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string OrNode::toString() {
    return "OrNode";
}

void CombineNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this()); 
}

std::string CombineNode::toString() {
    return "CombineNode";
}

ClosureNode::ClosureNode(int minRep, int maxRep, bool grd):
        minRepetition(minRep), maxRepetition(maxRep), greedy(grd) {}

void ClosureNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string ClosureNode::toString() {
    return std::string("ClosureNode(") + std::to_string(minRepetition) + "," + 
            std::to_string(maxRepetition) + "," + ( greedy ? "G" : "N" ) + ")";
}

bool ClosureNode::getGreedy() const {
    return greedy;
}

int ClosureNode::getMinRepetition() const {
    return minRepetition;
}

int ClosureNode::getMaxRepetition() const {
    return maxRepetition;
}

void CaptureNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string CaptureNode::toString() {
    return "CaptureNode";
}

void ExtensionNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string ExtensionNode::toString() {
    return "ExtensionNode";
}

void PositivePrecheckNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string PositivePrecheckNode::toString() {
    return "PositivePrecheckNode";
}

void NegativePrecheckNode::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string NegativePrecheckNode::toString() {
    return "NegativePrecheckNode";
}

std::string LeftBracket::toString() {
    return "LeftBracket";
}

void RightBracket::accept(Visitor* visitor) {
    visitor->visit(shared_from_this());
}

std::string RightBracket::toString() {
    return "RightBracket";
}

void ElementNode::handleEscapeCharacter(char escapeCharacter) {
    switch (escapeCharacter) {
        case 'a':
            setElement('\a');
            break;
        case 'b':
            setElement('\b');
            break;
        case 't':
            setElement('\t');
            break;
        case 'r':
            setElement('\r');
            break;
        case 'v':
            setElement('\v');
            break;
        case 'f':
            setElement('\f');
            break;
        case 'n':
            setElement('\n');
            break;
        case 'e':
            setElement('\e');
            break;
        case 'w':
            for (char c = 'A'; c <= 'Z'; c++)
                setElement(c);
            for (char c = 'a'; c <= 'z'; c++)
                setElement(c);
            for (char c = '0'; c <= '9'; c++)
                setElement(c);
            setElement('_');
            break;
        case 'd':
            for (char c = '0'; c <= '9'; c++)
                setElement(c);
            break;
        case 's':
            setElement(' ');
            setElement('\f');
            setElement('\n');
            setElement('\r');
            setElement('\t');
            setElement('\v');
            break;
        case 'W':
            for (int pos = 0; pos != int('0'); pos++)
                setElement(pos);
            for (int pos = int('9') + 1; pos != int('A'); pos++)
                setElement(pos);
            for (int pos = int('Z') + 1; pos != int('a'); pos++) {
                if (int('_') == pos)
                    continue;
                setElement(pos);
            }
            for (int pos = int('z') + 1; pos != 128; pos++)
                setElement(pos);
            break;
        case 'D':
            for (int pos = 0; pos != int('0'); pos++)
                setElement(pos);
            for (int pos = int('9') + 1; pos != 128; pos++)
                setElement(pos);
            break;
        case 'S':
            for (int pos = 0; pos != 128; pos++) {
                if (int(' ') == pos || int('\f') == pos || int('\n') == pos ||
                        int('\r') == pos || int('\t') == pos || int('\v') == pos)
                    continue;
                setElement(pos);
            }
            break;
        case '*':
            setElement('*');
            break;
        case '+':
            setElement('+');
            break;
        case '?':
            setElement('?');
            break;
        case '.':
            setElement('.');
            break;
        case '$':
            setElement('$');
            break;
        case '^':
            setElement('^');
            break;
        case '[':
            setElement('[');
            break;
        case ']':
            setElement(']');
            break;
        case '(':
            setElement('(');
            break;
        case ')':
            setElement(')');
            break;
        case '{':
            setElement('{');
            break;
        case '}':
            setElement('}');
            break;
        case '|':
            setElement('|');
            break;
        case '\\':
            setElement('\\');
            break;
        case '-':
            setElement('-');
            break;
        default:
            throw -1;
    }
}

std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Node> node) {
    os << node->toString();
    return os;
}


} // namespace Regex