#pragma once

#include "AST.hpp"

class AssigmentNode: public ASTNode {
public:
    AssigmentNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;
};
