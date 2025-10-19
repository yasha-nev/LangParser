
#include "AST/ArithmeticExpressionNode.hpp"

ArithmeticExpressionNode::ArithmeticExpressionNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ARITHMETIC_EXPRESSION;
}

ArithmeticExpressionNode::ArithmeticExpressionNode(const std::string& op):
    ASTNode(),
    m_operator(op) {
    m_nodeType = ASTNodeType::ARITHMETIC_EXPRESSION;
}

ArithmeticExpressionNode::ArithmeticExpressionNode(
    const std::string& op,
    std::unique_ptr<ValueNode> param,
    std::unique_ptr<ArithmeticExpressionNode> expression):
    ASTNode(),
    m_param(std::move(param)),
    m_expression(std::move(expression)) {
    m_nodeType = ASTNodeType::ARITHMETIC_EXPRESSION;
}

void ArithmeticExpressionNode::setParam(std::unique_ptr<ValueNode> param) {
    m_param.swap(param);
}

const std::unique_ptr<ValueNode>& ArithmeticExpressionNode::getParam() {
    return m_param;
}

void ArithmeticExpressionNode::setExpression(std::unique_ptr<ArithmeticExpressionNode> expression) {
    m_expression.swap(expression);
}

const std::unique_ptr<ArithmeticExpressionNode>& ArithmeticExpressionNode::getExpression() {
    return m_expression;
}
