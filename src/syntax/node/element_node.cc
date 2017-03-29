//  element_node.cc
//  Created by viredery on 17/03/28

#include "element_node.h"

namespace regex {

ElementNode::ElementNode(bool antonymy) : antonymy_(antonymy) {
  element_arr_.fill(antonymy_);
}

void ElementNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

int ElementNode::GetPri() const {
  return kHigh;
}

void ElementNode::AddElement(char character) {
  element_arr_[static_cast<std::array<bool, kArraySize>::size_type>(character)] = !antonymy_;
}

void ElementNode::AddElement(int pos) {
  element_arr_[static_cast<std::array<bool, kArraySize>::size_type>(pos)] = !antonymy_;
}

std::array<bool, ElementNode::kArraySize>& ElementNode::element_arr() {
  return element_arr_;
}

void ElementNode::HandleEscapeCharacter(char escapeCharacter) {
  switch (escapeCharacter) {
    case 'a':
      AddElement('\a');
      break;
    case 'b':
      AddElement('\b');
      break;
    case 't':
      AddElement('\t');
      break;
    case 'r':
      AddElement('\r');
      break;
    case 'v':
      AddElement('\v');
      break;
    case 'f':
      AddElement('\f');
      break;
    case 'n':
      AddElement('\n');
      break;
    case 'e':
      AddElement('\e');
      break;
    case '*':
      AddElement('*');
      break;
    case '+':
      AddElement('+');
      break;
    case '?':
      AddElement('?');
      break;
    case '.':
      AddElement('.');
      break;
    case '$':
      AddElement('$');
      break;
    case '^':
      AddElement('^');
      break;
    case '[':
      AddElement('[');
      break;
    case ']':
      AddElement(']');
      break;
    case '(':
      AddElement('(');
      break;
    case ')':
      AddElement(')');
      break;
    case '{':
      AddElement('{');
      break;
    case '}':
      AddElement('}');
      break;
    case '|':
      AddElement('|');
      break;
    case '\\':
      AddElement('\\');
      break;
    case '-':
      AddElement('-');
      break;
    case 'd':
      for (int pos = static_cast<int>('0'); pos <= static_cast<int>('9'); ++pos) {
        AddElement(pos);
      }
      break;
    case 'D':
      for (int pos = 0; pos < static_cast<int>('0'); ++pos) {
        AddElement(pos);
      }
      for (int pos = static_cast<int>('9') + 1; pos < 128; ++pos) {
        AddElement(pos);
      }
      break;
    case 'w':
      for (int pos = static_cast<int>('A'); pos <= static_cast<int>('Z'); ++pos) {
        AddElement(pos);
      }
      for (int pos = static_cast<int>('a'); pos <= static_cast<int>('z'); ++pos) {
        AddElement(pos);
      }
      for (int pos = static_cast<int>('0'); pos <= static_cast<int>('9'); ++pos) {
        AddElement(pos);
      }
      AddElement('_');
      break;
    case 'W':
      for (int pos = 0; pos < static_cast<int>('0'); ++pos) {
        AddElement(pos);
      }
      for (int pos = static_cast<int>('9') + 1; pos < static_cast<int>('A'); ++pos) {
        AddElement(pos);
      }
      for (int pos = static_cast<int>('Z') + 1; pos < static_cast<int>('a'); ++pos) {
        if (int('_') == pos) continue;
        AddElement(pos);
      }
      for (int pos = static_cast<int>('z') + 1; pos < 128; ++pos) {
        AddElement(pos);
      }
      break;
    case 's':
      AddElement(' ');
      AddElement('\f');
      AddElement('\n');
      AddElement('\r');
      AddElement('\t');
      AddElement('\v');
      break;
    case 'S':
      for (int pos = 0; pos < 128; ++pos) {
        if (static_cast<int>(' ') == pos || static_cast<int>('\f') == pos || static_cast<int>('\n') == pos ||
            static_cast<int>('\r') == pos || static_cast<int>('\t') == pos || static_cast<int>('\v') == pos)
          continue;
        AddElement(pos);
      }
      break;
    default:
      throw std::invalid_argument("ERROR TYPE");
  }
}

std::string ElementNode::ConvertString() const {
  return "ElementNode";
}

} //namespace regex