#pragma once

#include "AST.hpp"

class ConditionExpressionNode: public ASTNode {
public:
    ConditionExpressionNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void setConditionType(int conditionType);

    int getConditionType() const noexcept;

private:
    int m_conditionType;
};
