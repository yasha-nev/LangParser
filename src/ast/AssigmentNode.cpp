#include "ast/AssigmentNode.hpp"

AssigmentNode::AssigmentNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ASSIGMENTS;
}

const std::list<std::unique_ptr<ASTNode>>& AssigmentNode::getNodes() {
    return m_nodes;
}

void AssigmentNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VARIABLE ||
       node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_nodes.push_back(std::move(node));
    }
}

void AssigmentNode::printNode(int deep) {
    std::cout << "|" << std::string(deep, '-') << " Operator: =\n";
    std::cout << "|" << std::string(deep + 1, '-') << " Left operand:\n";

    for(const auto& var: m_nodes) {
        if(var->getNodeType() == ASTNodeType::VARIABLE) {
            var->printNode(deep + 2);
        }
    }

    std::cout << "|" << std::string(deep + 1, '-') << " Right operand:\n";

    for(const auto& exp: m_nodes) {
        if(exp->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
            exp->printNode(deep + 2);
        }
    }
}
