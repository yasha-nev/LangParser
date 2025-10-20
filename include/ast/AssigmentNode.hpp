#pragma once

#include "Ast.hpp"

class AssigmentNode: public ASTNode {
public:
    AssigmentNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;
};
