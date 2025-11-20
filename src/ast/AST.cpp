#include "ast/AST.hpp"

ASTNode::ASTNode() {
    m_nodeType = ASTNodeType::DEFAULT;
}

ASTNodeType ASTNode::getNodeType() const noexcept {
    return m_nodeType;
}

AST::AST(std::unique_ptr<ASTNode> root):
    m_root(std::move(root)) {
}

const std::unique_ptr<ASTNode>& AST::getRootNode() const noexcept {
    return m_root;
}
