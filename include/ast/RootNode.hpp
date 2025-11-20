#pragma once

#include "AST.hpp"

class RootNode: public ASTNode {
public:
    RootNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;
};
