#include "ast/AssigmentNode.hpp"

AssigmentNode::AssigmentNode(int deep):
    ASTNode(deep) {
    m_nodeType = ASTNodeType::ASSIGMENTS;
}

ASTNode *AssigmentNode::process(ASTNode *parent, const EarleyItem &eItem, int deep) {

}

void AssigmentNode::addNode(std::unique_ptr<ASTNode> node) {
    if (node->getNodeType() == ASTNodeType::VARIABLE) {
        m_variables.push_back(std::move(node));
    } else if (node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_expression.swap(node);
    }
}

void AssigmentNode::printNode() {
    std::cout << "|" << std::string(m_deep, '-') << "- Operator: =\n";
    std::cout << "|" << std::string(m_deep, '-') << "- Left operand:\n";

    for (const auto &var : m_variables) {
        var->printNode();
    }

    std::cout << "|" << std::string(m_deep, '-') << "- Right operand:\n";
    
    if (m_expression) {
        m_expression->printNode();
    }
}

const std::list<std::unique_ptr<ASTNode>>& AssigmentNode::getVariables() {
    return m_variables;
}

const std::unique_ptr<ASTNode> &AssigmentNode::getExpression() {
    return m_expression;
}

