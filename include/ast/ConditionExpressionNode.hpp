#pragma once

#include "AST.hpp"

#include <iostream>

class ConditionExpressionNode: public ASTNode {
public:
    ConditionExpressionNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;

    void setConditionType(int conditionType);

    int getConditionType();

private:
    int m_conditionType;
};
