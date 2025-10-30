#include "ast/BranchStatementNode.hpp"

BranchStatementNode::BranchStatementNode():
    ASTNode() {
    m_nodeType = ASTNodeType::BRANCH;
}

const std::list<std::unique_ptr<ASTNode>>& BranchStatementNode::getNodes() {
    return m_nodes;
}

void BranchStatementNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}

void BranchStatementNode::printNode(int deep) {
    std::cout << "|" << std::string(deep, '-') << " If:\n";

    for(const auto& var: m_nodes) {
        if(var->getNodeType() == ASTNodeType::CONDITION_EXPRESSION) {
            std::cout << "|" << std::string(deep, '-') << " Condition\n";
        } else {
            std::cout << "|" << std::string(deep, '-') << " Field\n";
        }
        var->printNode(deep + 1);
    }
}
