#pragma once

#include "AST.hpp"

#include <iostream>

class RootNode: public ASTNode {
public:
    RootNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;
};
