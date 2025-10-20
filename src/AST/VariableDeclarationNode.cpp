#include "ast/VariableDeclarationNode.hpp"

VariableDeclarationNode::VariableDeclarationNode(int deep):
    ASTNode(deep) {
    m_nodeType = ASTNodeType::VARIABLE_DECLARATION;
}

VariableDeclarationNode::VariableDeclarationNode(int deep, DeclaretionType variableType):
    ASTNode(deep),
    m_variableType(variableType) {
    m_nodeType = ASTNodeType::VARIABLE_DECLARATION;
}

DeclaretionType VariableDeclarationNode::getVariablesType() {
    return m_variableType;
}

ASTNode *VariableDeclarationNode::process(ASTNode *parent, const EarleyItem &eItem, int deep) {

}

void VariableDeclarationNode::addNode(std::unique_ptr<ASTNode> node) {
    if (node->getNodeType() == ASTNodeType::VARIABLE) {
        m_variables.push_back(std::move(node));
    }
}


void VariableDeclarationNode::printNode() {
    std::cout << "|" << std::string(m_deep, '-') << "- Type: " << declarationTypeToString(m_variableType) << "\n";
    for (const auto &var : m_variables) {
        var->printNode();
    }
}


void VariableDeclarationNode::setVariablesType(DeclaretionType variableType) {
    m_variableType = variableType;
}

const std::list<std::unique_ptr<ASTNode>>& VariableDeclarationNode::getVariables() {
    return m_variables;
}



std::string declarationTypeToString(DeclaretionType type) {

    switch (type)
    {
    case (DeclaretionType::BOOL):
        return "bool";
    case (DeclaretionType::INT):
        return "int";
    case (DeclaretionType::FLOAT):
        return "float";
    default:
        return "";
    }
}