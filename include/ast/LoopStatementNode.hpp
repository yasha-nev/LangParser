#pragma once

#include "AST.hpp"

#include <iostream>

class LoopStatementNode: public ASTNode {
public:
    LoopStatementNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;

    int getLoopType();

    void setLoopType(int loopType);

private:
    int m_loopType;
};
