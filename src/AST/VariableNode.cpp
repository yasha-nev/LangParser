#include "ast/VariableNode.hpp"

VariableNode::VariableNode(int deep): ASTNode(deep) {
    m_nodeType = ASTNodeType::VARIABLE;
}


VariableNode::VariableNode(int deep, const std::string& variable):
    ASTNode(deep),
    m_variable(variable) {
    m_nodeType = ASTNodeType::VARIABLE;
}

ASTNode *VariableNode::process(ASTNode *parent, const EarleyItem &eItem, int deep) {

}

void VariableNode::addNode(std::unique_ptr<ASTNode> node) {

}

void VariableNode::printNode() {
    std::cout << "|" << std::string(m_deep, '-') << "- Identifier: " << m_variable << "\n";
}

void VariableNode::setVariable(const std::string& variable) {
    m_variable = variable;
}

const std::string& VariableNode::getVariable() {
    return m_variable;
}