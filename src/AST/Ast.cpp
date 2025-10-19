#include "AST/Ast.hpp"

ASTNode::ASTNode() {
    m_nodeType = ASTNodeType::DEFAULT;
}

ASTNodeType ASTNode::getNodeType() {
    return m_nodeType;
}

void AST::buildTree(const std::set<Lexem>& tokens, const std::set<EarleyItem>& items) {
}
