#include "ast/RootNode.hpp"

RootNode::RootNode(int deep):
    ASTNode(deep) {
    m_nodeType = ASTNodeType::ROOT;
}

ASTNode *RootNode::process(ASTNode *parent, const EarleyItem &eItem, int deep) {

}

void RootNode::printNode() {
    std::cout << "AST:\n";
    for (const auto &node : m_nodes) {
        node->printNode();
    }
}

void RootNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}

const std::list<std::unique_ptr<ASTNode>> &RootNode::getNodes() {
    return m_nodes;
}
