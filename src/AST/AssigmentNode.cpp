#include "AST/AssigmentNode.hpp"

AssigmentNode::AssigmentNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ASSIGMENTS;
}

AssigmentNode::AssigmentNode(std::unique_ptr<ArithmeticExpressionNode> expression):
    ASTNode(),
    m_expression(std::move(expression)) {

    m_nodeType = ASTNodeType::ASSIGMENTS;
}

void AssigmentNode::addVariable(std::unique_ptr<VariableNode> variable) {
    m_variables.push_back(std::move(variable));
}

const std::list<std::unique_ptr<VariableNode>>& AssigmentNode::getVariables() {
    return m_variables;
}

void AssigmentNode::setArithmeticExpression(std::unique_ptr<ArithmeticExpressionNode> node) {
    m_expression.swap(node);
}
