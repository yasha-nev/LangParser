#include "ast/VariableNode.hpp"

VariableNode::VariableNode():
    ASTNode() {
    m_nodeType = ASTNodeType::VARIABLE;
}

VariableNode::VariableNode(const std::string& variable):
    ASTNode(),
    m_variable(variable) {
    m_nodeType = ASTNodeType::VARIABLE;
}

const std::list<std::unique_ptr<ASTNode>>& VariableNode::getNodes() {
    return m_nodes;
}

void VariableNode::addNode(std::unique_ptr<ASTNode> node) {
}

void VariableNode::printNode(int deep) {
    std::cout << "|" << std::string(deep, '-') << " Identifier: " << m_variable << "\n";
}

void VariableNode::setVariable(const std::string& variable) {
    m_variable = variable;
}

const std::string& VariableNode::getVariable() {
    return m_variable;
}
