#include "ast/RootNode.hpp"

RootNode::RootNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ROOT;
}

const std::list<std::unique_ptr<ASTNode>>& RootNode::getNodes() const noexcept {
    return m_nodes;
}

void RootNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}
