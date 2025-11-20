#pragma once

#include "AST.hpp"

class BranchStatementNode: public ASTNode {
public:
    BranchStatementNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;
};
