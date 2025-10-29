#pragma once

#include "AST.hpp"

#include <iostream>

class BranchNode: public ASTNode {
public:
    BranchNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;
};
