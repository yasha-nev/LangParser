
#include "ast/ArithmeticExpressionNode.hpp"

ArithmeticExpressionNode::ArithmeticExpressionNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ARITHMETIC_EXPRESSION;
}

const std::list<std::unique_ptr<ASTNode>>& ArithmeticExpressionNode::getNodes() const noexcept {
    return m_nodes;
}

void ArithmeticExpressionNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VALUE || node->getNodeType() == ASTNodeType::VARIABLE ||
       node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_nodes.push_back(std::move(node));
    }
}

void ArithmeticExpressionNode::setOperator(int op) {
    m_operator = op;
}

int ArithmeticExpressionNode::getOperator() const noexcept {
    return m_operator;
}
