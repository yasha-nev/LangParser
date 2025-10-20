
#include "ast/ArithmeticExpressionNode.hpp"

ArithmeticExpressionNode::ArithmeticExpressionNode(int deep):
    ASTNode(deep) {
    m_nodeType = ASTNodeType::ARITHMETIC_EXPRESSION;
}

ASTNode *ArithmeticExpressionNode::process(ASTNode *parent, const EarleyItem &eItem, int deep) {

}

void ArithmeticExpressionNode::addNode(std::unique_ptr<ASTNode> node) {
    if (node->getNodeType() == ASTNodeType::VALUE || node->getNodeType() == ASTNodeType::VARIABLE) {
        m_param.swap(node);
    } else if (node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_expression.swap(node);
    }
}

void ArithmeticExpressionNode::printNode() {
    std::cout << "|" << std::string(m_deep, '-') << "- Operator: " << m_operator << "\n";

    
    if (m_param) {
        std::cout << "|" << std::string(m_deep, '-') << "- Left operand:\n";
        m_param->printNode();
    }
    
    if (m_expression) {
        std::cout << std::string(m_deep, '-') << "- Right operand: =\n";
        m_expression->printNode();
    }
}

void ArithmeticExpressionNode::setOperator(const std::string &op) {
    m_operator = op;
}

const std::unique_ptr<ASTNode>& ArithmeticExpressionNode::getParam() {
    return m_param;
}

const std::unique_ptr<ASTNode>& ArithmeticExpressionNode::getExpression() {
    return m_expression;
}