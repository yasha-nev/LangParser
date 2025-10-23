#include "ast/AST.hpp"

ASTNode::ASTNode() {
    m_nodeType = ASTNodeType::DEFAULT;
}

ASTNodeType ASTNode::getNodeType() {
    return m_nodeType;
}

AST::AST(std::unique_ptr<ASTNode> root):
    m_root(std::move(root)) {
}

void AST::printTree() {
    m_root->printNode(0);
}
