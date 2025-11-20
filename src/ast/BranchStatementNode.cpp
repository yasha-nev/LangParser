#include "ast/BranchStatementNode.hpp"

BranchStatementNode::BranchStatementNode():
    ASTNode() {
    m_nodeType = ASTNodeType::BRANCH;
}

const std::list<std::unique_ptr<ASTNode>>& BranchStatementNode::getNodes() const noexcept {
    return m_nodes;
}

void BranchStatementNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}
