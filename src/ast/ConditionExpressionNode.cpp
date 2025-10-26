
#include "ast/ConditionExpressionNode.hpp"

ConditionExpressionNode::ConditionExpressionNode():
    ASTNode() {
    m_nodeType = ASTNodeType::CONDITION_EXPRESSION;
}

const std::list<std::unique_ptr<ASTNode>>& ConditionExpressionNode::getNodes() {
    return m_nodes;
}

void ConditionExpressionNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VALUE || node->getNodeType() == ASTNodeType::VARIABLE ||
       node->getNodeType() == ASTNodeType::CONDITION_EXPRESSION ||
       node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_nodes.push_back(std::move(node));
    }
}

void ConditionExpressionNode::printNode(int deep) {

    if(m_nodes.size() == 1) {
        m_nodes.front()->printNode(deep + 1);
    }

    else {
        std::cout << "|" << std::string(deep, '-') << " Condition: " << m_conditionType << "\n";

        int i = 0;
        for(const auto& node: m_nodes) {
            if(i == 0) {
                std::cout << "|" << std::string(deep, '-') << " Left operand:\n";
            } else {
                std::cout << "|" << std::string(deep, '-') << " Right operand: \n";
            }

            node->printNode(deep + 1);

            i++;
        }
    }
}

void ConditionExpressionNode::setConditionType(int conditionType) {
    m_conditionType = conditionType;
}

int ConditionExpressionNode::getConditionType() {
    return m_conditionType;
}
