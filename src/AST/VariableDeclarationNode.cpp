#include "AST/VariableDeclarationNode.hpp"

VariableDeclarationNode::VariableDeclarationNode():
    ASTNode() {
    m_nodeType = ASTNodeType::VARIABLE_DECLARATION;
}

VariableDeclarationNode::VariableDeclarationNode(DeclaretionType variableType):
    ASTNode(),
    m_variableType(variableType) {
    m_nodeType = ASTNodeType::VARIABLE_DECLARATION;
}

DeclaretionType VariableDeclarationNode::getVariablesType() {
    return m_variableType;
}

void VariableDeclarationNode::setVariablesType(DeclaretionType variableType) {
    m_variableType = variableType;
}

const std::list<std::unique_ptr<VariableNode>>& VariableDeclarationNode::getVariables() {
    return m_variables;
}

void VariableDeclarationNode::addVariable(std::unique_ptr<VariableNode> variable) {
    m_variables.push_back(std::move(variable));
}
