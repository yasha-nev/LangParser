#pragma once

#include "Ast.hpp"

class RootNode: public ASTNode {
public:
    RootNode(int deep);

    ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode() override;

    const std::list<std::unique_ptr<ASTNode>> &getNodes();

private:
    std::list<std::unique_ptr<ASTNode>> m_nodes;
};
