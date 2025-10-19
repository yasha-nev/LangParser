#include "AST/RootNode.hpp"

RootNode::RootNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ROOT;
}

void RootNode::addNode(std::unique_ptr<ASTNode>&& node) {
    m_nodes.push_back(std::move(node));
}
