
#include "ast/ConditionExpressionNode.hpp"

ConditionExpressionNode::ConditionExpressionNode():
    ASTNode() {
    m_nodeType = ASTNodeType::CONDITION_EXPRESSION;
}

const std::list<std::unique_ptr<ASTNode>>& ConditionExpressionNode::getNodes() const noexcept {
    return m_nodes;
}

void ConditionExpressionNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VALUE || node->getNodeType() == ASTNodeType::VARIABLE ||
       node->getNodeType() == ASTNodeType::CONDITION_EXPRESSION ||
       node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_nodes.push_back(std::move(node));
    }
}

void ConditionExpressionNode::setConditionType(int conditionType) {
    m_conditionType = conditionType;
}

int ConditionExpressionNode::getConditionType() const noexcept {
    return m_conditionType;
}
