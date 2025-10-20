#include "ast/RootNode.hpp"

RootNode::RootNode():
    ASTNode() {
    m_nodeType = ASTNodeType::ROOT;
}

const std::list<std::unique_ptr<ASTNode>>& RootNode::getNodes() {
    return m_nodes;
}

void RootNode::printNode(int deep) {
    std::cout << "AST:\n";
    for(const auto& node: m_nodes) {
        node->printNode(deep + 1);
    }
}

void RootNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}
