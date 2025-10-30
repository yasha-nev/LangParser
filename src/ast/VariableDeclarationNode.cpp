#include "ast/VariableDeclarationNode.hpp"

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

const std::list<std::unique_ptr<ASTNode>>& VariableDeclarationNode::getNodes() {
    return m_nodes;
}

void VariableDeclarationNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VARIABLE) {
        m_nodes.push_back(std::move(node));
    }
}

void VariableDeclarationNode::printNode(int deep) {
    std::cout << "|" << std::string(deep, '-')
              << " Declaration: \n";
    std::cout << "|" << std::string(deep + 1, '-')
              << " Type: " << declarationTypeToString(m_variableType) << "\n";
    for(const auto& var: m_nodes) {
        var->printNode(deep + 1);
    }
}

void VariableDeclarationNode::setVariablesType(DeclaretionType variableType) {
    m_variableType = variableType;
}

std::string declarationTypeToString(DeclaretionType type) {

    switch(type) {
        case(DeclaretionType::BOOL):
            return "bool";
        case(DeclaretionType::INT):
            return "int";
        case(DeclaretionType::FLOAT):
            return "float";
        default:
            return "";
    }
}
