#include "AST/VariableNode.hpp"

VariableNode::VariableNode(const std::string& variable):
    ASTNode(),
    m_variable(variable) {
    m_nodeType = ASTNodeType::VARIABLE;
}

void VariableNode::setVariable(const std::string& variable) {
    m_variable = variable;
}

const std::string& VariableNode::getVariable() {
    return m_variable;
}
