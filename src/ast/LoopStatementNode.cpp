#include "ast/LoopStatementNode.hpp"

LoopStatementNode::LoopStatementNode():
    ASTNode() {
    m_nodeType = ASTNodeType::LOOP;
}

const std::list<std::unique_ptr<ASTNode>>& LoopStatementNode::getNodes() const noexcept {
    return m_nodes;
}

void LoopStatementNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}

int LoopStatementNode::getLoopType() const noexcept {
    return m_loopType;
}

void LoopStatementNode::setLoopType(int loopType) {
    m_loopType = loopType;
}
