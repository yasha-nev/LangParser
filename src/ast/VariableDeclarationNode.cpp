#include "ast/VariableDeclarationNode.hpp"

VariableDeclarationNode::VariableDeclarationNode():
    ASTNode() {
    m_nodeType = ASTNodeType::VARIABLE_DECLARATION;
}

VariableDeclarationNode::VariableDeclarationNode(int variableType):
    ASTNode(),
    m_variableType(variableType) {
    m_nodeType = ASTNodeType::VARIABLE_DECLARATION;
}

int VariableDeclarationNode::getVariablesType() const noexcept {
    return m_variableType;
}

const std::list<std::unique_ptr<ASTNode>>& VariableDeclarationNode::getNodes() const noexcept {
    return m_nodes;
}

void VariableDeclarationNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VARIABLE) {
        m_nodes.push_back(std::move(node));
    }
}

void VariableDeclarationNode::setVariablesType(int variableType) {
    m_variableType = variableType;
}
