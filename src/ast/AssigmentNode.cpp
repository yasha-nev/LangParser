#include "ast/AssigmentNode.hpp"

AssigmentNode::AssigmentNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ASSIGMENTS;
}

const std::list<std::unique_ptr<ASTNode>>& AssigmentNode::getNodes() const noexcept {
    return m_nodes;
}

void AssigmentNode::addNode(std::unique_ptr<ASTNode> node) {
    if(node->getNodeType() == ASTNodeType::VARIABLE ||
       node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        m_nodes.push_back(std::move(node));
    }
}
