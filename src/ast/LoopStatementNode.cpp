#include "ast/LoopStatementNode.hpp"

LoopStatementNode::LoopStatementNode():
    ASTNode() {
    m_nodeType = ASTNodeType::LOOP;
}

const std::list<std::unique_ptr<ASTNode>>& LoopStatementNode::getNodes() {
    return m_nodes;
}

void LoopStatementNode::addNode(std::unique_ptr<ASTNode> node) {
    m_nodes.push_back(std::move(node));
}

void LoopStatementNode::printNode(int deep) {
    std::cout << "|" << std::string(deep, '-') << " LOOP: " << m_loopType << "\n";

    for(const auto& var: m_nodes) {
        if(var->getNodeType() == ASTNodeType::ASSIGMENTS) {
            std::cout << "|" << std::string(deep + 1, '-') << " Assigments:\n";
            var->printNode(deep + 2);
        } else if(var->getNodeType() == ASTNodeType::CONDITION_EXPRESSION) {
            std::cout << "|" << std::string(deep + 1, '-') << " condition:\n";
            var->printNode(deep + 2);
        } else {
            std::cout << "|" << std::string(deep + 1, '-') << " Loop field:\n";
            var->printNode(deep + 2);
        }
    }
}

int LoopStatementNode::getLoopType() {
    return m_loopType;
}

void LoopStatementNode::setLoopType(int loopType) {
    m_loopType = loopType;
}
