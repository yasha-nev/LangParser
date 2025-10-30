
#include "ast/ArithmeticExpressionNode.hpp"

ArithmeticExpressionNode::ArithmeticExpressionNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ARITHMETIC_EXPRESSION;
}

const std::list<std::unique_ptr<ASTNode>>& ArithmeticExpressionNode::getNodes() {
    return m_nodes;
}

void ArithmeticExpressionNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VALUE || node->getNodeType() == ASTNodeType::VARIABLE ||
       node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_nodes.push_back(std::move(node));
    }
}

void ArithmeticExpressionNode::printNode(int deep) {

    if(m_nodes.size() == 1) {
        m_nodes.front()->printNode(deep + 1);
    }

    else {
        std::cout << "|" << std::string(deep, '-') << " Operator: " << m_operator << "\n";

        int i = 0;
        for(const auto& node: m_nodes) {
            if(i == 0) {
                std::cout << "|" << std::string(deep + 1, '-') << " Left operand:\n";
            } else {
                std::cout << "|" << std::string(deep + 1, '-') << " Right operand: \n";
            }

            node->printNode(deep + 2);

            i++;
        }
    }
}

void ArithmeticExpressionNode::setOperator(int op) {
    m_operator = op;
}
